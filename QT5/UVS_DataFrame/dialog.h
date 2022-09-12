#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "DevManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class CMyPreview;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    static void framePrint(const uvs_frame_info_t &frame);
    static void CALLBACK frameCallback(uvsobj_handle obj, const uvs_frame_info_t *frame, void *userData);

protected:
    void showEvent(QShowEvent *event) override;
    void getFrameConvertParam(uvs_frame_convert_t &convert);

private slots:
    void on_vcopy_clicked();

    void on_snapshot_clicked();

    void on_encode_clicked();

    void on_vcallback_clicked();

    void on_vlock_clicked();

    void on_acopy_clicked();

    void on_acallback_clicked();

    void on_alock_clicked();

private:
    Ui::Dialog *ui;
    CDevSDK dev;

    CMyPreview *preview = nullptr;

    bool audioCallback = false;
    bool videoCallback = false;
    bool encodeCallback = false;
};
#endif // DIALOG_H
