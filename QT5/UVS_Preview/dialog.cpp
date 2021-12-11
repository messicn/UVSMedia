#include "dialog.h"
#include "ui_dialog.h"

#ifdef WIN32
#include <QKeyEvent>
#else
#include <QTimer>
class SDLEvent : public QEvent
{
public:
    SDLEvent(uvsobj_handle obj, const uvs_sdl_event_t *event)
        : QEvent(QEvent::User), devObj(obj), sdlEvent(*event) {}
    ~SDLEvent() = default;

    uvsobj_handle devObj;
    uvs_sdl_event_t sdlEvent;
};
#endif

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->video->setStyleSheet("border:1px solid black");

#ifdef WIN32
    ui->ontop->hide();
    ui->video->installEventFilter(this);
    ui->vrenderer->addItems(QStringList("DirectX 3D") << "Direct Draw");
#else
    ui->vrenderer->addItems(QStringList("OpenGL") << "Vulkan");
#endif

    QStringList str;
    enumDev(uvs_dev_audio_capture, str);
    if (!str.isEmpty()) ui->acap->addItems(str);

    enumDev(uvs_dev_video_capture, str);
    if (!str.isEmpty()) ui->vcap->addItems(str);

    enumDev(uvs_dev_audio_renderer, str);
    if (!str.isEmpty()) ui->arenderer->addItems(str);

    ui->volume->setRange(0, 100);
    ui->balance->setRange(-100, 100);

    connect(ui->acap, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dialog::devChanged);
    connect(ui->vcap, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dialog::devChanged);
    connect(ui->arenderer, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dialog::devChanged);

    connect(ui->mirror, QOverload<bool>::of(&QPushButton::clicked), this, &Dialog::videoMirror);
    connect(ui->flip, QOverload<bool>::of(&QPushButton::clicked), this, &Dialog::videoMirror);

    devStart(false); /* start preview in showEvent */
}

Dialog::~Dialog()
{
    previewStop();
    devClose();
    delete ui;
}

void Dialog::showEvent(QShowEvent *event)
{
#ifndef WIN32
    if (alwaysOnTop())
    {
        /* start preview in moveEvent */
    }
    else
#endif
    {
        previewStart();
    }
    QDialog::showEvent(event);
}

#ifdef WIN32
bool Dialog::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->video && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ev = dynamic_cast< QKeyEvent* >(event);
        if (ev && ev->key() == Qt::Key_Escape)
        {
            if (ui->video->isFullScreen())
            {
                ui->video->setWindowFlag(Qt::Window, false);
                ui->video->move(pos);
                ui->video->resize(size);
                ui->video->show();
                return true;
            }
        }
    }

    return QDialog::eventFilter(obj, event);
}

#else
void Dialog::eventCallback(uvsobj_handle obj, const uvs_sdl_event_t *event, void *userData)
{
    Dialog *dlg = static_cast< Dialog* >(userData);
    qApp->postEvent(dlg, new SDLEvent(obj, event));
}

void Dialog::customEvent(QEvent *event)
{
    SDLEvent *ev = dynamic_cast< SDLEvent* >(event);
    if (ev)
    {
        if (ev->sdlEvent.type == uvs_sdl_event_key_down)
        {
#define KEY_ESC 41
            if (ev->sdlEvent.scancode == KEY_ESC)
            {
                if (dev)
                {
                    dev.PreviewStop();
                    previewStart();
                }
            }
        }
    }
}

void Dialog::moveEvent(QMoveEvent *event)
{
    if (alwaysOnTop())
    {
        previewStop();

        ++count;
        QTimer::singleShot(100, this, &Dialog::moveDelay);
    }

    QWidget::moveEvent(event);
}

void Dialog::moveDelay()
{
    if (--count == 0)
    {
        previewStart();
    }
}

bool Dialog::alwaysOnTop()
{
    return ui->ontop->checkState() == Qt::Checked;
}

#endif

