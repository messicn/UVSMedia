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
    static void CALLBACK devCallback(uvs_dev_notify_e notify, const uvs_dev_info_tX *info, uvsobj_handle obj, void *userData);

    void showEvent(QShowEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void customEvent(QEvent *event) override;

    void previewStart(void);
    void previewStop(void);

private slots:
    void on_browse_clicked();

    void on_backcr_clicked();

    void on_apply_clicked();

private:
    Ui::Dialog *ui;
    CDevSDK dev;
    int timer;
    QColor color;
};
#endif // DIALOG_H
