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
    void timerEvent(QTimerEvent *event) override;

    void addTitle(const QString &name, int beginning=0, int duration=1);

private slots:
    void on_dir_textChanged(const QString &arg1);

    void on_browse_clicked();

    void on_font_clicked();

    void on_open_clicked();

    void on_repair_clicked();

    void on_merge_clicked();

    void on_cut_clicked();

    void on_add_clicked();

    void on_save_clicked();

private:
    Ui::Dialog *ui;
    QFont font;
    int timer;

    bool repair = false;
    bool merge = false;
    bool cut = false;
    bool title = false;
};
#endif // DIALOG_H
