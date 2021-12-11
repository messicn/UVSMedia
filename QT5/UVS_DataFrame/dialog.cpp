#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>
#include <QFileDialog>

#define COPY_FRAME_TO_USER_BUFFER 1

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , dev(0)
{
    ui->setupUi(this);
    ui->video->setStyleSheet("border:1px solid black");
    ui->rotate->addItems(QStringList("None") << "90" << "180" << "270");
    ui->scale->addItems(QStringList("None") << "640 x 480" << "3840 x 2160");

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
    }
}

Dialog::~Dialog()
{
    if (dev)
    {
        if (audioCallback) on_acallback_clicked();
        if (videoCallback) on_vcallback_clicked();
        if (encodeCallback) on_encode_clicked();

        dev.DeviceClose();
    }
    delete ui;
}

void Dialog::framePrint(const uvs_frame_info_t &frame)
{
    enum { NONE, YUY2, UYVY, YV12,
           I420, NV12, NV21, I422,
           I444, BGR24, RGB24, ARGB32,
           RGBA32, ABGR32, BGRA32, MJPG,
           H264IDR, H264I, H264P, H264B,
           H265IDR, H265I, H265P, H265B,
           PCM, MP3, AAC };
    const char* str[] = { "NONE", "Video: YUY2", "Video: UYVY", "Video: YV12",
                            "Video: I420", "Video: NV12", "Video: NV21", "Video: I422",
                            "Video: I444", "Video: BGR24", "Video: RGB24", "Video: ARGB32",
                            "Video: RGBA32", "Video: ABGR32", "Video: BGRA32", "Video: MJPG",
                            "Video: H.264(AVC) IDR", "Video: H.264(AVC) I", "Video: H.264(AVC) P", "Video: H.264(AVC) B",
                            "Video: H.265(HEVC) IDR", "Video: H.265(HEVC) I", "Video: H.265(HEVC) P", "Video: H.265(HEVC) B",
                            "Audio: PCM", "Audio: MP3", "Audio: AAC" };
    int index;
    switch (frame.frameType)
    {
        case uvs_frame_video_YUY2:
            index = YUY2; break;
        case uvs_frame_video_UYVY:
            index = UYVY; break;
        case uvs_frame_video_YV12:
            index = YV12; break;
        case uvs_frame_video_I420:
            index = I420; break;
        case uvs_frame_video_NV12:
            index = NV12; break;
        case uvs_frame_video_NV21:
            index = NV21; break;
        case uvs_frame_video_I422:
            index = I422; break;
        case uvs_frame_video_I444:
            index = I444; break;
        case uvs_frame_video_BGR24:
            index = BGR24; break;
        case uvs_frame_video_RGB24:
            index = RGB24; break;
        case uvs_frame_video_ARGB32:
            index = ARGB32; break;
        case uvs_frame_video_RGBA32:
            index = RGBA32; break;
        case uvs_frame_video_ABGR32:
            index = ABGR32; break;
        case uvs_frame_video_BGRA32:
            index = BGRA32; break;
        case uvs_frame_video_MJPG:
            index = MJPG; break;
        case uvs_frame_video_H264_IDR:
            index = H264IDR; break;
        case uvs_frame_video_H264_I:
            index = H264I; break;
        case uvs_frame_video_H264_P:
            index = H264P; break;
        case uvs_frame_video_H264_B:
            index = H264B; break;
        case uvs_frame_video_H265_IDR:
            index = H265IDR; break;
        case uvs_frame_video_H265_I:
            index = H265I; break;
        case uvs_frame_video_H265_P:
            index = H265P; break;
        case uvs_frame_video_H265_B:
            index = H265B; break;
        case uvs_frame_audio_PCM:
            index = PCM; break;
        case uvs_frame_audio_MP3:
            index = MP3; break;
        case uvs_frame_audio_AAC:
            index = AAC; break;

        default:
            index = NONE; break;
    }

    if (index >= PCM)
    { // audio
        qDebug() << str[index]
                 << " channels " << frame.audioChannels
                 << " bits per sample " << frame.audioBitsPerSample
                 << " samples per second " << frame.audioSamplesPerSec
                << " data " << frame.frameData
                << " size " << frame.frameDataLen
                << " ts " << frame.timeStamp;
    }
    else if (index > NONE)
    {
        qDebug() << str[index]
                 << " width " << frame.videoWidth
                 << " height " << frame.videoHeight
                 << " stride " << frame.videoDataStride[0] << " " << frame.videoDataStride[1]
                << " data " << frame.frameData
                << " size " << frame.frameDataLen
                << " ts " << frame.timeStamp;
    }
    else
    {
        qDebug() << str[NONE];
    }
}

void CALLBACK Dialog::frameCallback(uvsobj_handle obj, const uvs_frame_info_t *frame, void *userData)
{
    Q_UNUSED(obj);
    Q_UNUSED(userData);

    if (frame) framePrint(*frame);
}

void Dialog::showEvent(QShowEvent *event)
{
    if (dev)
    {
        dev.PreviewStart(reinterpret_cast< HWND >(ui->video->winId()));
    }

    QDialog::showEvent(event);
}

void Dialog::getFrameConvertParam(uvs_frame_convert_t &convert)
{
    static uvs_rotate_mode_e mode[] = { uvs_rotate_none, uvs_rotate_90, uvs_rotate_180, uvs_rotate_270 };

    memset(&convert, 0, sizeof(uvs_frame_convert_t));

    // video rotate
    int index = ui->rotate->currentIndex();
    if (index > 0)
    {
        convert.rotateMode = mode[ui->rotate->currentIndex()];
    }

    // video scale
    index = ui->scale->currentIndex();
    if (index > 0)
    {
        convert.scaleWidth = index == 1 ? 640 : 3840;
        convert.scaleHeight = index == 1 ? 480 : 2160;
    }

    // video mirror
    convert.bFlip = ui->flip->checkState() == Qt::Checked;
    convert.bMirror = ui->mirror->checkState() == Qt::Checked;
}

