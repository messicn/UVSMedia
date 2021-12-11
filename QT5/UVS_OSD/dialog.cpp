#include "dialog.h"
#include "ui_dialog.h"

#include <QFileDialog>
#include <QFontDialog>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , dev(0)
    , font("Arial", 36)
{
    ui->setupUi(this);
    ui->video->setStyleSheet("border:1px solid black");
    ui->date->addItems(QStringList("YY-MM-DD") << "MM-DD-YY" << "DD-MM-YY" << "MN DD YY" << "Mn DD YY");
    ui->week->addItems(QStringList("None") << "Full Name" << "Short Name");
    ui->time->addItems(QStringList("24 Hour") << "12 Hour" << "12 Hour AMPM");
    ui->text->setText("UVS Text Sample");
#ifdef WIN32
    ui->rectstyle->addItems(QStringList("Solid") << "Dash" << "Dot" << "Dash Dot");
    ui->elipsestyle->addItems(QStringList("Solid") << "Dash" << "Dot" << "Dash Dot");
#else
    ui->rectstyle->addItem("Solid");
    ui->elipsestyle->addItem("Solid");
#endif
    ui->osd->addItems(QStringList("Time OSD") << "Text OSD" << "Image OSD" << "Rect OSD" << "Ellipse OSD");
    ui->control->addItems(QStringList("None") << "Blink" << "Roll" << "Scroll 1" << "Scroll 2" << "Clear" << "Fade");

    connect(ui->date, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dialog::timeosd);
    connect(ui->week, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dialog::timeosd);
    connect(ui->time, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dialog::timeosd);

    if (dev)
    {
        dev.DeviceStart();
        dev.GetVideoProperty(format);
    }

    timer = startTimer(100);
}

Dialog::~Dialog()
{
    killTimer(timer);
    dev.DeviceClose();
    delete ui;
}

void Dialog::showEvent(QShowEvent *event)
{
    if (dev)
    {
        dev.PreviewStart(reinterpret_cast< HWND >(ui->video->winId()));
    }
    QDialog::showEvent(event);
}

void Dialog::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if (dev)
    {
        if (osdctrl == move || osdctrl == scroll0 || osdctrl == scroll1)
        {
            int x, width;
            int r = dev.VideoOSDControl(osdindex, uvs_osd_get_position, &x);
            if (r == UVS_OK)
            {
                r = dev.VideoOSDControl(osdindex, uvs_osd_get_size, &width);
                if (r == UVS_OK)
                {
                    int pos = 0;
                    if (osdctrl == scroll0 || osdctrl == scroll1)
                    {
                        dev.VideoOSDControl(osdindex, uvs_osd_get_clip_position, &pos);
                    }

                    if (x + width > pos)
                    {
                        /* move left */
                        x -= 4;
                    }
                    else
                    {
                        /* right beginning */
                        x = osdctrl == move ? format.videoWidth : pos + width;
                    }

                    dev.VideoOSDControl(osdindex, uvs_osd_set_position, &x);
                }
            }
        }
        else if (osdctrl == rect)
        {
            int width, height;
            int r = dev.VideoOSDControl(osdindex, uvs_osd_get_clip_size, &width, &height);
            if (r == UVS_OK)
            {
                if (width > 0 && height > 0)
                {
                    /* reduce size */
                    width *= 0.9;
                    height *= 0.9;
                }
                else
                {
                    dev.VideoOSDControl(osdindex, uvs_osd_get_size, &width, &height);
                }

                width = (width + 1) & ~1; /* width must be even */
                dev.VideoOSDControl(osdindex, uvs_osd_set_clip_size, &width, &height);
            }
        }
        else if (osdctrl == fade)
        {
            int opacity, bkopacity, r;
        #ifdef WIN32
            r = dev.VideoOSDControl(osdindex, uvs_osd_get_opacity, &opacity, &bkopacity);
        #else
            uvs_color_t color, bkcolor;
            if (imageindex == osdindex)
            {
                r = dev.VideoOSDControl(osdindex, uvs_osd_get_opacity, &opacity, &bkopacity);
            }
            else
            {
                r = dev.VideoOSDControl(osdindex, uvs_osd_get_color, &color, &bkcolor);
                opacity = color.alpha;
                bkopacity = bkcolor.alpha;
            }
        #endif

            if (r == UVS_OK)
            {
                if (opacity > 20)
                {
                    opacity *= 0.9;
                    bkopacity *= 0.9;
                }
                else
                {
                    opacity = 255;
                    bkopacity = 128;
                }

            #ifdef WIN32
                dev.VideoOSDControl(osdindex, uvs_osd_set_opacity, &opacity, &bkopacity);
            #else
                if (imageindex == osdindex)
                {
                    dev.VideoOSDControl(osdindex, uvs_osd_set_opacity, &opacity, &bkopacity);
                }
                else
                {
                    color.alpha = static_cast< uint8_t >(opacity);
                    bkcolor.alpha = static_cast< uint8_t >(bkopacity);
                    dev.VideoOSDControl(osdindex, uvs_osd_set_color, &color, &bkcolor);
                }
            #endif
            }
        }
    }
}

