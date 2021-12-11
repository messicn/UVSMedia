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

    void getConfig(uvs_encode_config_t &config);

private slots:
    void on_mainrec_clicked();

    void on_subrec_clicked();

    void on_rec_clicked();

    void on_pause_clicked();

private:
    Ui::Dialog *ui;
    CDevSDK dev;

    int timer;
    bool rec = false;
    bool pause = false;
};
#endif // DIALOG_H