void Dialog::enumDev(uvs_dev_type_e t, QStringList &s)
{
    uvs_dev_info_tX info[16];
    int num = _countof(info);
    CDevSDK::EnumDevice(t, info, num);

    s.clear();
    for (int i=0; i<num; i++)
    {
#ifdef WIN32
    #ifdef UNICODE
        s << QString::fromUtf16(reinterpret_cast<ushort*>(info[i].szFriendlyDevName));
    #else
        s << QString::fromLocal8Bit(info[i].szFriendlyDevName);
    #endif
#else
        s << info[i].szFriendlyDevName;
#endif
    }
}

void Dialog::devStart(bool preview)
{
    auto index = ui->vcap->currentIndex();
    if (index >= 0)
    {
        dev.DeviceOpen(index);
        if (dev)
        {
            index = ui->acap->currentIndex();
            if (index >= 0)
            {
                /* set audio capture */
                dev.SetAudioDevice(uvs_dev_audio_capture, index);
            }

            index = ui->arenderer->currentIndex();
            if (index >= 0)
            {
                /* set audio renderer */
                dev.SetAudioDevice(uvs_dev_audio_renderer, index);
            }

            dev.DeviceStart();
            if (preview) previewStart();

            /* set video effect */
            int val[4];
            QSlider *obj[] = { ui->brightness,
                             ui->contrast,
                             ui->saturation,
                             ui->gamma };
            uvs_video_effect_e effect[] = { uvs_video_brightness,
                                          uvs_video_contrast,
                                          uvs_video_saturation,
                                          uvs_video_gamma };
            for (size_t i=0; i<_countof(effect); i++)
            {
                int r = dev.GetVideoEffectRange(effect[i], val[0], val[1], val[2], val[3]);
                if (r == UVS_OK)
                {
                    r = dev.GetVideoEffect(effect[i],val[2]);
                    if (r == UVS_OK)
                    {
                        obj[i]->setRange(val[0], val[1]);
                        obj[i]->setValue(val[2]);
                    }
                }
            }

            int r = dev.GetAudioVolume(val[0]);
            if (r == UVS_OK) ui->volume->setValue(val[0]);

            r = dev.GetAudioBalance(val[0]);
            if (r == UVS_OK) ui->balance->setValue(val[0]);

            ui->mirror->setCheckState(Qt::Unchecked);
            ui->flip->setCheckState(Qt::Unchecked);
            ui->mute->setCheckState(Qt::Unchecked);

            zoomin = zoomout = false;
        }
    }
}

void Dialog::devClose(void)
{
    if (dev)
    {
        dev.DeviceClose();
        ui->video->update();
    }
}

void Dialog::previewStart(void)
{
    if (dev)
    {
#ifdef WIN32
        auto disp = ui->vrenderer->currentIndex() == 0 ? uvs_disp_type_d3d : uvs_disp_type_ddraw;
        dev.PreviewStart(reinterpret_cast< HWND >(ui->video->winId()), disp);
#else
        int disp = ui->vrenderer->currentIndex() == 0 ? uvs_window_opengl : uvs_window_vulkan;
        if (alwaysOnTop())
        {
            auto pos = ui->video->mapToGlobal(QPoint(0, 0));
            auto size = ui->video->size();

            RECT rc;
            rc.x = pos.x();
            rc.y = pos.y();
            rc.width = size.width();
            rc.height = size.height();
            disp |= uvs_window_always_on_top;
            dev.PreviewStart(&rc, static_cast<uvs_window_e>(disp), Q_NULLPTR);
        }
        else
        {
            dev.PreviewStart(reinterpret_cast< HWND >(ui->video->winId()));
        }
#endif
    }
}

void Dialog::previewStop(void)
{
    if (dev)
    {
        ui->video->hide();
        dev.PreviewStop();
        ui->video->show();
    }
}

void Dialog::devChanged()
{
    previewStop();
    devClose();
    devStart(true);
}

void Dialog::videoMirror()
{
    if (dev)
    {
        BOOL horiz = ui->mirror->checkState() == Qt::Checked;
        BOOL vert = ui->flip->checkState() == Qt::Checked;
        dev.SetVideoMirror(horiz, vert);
    }
}

void Dialog::on_vrenderer_currentIndexChanged(int index)
{
    Q_UNUSED(index);

    if (zoomin) on_zoomin_clicked();
    if (zoomout) on_zoomout_clicked();

    previewStop();
    previewStart();
}