void Dialog::currentFont(uvs_font_info_tX &info)
{
    memset(&info, 0, sizeof(uvs_font_info_tX));

#ifdef WIN32
    _tcscpy(info.szFontName, _string(font.family()));
    int style = uvs_font_style_cleartype;
#else
    QStringList fonts("/usr/share/fonts/truetype/Gargi/Gargi.ttf");
    fonts << "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";

    foreach (const QString& str, fonts) {
        QFileInfo file(str);
        if (file.isFile())
        {
            _tcscpy(info.szFontName, _string(str)); // Copy full path directly
            break;
        }
    }
    
    int style = uvs_font_style_regular;
#endif
    if (font.bold()) style |= uvs_font_style_bold;
    if (font.italic()) style |= uvs_font_style_italic;
    if (font.underline()) style |= uvs_font_style_underline;
    if (font.strikeOut()) style |= uvs_font_style_strikeout;
    info.fontStyle = static_cast< uvs_font_style_e >(style);
    info.fontPointSize = font.pointSize();

#ifdef WIN32
    info.textColor = RGB(0, 0, 255);
    info.textOpacity = 255;
#else
    info.textColor.r = 0;
    info.textColor.g = 0;
    info.textColor.b = 255;
    info.textColor.alpha = 255;
#endif
}

void Dialog::disableOSD(int index)
{
    dev.VideoOSDControl(index, uvs_osd_delete);

    /* OSD disable(en=0) / enable(en=1) for reused */
    //int en = 0; dev.VideoOSDControl(index, uvs_osd_enable, &en);
}

void Dialog::on_font_clicked()
{
    bool ok;
    font = QFontDialog::getFont(&ok, font, this);
}

void Dialog::on_browse_clicked()
{
    auto str = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Images (*.png *.bmp *.jpg);;All Files(*.*)"));
    if (!str.isEmpty())
    {
        ui->image->setText(str);
    }
}

void Dialog::on_timeosd_clicked(bool checked)
{
    if (dev)
    {
        if (checked)
        {
            /* %M month, %D month of day, %H 24 hours, %h 12 hours, %m minute, %s second, %Y year,
             * %t AM/PM, %N month name, %n month short name, %W week name, %w week short name, %% % */
            static QStringList date(QStringList("%Y-%M-%D") << "%M-%D-%Y" << "%D-%M-%Y" << "%N %D %Y" << "%n %D %Y");
            static QStringList week(QStringList("") << " %W" << " %w");
            static QStringList time(QStringList(" %H:%m:%s") << " %h:%m:%s" << " %h:%m:%s %t");

            QString str = date[ui->date->currentIndex()];

            str += week[ui->week->currentIndex()];

            str += time[ui->time->currentIndex()];

            uvs_font_info_tX info;
            currentFont(info);
            dev.SetTimeOSD(timeindex, 20, 20, _string(str), info);
        }
        else
        {
            disableOSD(timeindex);
        }
    }
}

void Dialog::on_textosd_clicked(bool checked)
{
    if (dev)
    {
        if (checked)
        {
            auto str = ui->text->text();
            if (!str.isEmpty())
            {
                uvs_font_info_tX info;
                currentFont(info);
                int width = 0;
                int height = 0;
                if (ui->multi->checkState() == Qt::Checked)
                {
                    width = 200;
                    height = 100;
                    info.stringFormat = uvs_string_rect_multiple_lines;
                }
                dev.SetTextOSD(textindex, 20, 100, width, height, _string(str), info);
            }
        }
        else
        {
            disableOSD(textindex);
        }
    }
}

void Dialog::on_imageosd_clicked(bool checked)
{
    if (dev)
    {
        if (checked)
        {
            auto str = ui->image->text();
            if (!str.isEmpty())
            {
                dev.SetImageOSD(imageindex, 20, 160, 0, 0, 192, _string(str));
            }
        }
        else
        {
            disableOSD(imageindex);
        }
    }
}

