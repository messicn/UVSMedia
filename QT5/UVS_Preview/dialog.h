#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "DevManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

protected:
    void showEvent(QShowEvent *event) override;

#ifdef WIN32
    bool eventFilter(QObject *obj, QEvent *event) override;
#else
    static void eventCallback(uvsobj_handle obj, const uvs_sdl_event_t *event, void *userData);
    void customEvent(QEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    void moveDelay();
    bool alwaysOnTop();
#endif

    void enumDev(uvs_dev_type_e t, QStringList &s);
    void devStart(bool preview);
    void devClose();
    void previewStart();
    void previewStop();

    void devChanged();
    void videoMirror();

private slots:
    void on_vrenderer_currentIndexChanged(int index);

    void on_brightness_valueChanged(int value);

    void on_contrast_valueChanged(int value);

    void on_saturation_valueChanged(int value);

    void on_gamma_valueChanged(int value);

    void on_volume_valueChanged(int value);

    void on_balance_valueChanged(int value);

    void on_mute_stateChanged(int arg1);

    void on_fullsc_clicked();

    void on_zoomin_clicked();

    void on_freeze_clicked();

    void on_zoomout_clicked();

    void on_ontop_clicked();

private:
    Ui::Dialog *ui;
    CDevSDK dev;
#ifdef WIN32
    QPoint pos;
    QSize size;
#else
    int count = 0;
#endif
    bool zoomin = false;
    bool zoomout = false;
};
#endif // DIALOG_H
