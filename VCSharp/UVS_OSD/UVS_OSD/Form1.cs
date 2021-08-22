using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using UVS_Media;

namespace UVS_OSD
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void OnLoad(object sender, EventArgs e)
        {
            textfont = new Font("Arail", 24);
            textcolor = Color.FromArgb(0, 0, 255);
            bkcolor = Color.FromArgb(255, 255, 255);

            int r;
            dev = new Dev(0, -1, out r);
            if (dev)
            {
                dev.DeviceStart();
                dev.GetVideoProperty(out format);
                dev.PreviewStart(video.Handle);
            }

            date.SelectedIndex = 0;
            week.SelectedIndex = 0;
            hours.SelectedIndex = 0;
            rectstyle.SelectedIndex = 0;
            ellipsestyle.SelectedIndex = 0;
            osd.SelectedIndex = 0;
            control.SelectedIndex = 0;

            timer1.Enabled = true;
        }

        private void OnClosed(object sender, FormClosedEventArgs e)
        {
            dev.Dispose();
        }

        private void GetFontInfo(ref Dev.FontInfo info)
        {
            info.szFontName = textfont.Name;
            info.fontPointSize = Convert.ToInt32(textfont.SizeInPoints);
            info.stringFormat = Dev.uvs_string_format_regular;
            info.textColor = Dev.ToCOLORREF(textcolor.ToArgb());
            info.textOpacity = 255;
            info.textBkColor = Dev.ToCOLORREF(bkcolor.ToArgb());
            info.textBkOpacity = 128;
            info.fontStyle = Dev.uvs_font_style_cleartype; /* for LCD Display */
            if (textfont.Bold) info.fontStyle |= Dev.uvs_font_style_bold;
            if (textfont.Italic) info.fontStyle |= Dev.uvs_font_style_italic;
            if (textfont.Strikeout) info.fontStyle |= Dev.uvs_font_style_strikeout;
            if (textfont.Underline) info.fontStyle |= Dev.uvs_font_style_underline;
        }

        private void DisableOSD(int index)
        {
            int dummy = 0;
            dev.VideoOSDControl(index, Dev.uvs_osd_delete, ref dummy, ref dummy);

            /* OSD disable / enable for reused */
            // int en = 0; dev.VideoOSDControl(index, Dev.uvs_osd_delete, ref en, ref dummy);
        }

        private void OnTimer(object sender, EventArgs e)
        {
            if (dev)
            {
                int x = 0;
                int y = 0;
                int width = 0;
                int height = 0;
                int dummy = 0;
                switch (osdctrl)
                {
                    case ctrlmove:
                    case ctrlscroll0:
                    case ctrlscroll1:
                        // get current position
                        int r = dev.VideoOSDControl(osdindex, Dev.uvs_osd_get_position, ref x, ref y);
                        if (r == Dev.UVS_OK)
                        {
                            r = dev.VideoOSDControl(osdindex, Dev.uvs_osd_get_size, ref width, ref dummy);
                            int pos = 0;
                            if (osdctrl == ctrlscroll0 || osdctrl == ctrlscroll1)
                            {
                                dev.VideoOSDControl(osdindex, Dev.uvs_osd_get_clip_position, ref pos, ref dummy);
                            }

                            if (x + width > pos)
                            {
                                // move left
                                x -= 8;
                            }
                            else
                            {
                                // right side beginning
                                x = osdctrl == ctrlmove ? format.videoWidth : pos + width;
                            }

                            dev.VideoOSDControl(osdindex, Dev.uvs_osd_set_position, ref x, ref y);
                        }
                        break;

                    case ctrlrect:
                        r = dev.VideoOSDControl(osdindex, Dev.uvs_osd_get_clip_size, ref width, ref height);
                        if (r == Dev.UVS_OK)
                        {
                            if (width > 0 && height > 0)
                            {
                                // reduce clip size
                                width = width * 9 / 10;
                                height = height * 9 / 10;
                            }
                            else
                            {
                                dev.VideoOSDControl(osdindex, Dev.uvs_osd_get_size, ref width, ref height);
                            }

                            width = (width + 1) & ~1; /* width must be even */
                            r = dev.VideoOSDControl(osdindex, Dev.uvs_osd_set_clip_size, ref width, ref height);
                        }
                        break;

                    case ctrlfade:
                        int opacity = 0;
                        int bkopacity = 0;
                        r = dev.VideoOSDControl(osdindex, Dev.uvs_osd_get_opacity, ref opacity, ref bkopacity);
                        if (r == Dev.UVS_OK)
                        {
                            if (opacity > 20)
                            {
                                opacity = opacity * 9 / 10;
                                bkopacity = bkopacity * 9 / 10;
                            }
                            else
                            {
                                opacity = 255;
                                bkopacity = 255;
                            }

                            r = dev.VideoOSDControl(osdindex, Dev.uvs_osd_set_opacity, ref opacity, ref bkopacity);
                        }
                        break;
                }
            }
        }

        private void OnTimeosd(object sender, EventArgs e)
        {
            if (dev)
            {
                if (timeosd.Checked)
                {
                    string[] datearray = new string[] { "%Y-%M-%D", "%M-%D-%Y", "%D-%M-%Y", "%N %D %Y", "%n %D %Y" };
                    string[] weekarray = new string[] { "", " %W", " %w" };
                    string[] hourarray = new string[] { " %H:%m:%s", " %h:%m:%s", " %h:%m:%s %t" };

                    string format = datearray[date.SelectedIndex];
                    format += weekarray[week.SelectedIndex];
                    format += hourarray[hours.SelectedIndex];

                    var info = new Dev.FontInfo();
                    GetFontInfo(ref info);
                    dev.SetTimeOSD(timeindex, 20, 20, format, ref info);
                }
                else
                {
                    DisableOSD(timeindex);
                }
            }
        }

        private void OnTextosd(object sender, EventArgs e)
        {
            if (dev)
            {
                if (textosd.Checked)
                {
                    if (text.Text != string.Empty)
                    {
                        var info = new Dev.FontInfo();
                        GetFontInfo(ref info);

                        int width = 0;
                        int height = 0;
                        if (multiline.Checked)
                        {
                            width = 200;
                            height = 100;
                            info.stringFormat = Dev.uvs_string_rect_multiple_lines;
                        }

                        dev.SetTextOSD(textindex, 20, 100, width, height, text.Text, ref info);
                    }
                }
                else
                {
                    DisableOSD(textindex);
                }
            }
        }

        private void OnImageosd(object sender, EventArgs e)
        {
            if (dev)
            {
                if (imgosd.Checked)
                {
                    if (image.Text != string.Empty)
                    {
                        dev.SetImageOSD(imageindex, 20, 160, 0, 0, 192, image.Text);
                    }
                }
                else
                {
                    DisableOSD(imageindex);
                }
            }
        }

        private void OnRectosd(object sender, EventArgs e)
        {
            if (dev)
            {
                if (rectosd.Checked)
                {
                    var info = new Dev.StyleInfo();
                    info.lineSize = 4;
                    info.edgeColor = Dev.ToCOLORREF(Color.FromArgb(255, 0, 0).ToArgb());
                    info.edgeOpacity = 255;
                    info.fillColor = Dev.ToCOLORREF(bkcolor.ToArgb());
                    info.fillOpacity = 128;

                    int[] style = new int[] { Dev.uvs_dash_style_solid, Dev.uvs_dash_style_dash,
                                              Dev.uvs_dash_style_dot, Dev.uvs_dash_style_dash_dot };
                    info.dashStyle = style[rectstyle.SelectedIndex];
                    dev.SetRectOSD(rectindex, 20, 200, 200, 200, ref info);
                }
                else
                {
                    DisableOSD(rectindex);
                }
            }
        }

        private void OnEllipseosd(object sender, EventArgs e)
        {
            if (dev)
            {
                if (ellipseosd.Checked)
                {
                    var info = new Dev.StyleInfo();
                    info.lineSize = 4;
                    info.edgeColor = Dev.ToCOLORREF(Color.FromArgb(255, 0, 0).ToArgb());
                    info.edgeOpacity = 255;
                    info.fillColor = Dev.ToCOLORREF(bkcolor.ToArgb());
                    info.fillOpacity = 128;

                    int[] style = new int[] { Dev.uvs_dash_style_solid, Dev.uvs_dash_style_dash,
                                              Dev.uvs_dash_style_dot, Dev.uvs_dash_style_dash_dot };
                    info.dashStyle = style[ellipsestyle.SelectedIndex];
                    dev.SetEllipseOSD(ellipseindex, 300, 200, 200, 200, ref info);
                }
                else
                {
                    DisableOSD(ellipseindex);
                }
            }
        }

        private void OnLineosd(object sender, EventArgs e)
        {
            if (dev)
            {
                if (lineosd.Checked)
                {
                    const int linesize = 4;
                    const int rectx = 20;
                    const int recty = 420;
                    const int rectwidth = 800;
                    const int rectheight = 400;

                    var info = new Dev.LineInfo();
                    info.lineSize = linesize;
                    info.lineColor = Dev.ToCOLORREF(Color.FromArgb(0, 255, 255).ToArgb());
                    info.lineOpacity = 255;

                    // line draw rect
                    int x0, y0, x1, y1;

                    /* draw horiz line0 */
                    x0 = rectx;
                    x1 = rectx + rectwidth;
                    y0 = y1 = recty;
                    dev.SetLineOSD(lineindex0, x0, y0, x1, y1, ref info);

                    /* draw horiz line1 */
                    y0 = y1 = recty + rectheight - linesize;
                    dev.SetLineOSD(lineindex1, x0, y0, x1, y1, ref info);

                    /* draw vertical line0 */
                    x0 = x1 = rectx;
                    y0 = recty + linesize;
                    y1 = recty + rectheight - linesize;
                    dev.SetLineOSD(lineindex2, x0, y0, x1, y1, ref info);

                    /* draw vertical line1 */
                    x0 = x1 = rectx + rectwidth - linesize;
                    dev.SetLineOSD(lineindex3, x0, y0, x1, y1, ref info);
                }
                else
                {
                    DisableOSD(lineindex0);
                    DisableOSD(lineindex1);
                    DisableOSD(lineindex2);
                    DisableOSD(lineindex3);
                }
            }
        }

        private void OnMultiLine(object sender, EventArgs e)
        {
            if (textosd.Checked) OnTextosd(sender, e);
        }

        private const int timeindex = Dev.uvs_time_osd_index_preview_enc; // Dev.uvs_time_osd_index_preview_only;
        private const int baseindex = Dev.uvs_osd_index_preview_only;
        private const int textindex = baseindex + 1;
        private const int imageindex = baseindex + 2;
        private const int rectindex = baseindex + 3;
        private const int ellipseindex = baseindex + 4;
        private const int lineindex0 = baseindex + 5;
        private const int lineindex1 = baseindex + 6;
        private const int lineindex2 = baseindex + 7;
        private const int lineindex3 = baseindex + 8;

        private const int ctrlnone = 0;
        private const int ctrlblink = 1;
        private const int ctrlmove = 2;
        private const int ctrlscroll0 = 3;
        private const int ctrlscroll1 = 4;
        private const int ctrlrect = 5;
        private const int ctrlfade = 6;

        private Dev dev;
        private Dev.VideoFormat format;
        private Font textfont;
        private Color textcolor;
        private Color bkcolor;

        private int osdindex;
        private int osdctrl;

        private void OnFont(object sender, EventArgs e)
        {
            fontDialog1.Font = textfont;
            fontDialog1.Color = textcolor;
            if (fontDialog1.ShowDialog() == DialogResult.OK)
            {
                textfont = fontDialog1.Font;
            }
        }

        private void OnBrowse(object sender, EventArgs e)
        {
            openFileDialog1.FileName = "";
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                image.Text = openFileDialog1.FileName;
            }
        }

        private void OnDate(object sender, EventArgs e)
        {
            if (timeosd.Checked) OnTimeosd(sender, e);
        }

        private void OnWeek(object sender, EventArgs e)
        {
            if (timeosd.Checked) OnTimeosd(sender, e);
        }

        private void OnHours(object sender, EventArgs e)
        {
            if (timeosd.Checked) OnTimeosd(sender, e);
        }

        private void OnRectstyle(object sender, EventArgs e)
        {
            if (rectosd.Checked) OnRectosd(sender, e);
        }

        private void OnEllipsestyle(object sender, EventArgs e)
        {
            if (ellipseosd.Checked) OnEllipseosd(sender, e);
        }

        private void OnSelect(object sender, EventArgs e)
        {
            if (dev)
            {
                int show = 0;
                int hide = 0;
                int width = 0;
                int height = 0;
                switch (osdctrl)
                {
                    case ctrlblink:
                        // clear show / hide period
                        dev.VideoOSDControl(osdindex, Dev.uvs_osd_set_blink, ref show, ref hide);
                        break;

                    case ctrlscroll0:
                    case ctrlscroll1:
                    case ctrlmove:
                        // restore clip
                        dev.VideoOSDControl(osdindex, Dev.uvs_osd_set_clip_size, ref width, ref height);
                        break;
                }

                var index = new int[] { timeindex, textindex, imageindex, rectindex, ellipseindex };
                osdindex = index[osd.SelectedIndex];
                osdctrl = control.SelectedIndex;
                switch (osdctrl)
                {
                    case ctrlblink:
                        show = 600;
                        hide = 400; // milli sec
                        dev.VideoOSDControl(osdindex, Dev.uvs_osd_set_blink, ref show, ref hide);
                        break;

                    case ctrlscroll0:
                    case ctrlscroll1:
                    case ctrlrect:
                        int r = dev.VideoOSDControl(osdindex, Dev.uvs_osd_get_size, ref width, ref height);
                        if (r == Dev.UVS_OK)
                        {
                            int x = 0;
                            int y = 0;
                            dev.VideoOSDControl(osdindex, Dev.uvs_osd_get_position, ref x, ref y);

                            // move to center
                            x = format.videoWidth > width ? (format.videoWidth - width) / 2 : 0;
                            /* x & width must be even */
                            x &= ~1;
                            width = (width + 1) & ~1;

                            dev.VideoOSDControl(osdindex, Dev.uvs_osd_set_position, ref x, ref y);
                            dev.VideoOSDControl(osdindex, Dev.uvs_osd_set_clip_position, ref x, ref y);
                            dev.VideoOSDControl(osdindex, Dev.uvs_osd_set_clip_size, ref width, ref height);

                            if (osdctrl == ctrlscroll1)
                            {
                                // create background
                                var info = new Dev.StyleInfo();
                                info.lineSize = 2;
                                info.dashStyle = Dev.uvs_dash_style_solid;
                                info.edgeColor = Dev.ToCOLORREF(Color.FromArgb(255, 255, 255).ToArgb());
                                info.edgeOpacity = 255;
                                info.fillColor = Dev.ToCOLORREF(Color.FromArgb(0, 255, 0).ToArgb());
                                info.fillOpacity = 128;
                                dev.SetRectOSD(baseindex, x, y, width, height, ref info);
                            }
                        }
                        break;
                }
            }
        }

        private void OnControl(object sender, EventArgs e)
        {
            OnSelect(sender, e);
        }
    }
}