void Dialog::on_rectosd_clicked(bool checked)
{
    if (dev)
    {
        if (checked)
        {
            uvs_style_info_t info;
            memset(&info, 0, sizeof(uvs_style_info_t));
            info.lineSize = 4;
#ifdef WIN32
            info.edgeColor = RGB(255, 0, 0);
            info.fillColor = RGB(255, 255, 255);
            info.edgeOpacity = 255;
            info.fillOpacity = 128;

            switch (ui->rectstyle->currentIndex()) {
            case 0:
                info.dashStyle = uvs_dash_style_solid;
                break;

            case 1:
                info.dashStyle = uvs_dash_style_dash;
                break;

            case 2:
                info.dashStyle = uvs_dash_style_dot;
                break;

            case 3:
                info.dashStyle = uvs_dash_style_dash_dot;
                break;

            default:
                break;
            }
#else
            info.edgeColor.r = 255;
            info.edgeColor.g = 0;
            info.edgeColor.b = 0;
            info.edgeColor.alpha = 255;
            info.fillColor.r = 255;
            info.fillColor.g = 255;
            info.fillColor.b = 255;
            info.fillColor.alpha = 128;
#endif
            dev.SetRectOSD(rectindex, 20, 200, 200, 200, info);
        }
        else
        {
            disableOSD(rectindex);
        }
    }
}

void Dialog::on_elipseosd_clicked(bool checked)
{
    if (dev)
    {
        if (checked)
        {
            uvs_style_info_t info;
            memset(&info, 0, sizeof(uvs_style_info_t));
            info.lineSize = 4;
#ifdef WIN32
            info.edgeColor = RGB(255, 0, 0);
            info.fillColor = RGB(255, 255, 255);
            info.edgeOpacity = 255;
            info.fillOpacity = 128;

            switch (ui->elipsestyle->currentIndex()) {
            case 0:
                info.dashStyle = uvs_dash_style_solid;
                break;

            case 1:
                info.dashStyle = uvs_dash_style_dash;
                break;

            case 2:
                info.dashStyle = uvs_dash_style_dot;
                break;

            case 3:
                info.dashStyle = uvs_dash_style_dash_dot;
                break;

            default:
                break;
            }
#else
            info.edgeColor.r = 255;
            info.edgeColor.g = 0;
            info.edgeColor.b = 0;
            info.edgeColor.alpha = 255;
            info.fillColor.r = 255;
            info.fillColor.g = 255;
            info.fillColor.b = 255;
            info.fillColor.alpha = 128;
#endif
            dev.SetEllipseOSD(ellipseindex, 300, 200, 200, 200, info);
        }
        else
        {
            disableOSD(ellipseindex);
        }
    }
}

void Dialog::on_lineosd_clicked(bool checked)
{
    if (dev)
    {
        const static int linesize = 4;
        const static int rectx = 20;
        const static int recty = 420;
        const static int rectwidth = 800;
        const static int rectheight = 400;

        do {
            int en = checked ? 1 : 0;
            int r = dev.VideoOSDControl(lineindex0, uvs_osd_enable, &en);
            if (r != UVS_OK) break;

            r = dev.VideoOSDControl(lineindex1, uvs_osd_enable, &en);
            if (r != UVS_OK) break;

            r = dev.VideoOSDControl(lineindex2, uvs_osd_enable, &en);
            if (r != UVS_OK) break;

            r = dev.VideoOSDControl(lineindex3, uvs_osd_enable, &en);
            if (r != UVS_OK) break;

            return;
        } while(0);

        if (checked)
        {
            uvs_line_info_t info;
            memset(&info, 0, sizeof(uvs_line_info_t));
            info.lineSize = linesize;
#ifdef WIN32
            info.lineColor = RGB(0, 255, 255);
            info.lineOpacity = 255;
#else
            info.lineColor.r = 0;
            info.lineColor.g = 255;
            info.lineColor.b = 255;
            info.lineColor.alpha = 255;
#endif
            int x0, y0, x1, y1;

            /* draw horiz line0 */
            x0 = rectx;
            x1 = rectx + rectwidth;
#ifdef WIN32
            y0 = y1 = recty;
#else
            /* draw line align middle */
            y0 = y1 = recty + linesize / 2;
#endif
            dev.SetLineOSD(lineindex0, x0, y0, x1, y1, info);

            /* draw horiz line1 */
#ifdef WIN32
            y0 = y1 = recty + rectheight - linesize;
#else
            /* draw line align middle */
            y0 = y1 = recty + rectheight - linesize / 2;
#endif
            dev.SetLineOSD(lineindex1, x0, y0, x1, y1, info);

            /* draw vertical line0 */
#ifdef WIN32
            x0 = x1 = rectx;
#else
            /* draw line align middle */
            x0 = x1 = rectx + (linesize - 1) / 2;
#endif
            y0 = recty + linesize;
            y1 = recty + rectheight - linesize;
            dev.SetLineOSD(lineindex2, x0, y0, x1, y1, info);

            /* draw vertical line1 */
#ifdef WIN32
            x0 = x1 = rectx + rectwidth - linesize;
#else
            /* draw line align middle */
            x0 = x1 = rectx + rectwidth - (linesize - 1) / 2;
#endif
            dev.SetLineOSD(lineindex3, x0, y0, x1, y1, info);
        }
    }
}

