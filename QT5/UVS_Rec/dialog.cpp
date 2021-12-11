#include "dialog.h"
#include "ui_dialog.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , dev(0)
{
    ui->setupUi(this);
    ui->video->setStyleSheet("border:1px solid black");
    ui->status->setStyleSheet("border:1px solid black");

    ui->venc->addItems(QStringList("Intel GPU H.264")
                       << "Intel GPU H.265"
                       << "Nvidia GPU H.264"
                       << "NVidia GPU H.265"
                       << "Open H.264");
    ui->aenc->addItems(QStringList("None") << "AAC" << "MP3");
    ui->encusage->addItems(QStringList("High Perfomance") << "Balance" << "High Quality");
    ui->encbitrate->addItems(QStringList("3000Kbps") << "5000Kbps" << "8000Kbps");
    ui->maxbitrate->addItems(QStringList("8000Kbps") << "10000Kbps" << "12000Kbps");
    ui->crop->addItems(QStringList("None") << "320 x 240" << "640 x 480" << "1280 x 720");
    ui->ratectrl->addItems(QStringList("CBR") << "CQP" << "VBR");
    ui->scale->addItems(QStringList("None") << "640 x 480" << "1280 x 720" << "1920 x 1280");
    ui->scaleusage->addItems(QStringList("High Perfomance") << "Balance" << "Quality" << "High Quality");
    ui->dur->addItems(QStringList("No Limits") << "1min" << "5min" << "15min");
    ui->size->addItems(QStringList("No Limits") << "32MB" << "128MB" << "512MB");

    ui->maindir->setText(QDir::currentPath());

    const int maxAudioDevCount = 8;
    uvs_dev_info_tX info[maxAudioDevCount];
    int count = maxAudioDevCount;
    CDevSDK::EnumDevice(uvs_dev_audio_capture, info, count);

    if (dev)
    {
        if (count > 0)
        {
            /* set audio capture */
            dev.SetAudioDevice(uvs_dev_audio_capture, info[0]);
        }

        dev.DeviceStart();

        // init enc frame rate, default same as input
        uvs_video_format_t format;
        int r = dev.GetVideoProperty(format);
        if (r == UVS_OK)
        {
            ui->framerate->addItems(QStringList("Default")
                                    << QString::number(format.frameRate / 2, 'f', 2));
        }
    }

    timer = startTimer(1000);
}

Dialog::~Dialog()
{
    dev.DeviceClose();
    killTimer(timer);
    delete ui;
}

void Dialog::showEvent(QShowEvent *event)
{
    if (dev)
    {
        dev.PreviewStart(reinterpret_cast< HWND >(ui->video->winId()));
    }
    QDialog::showEvent(event);
}

void Dialog::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if (dev)
    {
        if (rec)
        {
            uvs_encode_status_t status;
            int r = dev.GetVideoEncodeStatus(0, status);
            if (r == UVS_OK)
            {
                QString str("Input Frames:");
                str += QString::number(status.inputFrames);
                str += " (";
                str += QString::number(status.inputFrameRate, 'f', 2);
                str += "fps)\n";
                str += "Encode Frames:";
                str += QString::number(status.encodeFrames);
                str += " (";
                str += QString::number(status.encodeFrameRate, 'f', 2);
                str += "fps)";
                ui->status->setText(str);
            }
        }
    }
}

void Dialog::getConfig(uvs_encode_config_t &config)
{
    memset(&config, 0, sizeof(uvs_encode_config_t));
    config.encQuality = 28;

    // enc usage quality or performance related to encoding framerate
    static uvs_target_usage_e usage[] = { uvs_target_usage_performance, uvs_target_usage_balance, uvs_target_usage_quality };
    config.targetUsage = usage[ui->encusage->currentIndex()];

    // enc bitrate control
    static int encKbps[] = { 3000, 5000, 8000 };
    config.encBitRate = encKbps[ui->encbitrate->currentIndex()];

    static int maxKbps[] = { 8000, 10000, 12000 };
    config.maxBitRate = maxKbps[ui->maxbitrate->currentIndex()];

    static uvs_video_rcmode_e mode[] = { uvs_video_rcmode_CBR, uvs_video_rcmode_CQP, uvs_video_rcmode_VBR };
    config.rcMode = mode[ui->ratectrl->currentIndex()];

    // enc frame rate, 0 same as input
    int index = ui->framerate->currentIndex();
    if (index > 0)
    {
        uvs_video_format_t format;
        int r = dev.GetVideoProperty(format);
        if (r == UVS_OK) config.frameRate = format.frameRate / 2;
    }

    // video crop
    index = ui->crop->currentIndex();
    if (index > 0)
    {
        static int pos[][4] = { {0, 0, 0, 0}, {160, 120, 320, 240}, {160, 120, 640, 480}, {160, 120, 1280, 720} };
        config.cropLeft = pos[index][0];
        config.cropTop = pos[index][1];
        config.cropWidth = pos[index][2];
        config.cropHeight = pos[index][3];
    }

    // video scale
    index = ui->scale->currentIndex();
    if (index > 0)
    {
        /* Video scale after crop */
        static int sz[][2] = { {0, 0}, {640, 480}, {1280, 720}, {1920, 1080} };
        config.scaleWidth = sz[index][0];
        config.scaleHeight = sz[index][1];
    }

    static uvs_scale_usage_e scale[] = { uvs_scale_usage_performance,
                                         uvs_scale_usage_balance,
                                         uvs_scale_usage_quality,
                                         uvs_scale_usage_high_quality };
    config.scaleUsage = scale[ui->scaleusage->currentIndex()];
}

