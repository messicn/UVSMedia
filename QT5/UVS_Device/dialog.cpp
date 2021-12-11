#include "dialog.h"
#include "ui_dialog.h"

#include <QEvent>
#include <QFileDialog>
#include <QColorDialog>

class DevEvent : public QEvent
{
public:
    DevEvent(uvs_dev_notify_e notify, const uvs_dev_info_tX *info, uvsobj_handle obj)
        : QEvent(QEvent::User), devNofity(notify), devInfo(*info), devObj(obj) {}
    ~DevEvent() = default;

    uvs_dev_notify_e devNofity;
    uvs_dev_info_tX devInfo;
    uvsobj_handle devObj;
};

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , dev(0)
    , color(Qt::black)
{
    ui->setupUi(this);
    ui->video->setStyleSheet("border:1px solid black");
    ui->mode->addItem("Stretch");
    ui->mode->addItem("Center");

    CDevSDK::SetDeviceCallback(devCallback, this);

    dev.DeviceStart();
    timer = startTimer(300);
}

Dialog::~Dialog()
{
    killTimer(timer);

    /* Event disabled */
    CDevSDK::SetDeviceCallback(Q_NULLPTR, Q_NULLPTR);

    previewStop();
    dev.DeviceClose();

    delete ui;
}

void CALLBACK Dialog::devCallback(uvs_dev_notify_e notify, const uvs_dev_info_tX *info, uvsobj_handle obj, void *userData)
{
    Dialog *dlg = static_cast< Dialog* >(userData);
    qApp->postEvent(dlg, new DevEvent(notify, info, obj));
}

void Dialog::showEvent(QShowEvent *event)
{
    previewStart();
    QDialog::showEvent(event);
}

void Dialog::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer)
    {
        QString str;
        if (dev)
        {
            BOOL bSignal, bMode;
            auto r = dev.GetVideoStatus(bSignal, bMode);
            if (r == UVS_OK)
            {
                str = bSignal ? "Signal" : "No Signal";
                str += bMode ? "(USB3)" : "(USB2)";
            }
        }

        ui->status->setText(str);
    }
}

void Dialog::customEvent(QEvent *event)
{
    DevEvent *ev = dynamic_cast< DevEvent* >(event);
    if (ev)
    {
        if (ev->devNofity == uvs_dev_changed)
        {
            if (!dev)
            {
                dev.DeviceOpen(ev->devInfo);
                dev.DeviceStart();
                previewStart();
            }
        }
        else if (dev)
        { // dev closed
            if (dev.m_DevObj == ev->devObj)
            {
                previewStop();
                dev.DeviceClose();
            }
        }
    }
}

void Dialog::previewStart(void)
{
    if (dev) dev.PreviewStart(reinterpret_cast< HWND >(ui->video->winId()));
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

void Dialog::on_browse_clicked()
{
    auto str = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Images (*.png *.bmp *.jpg);;All Files(*.*)"));
    if (!str.isEmpty())
    {
        ui->image->setText(str);
    }
}

void Dialog::on_backcr_clicked()
{
    auto cr = QColorDialog::getColor(color, this);
    if (cr.isValid()) color = cr;
}

void Dialog::on_apply_clicked()
{
    auto str = ui->image->text();

    /* Valid after dev reopen */
    if (str.isEmpty())
    {
        CDevSDK::SetNosignalImage(Q_NULLPTR); /* No signal image disabled */
    }
    else
    {
        uvs_draw_mode_e m = ui->mode->currentIndex() == 0 ? uvs_draw_stretch : uvs_draw_center;
#ifdef WIN32
        COLORREF cr = RGB(color.red(), color.green(), color.blue());
#else
        uvs_color_t c;
        c.r = static_cast< uint8_t >(color.red());
        c.g = static_cast< uint8_t >(color.green());
        c.b = static_cast< uint8_t >(color.blue());
        c.alpha = 255;
        COLORREF cr = &c;
#endif
        CDevSDK::SetNosignalImage(_string(str), m, cr);
    }
}