void Dialog::on_multi_clicked(bool checked)
{
    Q_UNUSED(checked);
    if (ui->textosd->checkState() == Qt::Checked) on_textosd_clicked(true);
}

void Dialog::timeosd()
{
    if (ui->timeosd->checkState() == Qt::Checked) on_timeosd_clicked(true);
}

void Dialog::on_image_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    if (ui->imageosd->checkState() == Qt::Checked) on_imageosd_clicked(true);
}

void Dialog::on_rectstyle_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    if (ui->rectosd->checkState() == Qt::Checked) on_rectosd_clicked(true);
}

void Dialog::on_elipsestyle_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    if (ui->elipseosd->checkState() == Qt::Checked) on_elipseosd_clicked(true);
}

void Dialog::on_osd_currentIndexChanged(int index)
{
    const static int array[] = { timeindex, textindex, imageindex, rectindex, ellipseindex };

    if (dev)
    {
        if (osdctrl == blink)
        {
            // clear show / hide period
            int ms = 0;
            dev.VideoOSDControl(osdindex, uvs_osd_set_blink, &ms, &ms);
        }
        else if (osdctrl == scroll0 || osdctrl == scroll1 || osdctrl == rect)
        {
            int sz = 0;
            dev.VideoOSDControl(osdindex, uvs_osd_set_clip_size, &sz, &sz);
            if (osdctrl == scroll1)
            {
                /* delete background rect */
                dev.VideoOSDControl(baseindex, uvs_osd_delete);
            }
        }

        osdindex = array[index];
        osdctrl = ui->control->currentIndex();
        if (osdctrl == blink)
        {
            int show = 800;
            int hide = 600;
            dev.VideoOSDControl(osdindex, uvs_osd_set_blink, &show, &hide);
        }
        else if (osdctrl == scroll0 || osdctrl == scroll1 || osdctrl == rect)
        {
            int width, height;
            int r = dev.VideoOSDControl(osdindex, uvs_osd_get_size, &width, &height);
            if (r == UVS_OK)
            {
                /* position center */
                int x = format.videoWidth > width ? (format.videoWidth - width) / 2 : 0;
                /* x & width must be even */
                x &= ~1;
                width = (width + 1) & ~1;

                dev.VideoOSDControl(osdindex, uvs_osd_set_position, &x);
                dev.VideoOSDControl(osdindex, uvs_osd_set_clip_position, &x);
                dev.VideoOSDControl(osdindex, uvs_osd_set_clip_size, &width, &height);

                if (osdctrl == scroll1)
                {
                    /* create background rect */
                    int y, r = dev.VideoOSDControl(osdindex, uvs_osd_get_position, Q_NULLPTR, &y);
                    if (r == UVS_OK)
                    {
                        uvs_style_info_t info;
                        memset(&info, 0, sizeof(uvs_style_info_t));
                        info.lineSize = 2;
            #ifdef WIN32
                        info.edgeColor = RGB(0, 0, 0);
                        info.fillColor = RGB(0, 255, 0);
                        info.edgeOpacity = 128;
                        info.fillOpacity = 128;
            #else
                        info.edgeColor.r = 0;
                        info.edgeColor.g = 0;
                        info.edgeColor.b = 0;
                        info.edgeColor.alpha = 128;
                        info.fillColor.r = 0;
                        info.fillColor.g = 255;
                        info.fillColor.b = 0;
                        info.fillColor.alpha = 128;
            #endif
                        dev.SetRectOSD(baseindex, x, y, width, height, info);
                    }
                }
            }
        }
    }
}

void Dialog::on_control_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    on_osd_currentIndexChanged(ui->osd->currentIndex());
}