void Dialog::on_mainrec_clicked()
{
    auto str = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ".", QFileDialog::ShowDirsOnly);
    if (!str.isEmpty())
    {
        ui->maindir->setText(str);
    }
}

void Dialog::on_subrec_clicked()
{
    auto str = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ".", QFileDialog::ShowDirsOnly);
    if (!str.isEmpty())
    {
        ui->subdir->setText(str);
    }
}

void Dialog::on_rec_clicked()
{
    if (dev)
    {
        if (rec)
        {
            dev.RecordStop(UVS_STREAM_ALL);
            dev.EncodeStop(UVS_STREAM_ALL);

            rec = false;
            if (pause)
            {
                pause = false;
                ui->pause->setText("Rec Pause");
            }
        }
        else
        {
            const int mainstream = 0;
            const int substream = 1;

            static uvs_video_codec_e v[] = { uvs_video_codec_intel_h264,
                                             uvs_video_codec_intel_h265,
                                             uvs_video_codec_nvidia_h264,
                                             uvs_video_codec_nvidia_h265,
                                             uvs_video_codec_sw_h264 };
            static uvs_audio_codec_e a[] = { uvs_audio_codec_none, uvs_audio_codec_AAC, uvs_audio_codec_MP3 };
            static int KB[] = { 0, 32 * 1024, 128 * 1024, 256 *1024 };
            static int ms[] = { 0, 60 * 1000, 5 * 60 * 1000, 15 * 60 * 1000 };

            uvs_audio_format_t format;
            uvs_audio_codec_e acodec;
            int r = dev.GetAudioProperty(format, acodec); /* audio input is ready? */
            acodec = r == UVS_OK ? a[ui->aenc->currentIndex()] : uvs_audio_codec_none;

            // auto rec limit file size(KB), 0 manual control
            auto sz = KB[ui->size->currentIndex()];

            // auto rec limit duration(ms), 0 manual control
            auto dur = ms[ui->dur->currentIndex()];

            uvs_encode_config_t config;
            getConfig(config);

            // mp4 file repair support
            auto flags = ui->repair->isChecked();

            // main stream config
            auto dir = ui->maindir->text();
            auto vcodec = v[ui->venc->currentIndex()];
            if (!dir.isEmpty())
            {
                r = dev.SetVideoEncodeParam(mainstream, vcodec, config);
                if (r != UVS_OK)
                {
                    r = CDevSDK::QueryVideoEncoder(vcodec);
                    if (r != UVS_OK)
                    {
                        QMessageBox::information(this, "Record", "HW not support or codec library not found!");
                    }
                    return;
                }

                QString str("UVS Main Stream");
                r = dev.SetRecordMetadata(mainstream, _string(str));

                /* %M month, %D month of day, %H 24 hours, %h 12 hours, %m minute, %s second, %Y year,
                 * %t AM/PM, %N month name, %n month short name, %W week name, %w week short name, %i stream index, %% % */
                str = QDir::cleanPath(dir + QDir::separator() + "%Y%M%D_%H%m%s_%i.mp4");
                r = dev.RecordStart(mainstream, _string(str), Q_NULLPTR, acodec != uvs_audio_codec_none, flags, sz, dur);
                if (r != UVS_OK) return;
            }

            // sub stream config
            dir = ui->subdir->text();
            if (!dir.isEmpty())
            {
                /* 480P sub stream */
                config.scaleWidth = 640;
                config.scaleHeight = 480;
                config.encBitRate = 1000;
                config.maxBitRate = 3000;

                r = dev.SetVideoEncodeParam(substream, vcodec, config);
                if (r != UVS_OK)
                {
                    r = CDevSDK::QueryVideoEncoder(vcodec);
                    if (r != UVS_OK)
                    {
                        QMessageBox::information(this, "Record", "HW not support or codec library not found!");
                    }
                    return;
                }

                QString str("UVS Sub Stream");
                r = dev.SetRecordMetadata(substream, _string(str));

                str = QDir::cleanPath(dir + QDir::separator() + "%Y%M%D_%H%m%s_%i.mp4");
                r = dev.RecordStart(substream, _string(str), Q_NULLPTR, acodec != uvs_audio_codec_none, flags, sz, dur);
                if (r != UVS_OK) return;
            }

            // audio stream config
            dev.SetAudioProperty(acodec);

            r = dev.EncodeStart(UVS_STREAM_ALL);
            if (r != UVS_OK)
            {
                QMessageBox::information(this, "Record", "Encode failed!");
                return;
            }

            rec = true;
        }

        ui->rec->setText(rec ? "Rec Stop" : "Rec Start");
    }
}

void Dialog::on_pause_clicked()
{
    if (dev)
    {
        if (rec)
        {
            dev.RecordPause(UVS_STREAM_ALL, pause);
            pause = !pause;
            ui->pause->setText(pause ? "Rec Resume" : "Rec Pause");
        }
    }
}
