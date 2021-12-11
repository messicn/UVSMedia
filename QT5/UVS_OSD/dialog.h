#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <DevManager.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    const static int timeindex = uvs_time_osd_index_preview_only; // uvs_time_osd_index_preview_enc;
    const static int baseindex = uvs_osd_index_preview_only; // uvs_osd_index_preview_enc;
    const static int textindex = baseindex + 1;
    const static int imageindex = baseindex + 2;
    const static int rectindex = baseindex + 3;
    const static int ellipseindex = baseindex + 4;
    const static int lineindex0 = baseindex + 5;
    const static int lineindex1 = baseindex + 6;
    const static int lineindex2 = baseindex + 7;
    const static int lineindex3 = baseindex + 8;

    const static int none = 0;
    const static int blink = 1;
    const static int move = 2;
    const static int scroll0 = 3;
    const static int scroll1 = 4;
    const static int rect = 5;
    const static int fade = 6;

protected:
    void showEvent(QShowEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

    void currentFont(uvs_font_info_tX &info);
    void disableOSD(int index);

private slots:
    void on_font_clicked();

    void on_browse_clicked();

    void on_timeosd_clicked(bool checked);

    void on_textosd_clicked(bool checked);

    void on_imageosd_clicked(bool checked);

    void on_rectosd_clicked(bool checked);

    void on_elipseosd_clicked(bool checked);

    void on_lineosd_clicked(bool checked);

    void on_multi_clicked(bool checked);

    void timeosd();

    void on_image_textChanged(const QString &arg1);

    void on_rectstyle_currentIndexChanged(int index);

    void on_elipsestyle_currentIndexChanged(int index);

    void on_osd_currentIndexChanged(int index);

    void on_control_currentIndexChanged(int index);

private:
    Ui::Dialog *ui;
    CDevSDK dev;
    uvs_video_format_t format;
    int timer;
    QFont font;
    int osdindex = 0;
    int osdctrl = 0;
};
#endif // DIALOG_H