void Dialog::on_brightness_valueChanged(int value)
{
    if (dev)
    {
        dev.SetVideoEffect(uvs_video_brightness, value);
    }
}

void Dialog::on_contrast_valueChanged(int value)
{
    if (dev)
    {
        dev.SetVideoEffect(uvs_video_contrast, value);
    }
}

void Dialog::on_saturation_valueChanged(int value)
{
    if (dev)
    {
        dev.SetVideoEffect(uvs_video_saturation, value);
    }
}

void Dialog::on_gamma_valueChanged(int value)
{
    if (dev)
    {
        dev.SetVideoEffect(uvs_video_gamma, value);
    }
}

void Dialog::on_volume_valueChanged(int value)
{
    if (dev)
    {
        dev.SetAudioVolume(value);
    }
}

void Dialog::on_balance_valueChanged(int value)
{
    if (dev)
    {
        dev.SetAudioBalance(value);
    }
}

void Dialog::on_mute_stateChanged(int arg1)
{
    if (dev)
    {
        dev.SetAudioMute(arg1 == Qt::Checked);
    }
}

void Dialog::on_fullsc_clicked()
{
    if (dev)
    {
        if (zoomin) on_zoomin_clicked();
        if (zoomout) on_zoomout_clicked();

#ifdef WIN32
        pos = ui->video->pos();
        size = ui->video->size();
        ui->video->setWindowFlag(Qt::Window);
        ui->video->showFullScreen();
#else
        previewStop();

        int disp = ui->vrenderer->currentIndex() == 0 ? uvs_window_opengl : uvs_window_vulkan;
        disp |= uvs_window_fullscreen;
        dev.PreviewStart(Q_NULLPTR, static_cast<uvs_window_e>(disp), Q_NULLPTR);
        dev.PreviewSetEvent(uvs_sdl_event_key_down, eventCallback, this);
#endif
    }
}

void Dialog::on_zoomin_clicked()
{
    if (dev)
    {
        if (zoomin)
        {
            dev.PreviewSetRect(Q_NULLPTR, Q_NULLPTR);
            zoomin = false;
        }
        else
        {
            uvs_video_format_t format;
            int r = dev.GetVideoProperty(format);
            if (r == UVS_OK)
            {
                /* Zoom 2X */
                RECT rc;
#ifdef WIN32
                rc.left = format.videoWidth / 4;
                rc.top = format.videoHeight / 4;
                rc.right = format.videoWidth * 3 / 4;
                rc.bottom = format.videoHeight * 3 / 4;
#else
                rc.x = format.videoWidth / 4;
                rc.y = format.videoHeight / 4;
                rc.width = format.videoWidth / 2;
                rc.height = format.videoHeight / 2;
#endif
                dev.PreviewSetRect(Q_NULLPTR, &rc);
                zoomin = true;
            }
        }
    }
}

void Dialog::on_freeze_clicked()
{
    if (dev)
    {
        BOOL freeze;
        int r = dev.PreviewIsFreeze(freeze);
        if (r == UVS_OK) dev.PreviewFreeze(!freeze);
    }
}

void Dialog::on_zoomout_clicked()
{
    if (dev)
    {
        if (zoomout)
        {
            dev.PreviewSetRect(Q_NULLPTR, Q_NULLPTR);
            zoomout = false;
        }
        else
        {
            auto width = ui->video->size().width();
            auto height = ui->video->size().height();

            /* Zoom 1/2X */
            RECT rc;
#ifdef WIN32
            rc.left = width / 4;
            rc.top = height / 4;
            rc.right = width * 3 / 4;
            rc.bottom = height * 3 / 4;
#else
            rc.x = width / 4;
            rc.y = height / 4;
            rc.width = width / 2;
            rc.height = height / 2;
#endif

#ifdef WIN32
            COLORREF cr = RGB(240, 240, 240);
#else
            uvs_color_t c;
            c.r = 240;
            c.g = 240;
            c.b = 240;
            c.alpha = 255;
            COLORREF cr = &c;
#endif
            dev.PreviewSetRect(&rc, Q_NULLPTR, cr);
            ui->video->update();
            zoomout = true;
        }
    }
}

void Dialog::on_ontop_clicked()
{
    on_vrenderer_currentIndexChanged(ui->vrenderer->currentIndex());
}