void Dialog::on_vcopy_clicked()
{
    if (dev)
    {
        uvs_frame_info_t frame = { uvs_frame_NONE };

        uvs_frame_convert_t convert;
        getFrameConvertParam(convert);

#if COPY_FRAME_TO_USER_BUFFER
        uvs_video_format_t format;
        if (dev.GetVideoProperty(format) != UVS_OK) return;

        /* Calc buffer size */
        int width = qMax(format.videoWidth, convert.scaleWidth);
        int height = qMax(format.videoHeight, convert.scaleHeight);
        int sz = CDevSDK::CalcBufferSize(format.frameType, width, height);

        static quint8 buf[4 * 3840 * 2160];

        /* Set user buffer */
        frame.frameData = buf;
        frame.frameDataLen = sz;

        /* Set data stride, 0 default */
        /* frame.videoDataStride[0] = 0; */
        /* frame.videoDataStride[1] = 0; */
#endif
        if (convert.frameType != uvs_frame_NONE ||
            convert.bFlip || convert.bMirror ||
            convert.rotateMode != uvs_rotate_none ||
            (convert.scaleWidth > 0 && convert.scaleHeight > 0))
        {
            if (dev.CopyVideoFrame(frame, 1000, &convert) != UVS_OK) return;
        }
        else
        {
            // without conversion
            if (dev.CopyVideoFrame(frame) != UVS_OK) return;
        }

        framePrint(frame);
    }
}

void Dialog::on_snapshot_clicked()
{
    if (dev)
    {
        auto str = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Images (*.png *.bmp *.jpg);;All Files(*.*)"));
        if (!str.isEmpty())
        {
            if (QFileInfo(str).suffix().isEmpty()) str += ".jpg";

            uvs_frame_convert_t convert;
            getFrameConvertParam(convert);

            if (convert.frameType != uvs_frame_NONE ||
                convert.bFlip || convert.bMirror ||
                convert.rotateMode != uvs_rotate_none ||
                (convert.scaleWidth > 0 && convert.scaleHeight > 0))
            {
                dev.CaptureSnapshot(_string(str), 100, &convert);
            }
            else
            {
                // without conversion
                dev.CaptureSnapshot(_string(str));
            }
        }
    }
}

void Dialog::on_encode_clicked()
{
    if (dev)
    {
        do {
            if (encodeCallback)
            {
                dev.SetAudioEncodeFrameCallback(Q_NULLPTR);
                dev.SetVideoEncodeFrameCallback(0, Q_NULLPTR);
                dev.EncodeStop(0);
                encodeCallback = false;
                break;
            }

            // video stream config
            uvs_encode_config_t config = { uvs_target_usage_performance };
            config.codecProfile = uvs_codec_profile_auto;
            config.rcMode = uvs_video_rcmode_VBR;
            config.encBitRate = 4000;
            config.maxBitRate = 8000;
            config.encQuality = 28;
            int r = dev.SetVideoEncodeParam(0, uvs_video_codec_sw_h264, config);
            if (r != UVS_OK) break;

            r = dev.SetVideoEncodeFrameCallback(0, frameCallback);
            if (r != UVS_OK) break;

            // audio stream config
            if (ui->aenc->checkState() == Qt::Checked)
            {
                if (dev.SetAudioProperty(uvs_audio_codec_AAC) == UVS_OK)
                {
                    dev.SetAudioEncodeFrameCallback(frameCallback);
                }
            }

            r = dev.EncodeStart(0);
            if (r != UVS_OK) break;

            encodeCallback = true;
        } while(0);

        ui->encode->setText(encodeCallback ? "Callback Stop" : "Encode Frame Callback");
    }
}

void Dialog::on_vcallback_clicked()
{
    if (dev)
    {
        if (dev.SetVideoRawFrameCallback(videoCallback ? Q_NULLPTR : frameCallback) == UVS_OK)
        {
            videoCallback = !videoCallback;
            ui->vcallback->setText(videoCallback ? "Callback Stop" : "Video Frame Callback");
        }
    }
}

void Dialog::on_vlock_clicked()
{
    if (dev)
    {
        uvs_frame_info_t frame;
        if (dev.LockVideoRawFrame(frame) == UVS_OK)
        {
            framePrint(frame);
            dev.UnlockVideoRawFrame();
        }
    }
}

void Dialog::on_acopy_clicked()
{
    if (dev)
    {
        uvs_frame_info_t frame = { uvs_frame_NONE };

#if COPY_FRAME_TO_USER_BUFFER
        static quint8 buf[256 * 1024];
        /* Set user buffer */
        frame.frameData = buf;
        frame.frameDataLen = sizeof(buf);
#endif
        if (dev.CopyAudioRawFrame(frame) == UVS_OK)
        {
            framePrint(frame);
        }
    }
}

void Dialog::on_acallback_clicked()
{
    if (dev)
    {
        if (dev.SetAudioRawFrameCallback(audioCallback ? Q_NULLPTR : frameCallback) == UVS_OK)
        {
            audioCallback = !audioCallback;
            ui->acallback->setText(audioCallback ? "Callback Stop" : "Audio Frame Callback");
        }
    }
}

void Dialog::on_alock_clicked()
{
    if (dev)
    {
        uvs_frame_info_t frame;
        if (dev.LockAudioRawFrame(frame) == UVS_OK)
        {
            framePrint(frame);
            dev.UnlockAudioRawFrame();
        }
    }
}
