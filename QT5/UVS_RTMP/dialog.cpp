#include "dialog.h"
#include "ui_dialog.h"

#include <QFileDialog>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , dev(0)
{
    ui->setupUi(this);
    ui->video->setStyleSheet("border:1px solid black");
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    const int maxAudioDevCount = 8;
    uvs_dev_info_tX info[maxAudioDevCount];
    int count = maxAudioDevCount;
    CDevSDK::EnumDevice(uvs_dev_audio_capture, info, count);
    ui->liveaudio->setEnabled(count > 0);

    if (dev)
    {
        if (count > 0)
        {
            /* set audio capture */
            dev.SetAudioDevice(uvs_dev_audio_capture, info[0]);
        }
        dev.DeviceStart();
    }

    timer = startTimer(100);
}

Dialog::~Dialog()
{
    killTimer(timer);
    fileClose();
    dev.DeviceClose();
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
    if (rtmp)
    {
        int progress, r = rtmp->GetProgress(progress);
        if (r == UVS_OK)
        {
            ui->progressBar->setValue(progress);
        }
    }
}

void Dialog::fileClose()
{
    if (rtmp)
    {
        delete rtmp;
        rtmp = Q_NULLPTR;
    }
}

void Dialog::on_rtmplive_clicked()
{
    if (dev)
    {
        if (live)
        {
            dev.RTMPStop(UVS_STREAM_ALL);
            dev.EncodeStop(UVS_STREAM_ALL);
            live = false;
        }
        else
        {
            const int mainstream = 0;
            const int substream = 1;

            uvs_audio_codec_e acodec = uvs_audio_codec_AAC;
            uvs_video_codec_e vcodec = uvs_video_codec_sw_h264;
            uvs_encode_config_t config;
            memset(&config, 0, sizeof(uvs_encode_config_t));
            config.encQuality = 28;
            config.rcMode = uvs_video_rcmode_VBR;
            config.encBitRate = 5000;
            config.maxBitRate = 8000;

            // audio stream config
            BOOL audio = ui->liveaudio->checkState() == Qt::Checked;
            if (audio)
            {
                int r = dev.SetAudioProperty(acodec);
                if (r != UVS_OK) return;
            }

            // main stream config
            auto url = ui->mainurl->text();
            if (!url.isEmpty())
            {
                int r = dev.SetVideoEncodeParam(mainstream, vcodec, config);
                if (r != UVS_OK) return;

                r = dev.RTMPSend(mainstream, _string(url), audio);
                if (r != UVS_OK) return;
            }

            // sub stream config
            url = ui->suburl->text();
            if (!url.isEmpty())
            {
                /* Sub stream 480P */
                config.encBitRate = 1000;
                config.maxBitRate = 3000;
                config.scaleWidth = 640;
                config.scaleHeight = 480;

                int r = dev.SetVideoEncodeParam(substream, vcodec, config);
                if (r != UVS_OK) return;

                r = dev.RTMPSend(substream, _string(url), audio);
                if (r != UVS_OK) return;
            }

            int r = dev.EncodeStart(UVS_STREAM_ALL);
            if (r != UVS_OK) return;

            live = true;
        }

        ui->rtmplive->setText(live ? "Stop" : "RTMP Live Start");
    }
}

void Dialog::on_browse_clicked()
{
    auto str = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("MP4 Files (*.mp4)"));
    if (!str.isEmpty())
    {
        ui->mp4file->setText(str);
    }
}

void Dialog::on_rtmpfile_clicked()
{
    if (dev)
    {
        if (rtmp)
        {
            fileClose();
        }
        else
        {
            auto str = ui->mp4file->text();
            auto url = ui->mp4url->text();
            if (!str.isEmpty())
            {
                BOOL audio = ui->mp4audio->checkState() == Qt::Checked;
                rtmp = CFileRTMP::CreateInstance(_string(str), _string(url), audio);
            }
        }

        ui->rtmpfile->setText(rtmp ? "Stop" : "RTMP File Start");
    }
}
