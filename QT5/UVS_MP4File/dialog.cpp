#include "dialog.h"
#include "ui_dialog.h"

#include <QFileDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <QStandardItemModel>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , font("Arial", 36)
{
    ui->setupUi(this);
    ui->files->setEditTriggers(QTreeView::NoEditTriggers);
    ui->files->setSelectionBehavior(QTreeView::SelectRows);
    ui->files->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->files->header()->setDefaultSectionSize(360);
    ui->files->header()->setStretchLastSection(true);
    ui->text->setText("Title");

    auto u = new QIntValidator(0, 3600000, this);
    auto v = new QIntValidator(-1, 3600000, this);
    ui->filebegin->setValidator(u);
    ui->filebegin->setText("0");
    ui->fileend->setValidator(v);
    ui->fileend->setText("-1");
    ui->titlebegin->setValidator(u);
    ui->titlebegin->setText("0");
    ui->titletime->setValidator(u);
    ui->titletime->setText("3000");

    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    timer = startTimer(1000);
}

Dialog::~Dialog()
{
    killTimer(timer);
    delete ui;
}

void Dialog::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    int progress;
    if (repair) CDevSDK::MP4FileGetRepairProgress(progress);

    if (merge) CDevSDK::MP4FileGetMergeProgress(progress);

    if (cut) CDevSDK::MP4FileGetCutProgress(progress);

    if (title) CDevSDK::MP4FileGetTitleProgress(progress);

    if (repair || merge || cut || title)
    {
        if (progress >= 0) ui->progressBar->setValue(progress);

        if (progress == -1 || progress == 100)
        {
            if (repair) repair = false;
            if (merge) merge = false;
            if (cut) cut = false;
            if (title) title = false;

            setEnabled(true);
            QMessageBox::information(this, tr("Message"), progress == 100 ? "Operator succeed!" : "Operator failed!");
        }
    }
}

void Dialog::addTitle(const QString &name, int beginning, int duration)
{
    auto index = ui->files->currentIndex();
    if (index.isValid())
    {
        uvs_mp4_file_status_t status;
        auto str = ui->files->model()->itemData(index.sibling(index.row(), 0)).value(0).toString();
        if (CDevSDK::MP4FileGetStatus(_string(str), status) == UVS_OK)
        {
            uvs_mp4_file_title_tX param;
            memset(&param, 0, sizeof(uvs_mp4_file_title_tX));

            QByteArrayList array;
            auto text = ui->text->text();
            if (!text.isEmpty())
            {
#ifdef UNICODE
                param.szTitleText = _string(text);
#else
                array.append(text.toLocal8Bit());
                param.szTitleText = array.back().data();
#endif

#ifdef WIN32
                _tcscpy(param.textFont.szFontName, _string(font.family()));
                int style = uvs_font_style_cleartype;
#else
                QStringList fonts("/usr/share/fonts/truetype/Gargi/Gargi.ttf");
                fonts << "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";

                foreach (const QString& s, fonts) {
                    QFileInfo file(s);
                    if (file.isFile())
                    {
                        _tcscpy(param.textFont.szFontName, _string(s)); // Copy full path directly
                        break;
                    }
                }

                int style = uvs_font_style_regular;
#endif
                if (font.bold()) style |= uvs_font_style_bold;
                if (font.italic()) style |= uvs_font_style_italic;
                if (font.underline()) style |= uvs_font_style_underline;
                if (font.strikeOut()) style |= uvs_font_style_strikeout;
                param.textFont.fontStyle = static_cast< uvs_font_style_e >(style);
                param.textFont.fontPointSize = font.pointSize();

#ifdef WIN32
                param.textFont.textColor = RGB(0, 0, 255);
                param.textFont.textOpacity = 255;
                param.textFont.textBkColor = RGB(255, 255, 255);
                param.textFont.textBkOpacity = 128;
#else
                param.textFont.textColor.r = 0;
                param.textFont.textColor.g = 0;
                param.textFont.textColor.b = 255;
                param.textFont.textColor.alpha = 255;
                param.textFont.textBkColor.r = 255;
                param.textFont.textBkColor.g = 255;
                param.textFont.textBkColor.b = 255;
                param.textFont.textBkColor.alpha = 128;
#endif
            }

            auto image = ui->image->text();
            if (!image.isEmpty())
            {
#ifdef UNICODE
                param.szTitleImageFile = _string(image);
#else
                array.append(image.toLocal8Bit());
                param.szTitleImageFile = array.back().data();
#endif
                param.imageOpacity = 128;
            }

            param.x = param.y = 0;
            param.width = status.videoWidth;
            param.height = status.videoHeight;

            if (CDevSDK::MP4FileAddTitle(_string(str), beginning, &param, 1, duration, _string(name)) == UVS_OK)
            {
                setEnabled(false);
                ui->progressBar->setValue(0);
                title = true;
            }
            else
            {
                QMessageBox::information(this, tr("Message"), "Title add failed!");
            }
        }
    }
}

