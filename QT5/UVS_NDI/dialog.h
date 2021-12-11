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

private slots:
    void on_stream_clicked();

private:
    Ui::Dialog *ui;
    CDevSDK dev;

    bool start = false;
};
#endif // DIALOG_H
