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
    void timerEvent(QTimerEvent *event) override;

    void fileClose();

private slots:
    void on_rtmplive_clicked();

    void on_browse_clicked();

    void on_rtmpfile_clicked();

private:
    Ui::Dialog *ui;
    CDevSDK dev;
    CFileRTMP *rtmp = Q_NULLPTR;
    int timer;
    bool live = false;
};
#endif // DIALOG_H
