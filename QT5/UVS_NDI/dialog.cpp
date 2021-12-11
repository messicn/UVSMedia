#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , dev(0)
{
    ui->setupUi(this);
    ui->video->setStyleSheet("border:1px solid black");
    ui->source->setText("UVS Stream");
    ui->group->setEnabled(false);
    ui->rotate->addItems(QStringList("None") << "90" << "180" << "270");
    ui->scale->addItems(QStringList("None") << "640 x 480" << "3840 x 2160");

    const int maxAudioDevCount = 8;
    uvs_dev_info_tX info[maxAudioDevCount];
    int count = maxAudioDevCount;
    CDevSDK::EnumDevice(uvs_dev_audio_capture, info, count);
    ui->audio->setEnabled(count > 0);

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

void Dialog::on_stream_clicked()
{
    static uvs_rotate_mode_e mode[] = { uvs_rotate_none, uvs_rotate_90, uvs_rotate_180, uvs_rotate_270 };

    if (dev)
    {
        if (start)
        {
            dev.NDIStop();
            dev.NDIDestroy();
            start = false;
        }
        else
        {
            uvs_frame_convert_t convert;
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

            auto source = ui->source->text();
            if (!source.isEmpty())
            {
                auto group = ui->group->text();
                int r = dev.NDICreate(_string(source), group.isEmpty() ? Q_NULLPTR : _string(group));
                if (r == UVS_OK)
                {
                    if (convert.bFlip || convert.bMirror ||
                        convert.rotateMode != uvs_rotate_none ||
                        (convert.scaleWidth > 0 && convert.scaleHeight > 0))
                    {
                        dev.NDIConfig(&convert);
                    }

                    r = dev.NDIStart(ui->audio->checkState() == Qt::Checked);
                    if (r == UVS_OK) start = true;
                }
            }
        }

        ui->stream->setText(start ? "NDI Stream Stop" : "NDI Stream Start");
    }
}