void Dialog::on_dir_textChanged(const QString &arg1)
{
    QDir dir(arg1);
    auto list = dir.entryList(QStringList("*.mp4"), QDir::Files);

    auto model = new QStandardItemModel(ui->files);
    model->setHorizontalHeaderLabels(QStringList("MP4 Files") << "Status");

    uvs_mp4_file_status_t status;
    for (const auto &name : list)
    {
        auto file = QDir::cleanPath(arg1 + QDir::separator() + name);
        QList<QStandardItem*> items;
        items.append(new QStandardItem(file));

        QString str;
        int r = CDevSDK::MP4FileGetStatus(_string(file), status);
        if (r == UVS_OK)
        {
            switch (status.audioCodec) {
            case uvs_audio_codec_MP3:
                str += "MP3/";
                break;

            case uvs_audio_codec_AAC:
                str += "AAC/";
                break;

            default:
                str += "None/";
                break;
            }

            switch (status.videoCodec) {
            case uvs_video_codec_hw_h264:
            case uvs_video_codec_intel_h264:
            case uvs_video_codec_nvidia_h264:
            case uvs_video_codec_sw_h264:
            case uvs_video_codec_sw_x264:
                str += "H.264(AVC) ";
                break;

            case uvs_video_codec_hw_h265:
            case uvs_video_codec_intel_h265:
            case uvs_video_codec_nvidia_h265:
                str += "H.265(HEVC) ";
                break;
            }

            str += QString::number(status.videoWidth);
            str += " x ";
            str += QString::number(status.videoHeight);
            str += " ";
            str += QString::number(status.videoDuration);
            str += "ms ";
            str += QString::number(status.videoFrameRate, 'f', 2);
            str += "fps";
        }
        else
        {
            str = "Needs To Repair";
        }

        items.append(new QStandardItem(str));
        model->appendRow(items);
    }

    auto m = ui->files->model();
    ui->files->setModel(model);
    delete m;
}

void Dialog::on_browse_clicked()
{
    auto str = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ".", QFileDialog::ShowDirsOnly);
    if (!str.isEmpty())
    {
        ui->dir->setText(str);
    }
}

void Dialog::on_font_clicked()
{
    bool ok;
    font = QFontDialog::getFont(&ok, font, this);
}

void Dialog::on_open_clicked()
{
    auto str = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Images (*.png *.bmp *.jpg);;All Files(*.*)"));
    if (!str.isEmpty())
    {
        ui->image->setText(str);
    }
}

void Dialog::on_repair_clicked()
{
    auto index = ui->files->currentIndex();
    if (index.isValid())
    {
        auto str = ui->files->model()->itemData(index.sibling(index.row(), 0)).value(0).toString();
        auto mp4 = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("MP4 Files (*.mp4)"));
        if (!(str.isEmpty() || mp4.isEmpty()))
        {
            if (QFileInfo(mp4).suffix().isEmpty()) mp4 += ".mp4";
            if (CDevSDK::MP4FileRepair(_string(str), _string(mp4)) == UVS_OK)
            {
                setEnabled(false);
                ui->progressBar->setValue(0);
                repair = true;
            }
        }
    }
}

void Dialog::on_merge_clicked()
{
    auto list = ui->files->selectionModel()->selectedRows();

#ifdef WIN32
    LPCTSTR files[128];
#else
    LPTSTR files[128];
#endif

#ifdef UNICODE
    QStringList array;
    int num = 0;
    for (const auto &index : list)
    {
        array.append(ui->files->model()->itemData(index.sibling(index.row(), 0)).value(0).toString());
        if (num < static_cast<int>(_countof(files))) files[num++] = _string(array.back());
    }
#else
    QByteArrayList array;
    int num = 0;
    for (const auto &index : list)
    {
        array.append(ui->files->model()->itemData(index.sibling(index.row(), 0)).value(0).toString().toLocal8Bit());
        if (num < static_cast<int>(_countof(files))) files[num++] = array.back().data();
    }
#endif

    if (num > 1)
    {
        auto mp4 = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("MP4 Files (*.mp4)"));
        if (!mp4.isEmpty())
        {
           if (QFileInfo(mp4).suffix().isEmpty()) mp4 += ".mp4";
           if (CDevSDK::MP4FileMerge(files, num, _string(mp4)) == UVS_OK)
           {
               setEnabled(false);
               ui->progressBar->setValue(0);
               merge = true;
           }
        }
    }
}

void Dialog::on_cut_clicked()
{
    auto index = ui->files->currentIndex();
    if (index.isValid())
    {
        bool ok;
        auto begin = ui->filebegin->text().toInt(&ok);
        if (ok)
        {
            auto end = ui->fileend->text().toInt(&ok);
            if (ok)
            {
                auto str = ui->files->model()->itemData(index.sibling(index.row(), 0)).value(0).toString();
                auto mp4 = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("MP4 Files (*.mp4)"));
                if (!(str.isEmpty() || mp4.isEmpty()))
                {
                    if (QFileInfo(mp4).suffix().isEmpty()) mp4 += ".mp4";
                    if (CDevSDK::MP4FileCut(_string(str), begin, end, _string(mp4)) == UVS_OK)
                    {
                        setEnabled(false);
                        ui->progressBar->setValue(0);
                        cut = true;
                    }
                }
            }
        }
    }
}

void Dialog::on_add_clicked()
{
    bool ok;
    auto begin = ui->titlebegin->text().toInt(&ok);
    if (ok)
    {
        auto dur = ui->titletime->text().toInt(&ok);
        if (ok)
        {
            auto mp4 = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("MP4 Files (*.mp4)"));
            if (!mp4.isEmpty())
            {
                if (QFileInfo(mp4).suffix().isEmpty()) mp4 += ".mp4";
                addTitle(mp4, begin, dur);
            }
        }
    }
}

void Dialog::on_save_clicked()
{
    auto image = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Images (*.png *.bmp *.jpg);;All Files(*.*)"));
    if (!image.isEmpty())
    {
        if (QFileInfo(image).suffix().isEmpty()) image += ".jpg";
        addTitle(image);
    }
}
