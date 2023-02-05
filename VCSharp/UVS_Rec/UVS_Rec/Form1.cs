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

namespace UVS_Rec
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void OnLoad(object sender, EventArgs e)
        {
            dev = new Dev();

            venc.SelectedIndex = aenc.SelectedIndex = 0;
            encusage.SelectedIndex = 0;
            encbitrate.SelectedIndex = maxbitrate.SelectedIndex = 0;
            crop.SelectedIndex = rc.SelectedIndex = 0;
            scale.SelectedIndex = scaleusage.SelectedIndex = 0;
            filedur.SelectedIndex = filesz.SelectedIndex = 0;

            maindir.Text = Application.StartupPath;

            // has audio capture ?
            var num = Dev.max_dev_num;
            var info = new Dev.DevInfo[num];
            Dev.uvs_enum_device(Dev.uvs_dev_audio_capture, info, ref num);
            aenc.Enabled = num > 0;
            dev.DeviceOpen(0, num > 0 ? 0 : -1);
            if (dev)
            {
                // init enc frame rate, default same as input
                Dev.VideoFormat format;
                dev.GetVideoProperty(out format);
                framerate.Items.Add("Default");
                framerate.Items.Add(string.Format("{0:F2}", format.frameRate / 2));
                framerate.SelectedIndex = 0;

                dev.DeviceStart();
                dev.PreviewStart(video.Handle);

                timer1.Enabled = true;
            }
        }

        private void OnClosed(object sender, FormClosedEventArgs e)
        {
            dev.Dispose();
        }

        private void OnTimer(object sender, EventArgs e)
        {
            string str = "";
            if (dev)
            {
                Dev.EncodeStatus es;
                if (dev.GetVideoEncodeStatus(0, out es) == Dev.UVS_OK)
                {
                    str = string.Format("Input Frames:{0} ({1:F2}fps)\nEncode Frames:{2} ({3:F2}fps)",
                                        es.inputFrames, es.inputFrameRate, es.encodeFrames, es.encodeFrameRate);
                }
            }
            status.Text = str;
        }

        private void OnMainBrowse(object sender, EventArgs e)
        {
            if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                maindir.Text = folderBrowserDialog1.SelectedPath;
            }
        }

        private void OnSubBrowse(object sender, EventArgs e)
        {
            if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                subdir.Text = folderBrowserDialog1.SelectedPath;
            }
        }

        private void OnStart(object sender, EventArgs e)
        {
            if (dev)
            {
                if (rec)
                {
                    dev.RecordStop(Dev.UVS_STREAM_ALL);
                    dev.EncodeStop(Dev.UVS_STREAM_ALL);
                    rec = false;
                    resume = false;
                    recpause.Text = "Rec Pause";
                }
                else
                {
                    int[] vcodec = new int[] { Dev.uvs_video_codec_intel_h264, Dev.uvs_video_codec_intel_h265,
                                               Dev.uvs_video_codec_nvidia_h264, Dev.uvs_video_codec_nvidia_h265,
                                               Dev.uvs_video_codec_sw_h264 };
                    int[] acodec = new int[] { Dev.uvs_audio_codec_none, Dev.uvs_audio_codec_AAC, Dev.uvs_audio_codec_MP3 };
                    int[] tusage = new int[] { Dev.uvs_target_usage_performance, Dev.uvs_target_usage_balance, Dev.uvs_target_usage_quality };
                    int[] rcmode = new int[] { Dev.uvs_video_rcmode_VBR, Dev.uvs_video_rcmode_CBR,
                                               Dev.uvs_video_rcmode_CQP, Dev.uvs_video_rcmode_AVBR };
                    int[] susage = new int[] { Dev.uvs_scale_usage_performance, Dev.uvs_scale_usage_balance,
                                               Dev.uvs_scale_usage_quality, Dev.uvs_scale_usage_high_quality };
                    int[] encKbps = new int[] { 4000, 8000, 10000 };
                    int[] maxKbps = new int[] { 8000, 12000 };

                    uint[] szKB = new uint[] { 0, 128 * 1024, 256 * 1024, 512 * 1024 };
                    uint[] durMs = new uint[] { 0, 60 * 1000, 5 * 60 * 1000, 15 * 60 * 1000 };

                    const int mainstream = 0;
                    const int substream = 1;

                    Dev.EncodeConfig config = new Dev.EncodeConfig();
                    config.targetUsage = tusage[encusage.SelectedIndex];
                    config.encQuality = 28;
                    config.entropyCoding = Dev.uvs_avc_entropy_CABAC;
                    config.encBitrate = encKbps[encbitrate.SelectedIndex];
                    config.maxBitrate = maxKbps[maxbitrate.SelectedIndex];
                    config.rcControl = rcmode[rc.SelectedIndex];
                    config.scaleUsage = susage[scaleusage.SelectedIndex];
                    // 0 no scale, 1 480P, 2 1080P
                    config.scaleWidth = scale.SelectedIndex == 0 ? 0 : (scale.SelectedIndex == 1 ? 640 : 1920);
                    config.scaleHeight = scale.SelectedIndex == 0 ? 0 : (scale.SelectedIndex == 1 ? 480 : 1080);
                    // 0 no crop, 1 480P, 2 720P
                    config.cropLeft = crop.SelectedIndex == 0 ? 0 : 160;
                    config.cropTop = crop.SelectedIndex == 0 ? 0 : 120;
                    config.cropWidth = crop.SelectedIndex == 0 ? 0 : (crop.SelectedIndex == 1 ? 640 : 1280);
                    config.cropHeight = crop.SelectedIndex == 0 ? 0 : (crop.SelectedIndex == 1 ? 480 : 720);
                    // enc frame rate, 0 same as input
                    if (framerate.SelectedIndex == 0)
                    {
                        config.frameRate = 0;
                    }
                    else
                    {
                        Dev.VideoFormat format;
                        if (dev.GetVideoProperty(out format) != Dev.UVS_OK) return;
                        config.frameRate = format.frameRate / 2;
                    }

                    // auto rec limit file size(KB), 0 manual control
                    uint sz = szKB[filesz.SelectedIndex];

                    // auto rec limit duration(ms), 0 manual control
                    uint dur = durMs[filedur.SelectedIndex];

                    int codec = vcodec[venc.SelectedIndex];

                    // main stream config
                    if (maindir.Text != string.Empty)
                    {
                        if (dev.SetVideoEncodeConfig(mainstream, codec, ref config) != Dev.UVS_OK)
                        {
                            if (Dev.uvs_query_video_encoder(IntPtr.Zero, codec) != Dev.UVS_OK)
                            {
                                MessageBox.Show("HW not support or codec library not found!");
                            }
                            return;
                        }

                        /* %M month, %D month of day, %H 24 hours, %h 12 hours, %m minute, %s second, %Y year,
                        * %t AM/PM, %N month name, %n month short name, %W week name, %w week short name, %i stream index, %% % */
                        string str = System.IO.Path.Combine(maindir.Text, "%Y%M%D_%H%m%s_%i.mp4");
                        dev.SetRecMetaData(mainstream, "Main Stream");
                        
                        if (dev.RecordStart(mainstream, str, aenc.SelectedIndex != 0, null, true, sz, dur) != Dev.UVS_OK) return;
                    }

                    // sub stream config
                    if (subdir.Text != string.Empty)
                    {
                        config.scaleWidth = 640;
                        config.scaleHeight = 480;
                        config.encBitrate /= 4;
                        config.maxBitrate /= 4;
                        if (dev.SetVideoEncodeConfig(substream, codec, ref config) != Dev.UVS_OK)
                        {
                            if (Dev.uvs_query_video_encoder(IntPtr.Zero, codec) != Dev.UVS_OK)
                            {
                                MessageBox.Show("HW not support or codec library not found!");
                            }
                            return;
                        }

                        /* %M month, %D month of day, %H 24 hours, %h 12 hours, %m minute, %s second, %Y year,
                        * %t AM/PM, %N month name, %n month short name, %W week name, %w week short name, %i stream index, %% % */
                        string str = System.IO.Path.Combine(subdir.Text, "%Y%M%D_%H%m%s_%i.mp4");
                        dev.SetRecMetaData(substream, "Sub Stream");

                        if (dev.RecordStart(substream, str, aenc.SelectedIndex != 0, null, true, sz, dur) != Dev.UVS_OK) return;
                    }

                    // audio stream config
                    dev.audioCodec = acodec[aenc.SelectedIndex];

                    if (dev.EncodeStart(Dev.UVS_STREAM_ALL) != Dev.UVS_OK) return;
                    rec = true;
                }

                recstart.Text = rec ? "Record Stop" : "Record Start";
            }
        }

        private void OnPause(object sender, EventArgs e)
        {
            if (dev)
            {
                if (rec)
                {
                    dev.RecordPause(Dev.UVS_STREAM_ALL, !resume);
                    resume = !resume;
                    recpause.Text = resume ? "Rec Resume" : "Rec Pause";
                }
            }
        }

        private Dev dev;
        private bool rec;
        private bool resume;
    }
}
