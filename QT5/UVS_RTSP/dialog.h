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

    bool serverCreate();
    void serverDestroy();

    void fileClose();

    const QString stringFromURL(uvs_url_tX &url);

private slots:
    void on_rtsplive_clicked();

    void on_browse_clicked();

    void on_rtspfile_clicked();

private:
    Ui::Dialog *ui;
    CDevSDK dev;
    USHORT port = 0;
    bool live = false;
    CFileRTSP *rtsp = Q_NULLPTR;
};
#endif // DIALOG_H
