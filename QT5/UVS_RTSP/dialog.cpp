#include "dialog.h"
#include "ui_dialog.h"

#include <QFileDialog>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , dev(0)
{
    ui->setupUi(this);
    ui->video->setStyleSheet("border:1px solid black");
    ui->rtspport->addItems(QStringList("8554") << "554");
    ui->multicast->addItems(QStringList("None") << "233.233.233.233");
    ui->liveaudio->addItems(QStringList("None") << "AAC" << "MP3");
    ui->httptuner->addItems(QStringList("None") << "8080");

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
}

Dialog::~Dialog()
{
    if (live)
    {
        // destroy rtsp server
        on_rtsplive_clicked();
    }
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

bool Dialog::serverCreate()
{
    if (port == 0)
    {
        auto index = ui->rtspport->currentIndex();
        port = index == 0 ? 8554 : 554;

        index = ui->httptuner->currentIndex();
        USHORT tunner = index == 0 ? 0 : 8080;

        int r;
        auto user = ui->username->text();
        auto password = ui->password->text();
        if (user.isEmpty() || password.isEmpty())
        {
            r = CDevSDK::RTSPServerCreate(port, Q_NULLPTR, Q_NULLPTR, tunner);
        }
        else
        {
            r = CDevSDK::RTSPServerCreate(port, _string(user), _string(password), tunner);
        }

        if (r == UVS_OK) return true;

        /* failed */
        QMessageBox::information(this, "RTSP", "RTSP port is busy or without network!");
        port = 0;
    }

    return port > 0;
}

void Dialog::serverDestroy()
{
    if (live || rtsp) return;

    if (port > 0)
    {
        CDevSDK::RTSPServerDestroy(port);
        port = 0;
    }
}

void Dialog::fileClose()
{
    if (rtsp)
    {
        delete rtsp;
        rtsp = Q_NULLPTR;
    }
}

const QString Dialog::stringFromURL(uvs_url_tX &url)
{
#ifdef WIN32
    #ifdef UNICODE
        return QString::fromUtf16(reinterpret_cast<ushort*>(url.szURL));
    #else
        return QString::fromLocal8Bit(url.szURL);
    #endif
#else
        return QString(url.szURL);
#endif
}

void Dialog::on_rtsplive_clicked()
{
    if (dev)
    {
        if (live)
        {
            dev.RTSPStop(UVS_STREAM_ALL);
            dev.EncodeStop(UVS_STREAM_ALL);
            live = false;
            serverDestroy();
        }
        else
        {
            const int mainstream = 0;
            const int substream = 1;

            if (!serverCreate()) return;

            uvs_audio_codec_e acodec = uvs_audio_codec_none;
            uvs_video_codec_e vcodec = uvs_video_codec_sw_h264;
            uvs_encode_config_t config;
            memset(&config, 0, sizeof(uvs_encode_config_t));
            config.encQuality = 28;
            config.rcMode = uvs_video_rcmode_VBR;
            config.encBitRate = 5000;
            config.maxBitRate = 8000;

            // audio stream config
            auto index = ui->liveaudio->currentIndex();
            if (index > 0)
            {
                acodec = index == 1 ? uvs_audio_codec_AAC : uvs_audio_codec_MP3;
                int r = dev.SetAudioProperty(acodec);
                if (r != UVS_OK) return;
            }

            // rtp multicast config
            uvs_rtp_multicast_tX *multicast = Q_NULLPTR;
            uvs_rtp_multicast_tX info;
            memset(&info, 0, sizeof(uvs_rtp_multicast_tX));
            QString addr("233.233.233.233");
            index = ui->multicast->currentIndex();
            if (index > 0)
            {
                multicast = &info;
                info.ipAddress = _string(addr);
                info.ipPort = 23333;
            }

            // main stream config
            int r = dev.SetVideoEncodeParam(mainstream, vcodec, config);
            if (r != UVS_OK) return;

            QString name("main");
            r = dev.RTSPStart(mainstream, port, acodec != uvs_audio_codec_none, _string(name), multicast);
            if (r != UVS_OK) return;

            // sub stream config
            bool stream = ui->substream->checkState() == Qt::Checked;
            if (stream)
            {
                /* Sub stream 480P */
                config.encBitRate = 1000;
                config.maxBitRate = 3000;
                config.scaleWidth = 640;
                config.scaleHeight = 480;

                r = dev.SetVideoEncodeParam(substream, vcodec, config);
                if (r != UVS_OK) return;

                name = "sub";
                r = dev.RTSPStart(substream, port, acodec != uvs_audio_codec_none, _string(name), multicast);
                if (r != UVS_OK) return;
            }

            r = dev.EncodeStart(UVS_STREAM_ALL);
            if (r != UVS_OK) return;

            live = true;

            uvs_url_tX url;
            dev.RTSPGetURL(mainstream, url);
            ui->mainurl->setText(stringFromURL(url));
            if (stream)
            {
                dev.RTSPGetURL(substream, url);
                ui->suburl->setText(stringFromURL(url));
            }
        }

        ui->rtsplive->setText(live ? "Stop" : "RTSP Live Start");
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

void Dialog::on_rtspfile_clicked()
{
    if (dev)
    {
        if (rtsp)
        {
            fileClose();
            serverDestroy();
        }
        else
        {
            auto str = ui->mp4file->text();
            if (!str.isEmpty())
            {
                if (!serverCreate()) return;

                BOOL audio = ui->mp4audio->checkState() == Qt::Checked;
                rtsp = CFileRTSP::CreateInstance(_string(str), port, audio, Q_NULLPTR);
                if (rtsp)
                {
                    uvs_url_tX url;
                    int r = rtsp->GetURL(url);
                    if (r == UVS_OK) ui->mp4url->setText(stringFromURL(url));
                }
            }
        }

        ui->rtspfile->setText(rtsp ? "Stop" : "RTSP File Start");
    }
}
