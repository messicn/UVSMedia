using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using UVS_Media;

namespace UVS_Preview
{
    public partial class Form1 : Form
    {
        [DllImport("User32.dll")]
        public static extern IntPtr GetParent(IntPtr hwnd);

        [DllImport("User32.dll")]
        public static extern IntPtr SetParent(IntPtr hwnd, IntPtr hparent);

        [DllImport("User32.dll")]
        public static extern int GetWindowRect(IntPtr hwnd, out Dev.RECT rc);

        [DllImport("User32.dll")]
        public static extern int ScreenToClient(IntPtr hwnd, ref Dev.POINT pt);

        [DllImport("User32.dll")]
        public static extern int MoveWindow(IntPtr hwnd, int x, int y, int width, int height, int redraw);

        public Form1()
        {
            InitializeComponent();
        }

        private void OnLoad(object sender, EventArgs e)
        {
            // sdk init
            dev = new Dev();

            // enmu audio capture
            int num = 16;
            Dev.DevInfo[] info = new Dev.DevInfo[num];
            int r = Dev.uvs_enum_device(Dev.uvs_dev_audio_capture, info, ref num);
            if (num > 0)
            {
                for (int i = 0; i < num; i++)
                {
                    acap.Items.Add(info[i].szFriendlyDevName);
                }
                acap.SelectedIndex = 0;
            }

            // enmu audio renderer
            num = 16;
            r = Dev.uvs_enum_device(Dev.uvs_dev_audio_renderer, info, ref num);
            if (num > 0)
            {
                for (int i = 0; i < num; i++)
                {
                    arender.Items.Add(info[i].szFriendlyDevName);
                }
                // default audio renderer -1
            }

            // enmu video capture
            num = 16;
            r = Dev.uvs_enum_device(Dev.uvs_dev_video_capture, info, ref num);
            if (num > 0)
            {
                for (int i = 0; i < num; i++)
                {
                    vcap.Items.Add(info[i].szFriendlyDevName);
                }
                vcap.SelectedIndex = 0;
            }

            vrender.SelectedIndex = 0;

            DevStart();
        }

        private void OnClosed(object sender, FormClosedEventArgs e)
        {
            dev.Dispose();
        }

        private void DevStart()
        {
            dev.DeviceClose();
            dev.DeviceOpen(vcap.SelectedIndex, acap.SelectedIndex);
            if (dev)
            {
                audioCap = acap.SelectedIndex;
                videoCap = vcap.SelectedIndex;

                // set audio renderer
                int num = Dev.max_dev_num;
                Dev.DevInfo[] info = new Dev.DevInfo[num];
                int r = Dev.uvs_enum_device(Dev.uvs_dev_audio_renderer, info, ref num);
                if (num > 0 && arender.SelectedIndex >= 0 && arender.SelectedIndex < num)
                {
                    dev.SetAudioDevice(Dev.uvs_dev_audio_renderer, ref info[arender.SelectedIndex]);
                    audioRenderer = arender.SelectedIndex;
                }

                dev.DeviceStart();

                // set video renderer
                OnPreview(null, null);

                // set video effect range
                int[] effect = { Dev.uvs_video_brightness, Dev.uvs_video_contrast,
                                 Dev.uvs_video_saturation, Dev.uvs_video_gamma };
                TrackBar[] bar = { brightness, contrast, saturation, gamma };
                int minValue, maxValue, stepValue, defaultValue;
                for (int i = 0; i < 4; i++)
                {
                    r = dev.GetVideoEffectRange(effect[i], out minValue, out maxValue, out stepValue, out defaultValue);
                    if (r == Dev.UVS_OK)
                    {
                        bar[i].Minimum = minValue;
                        bar[i].Maximum = maxValue;
                    }
                }

                brightness.DataBindings.Clear();
                brightness.DataBindings.Add("Value", dev, "brightness", true, DataSourceUpdateMode.OnPropertyChanged);

                contrast.DataBindings.Clear();
                contrast.DataBindings.Add("Value", dev, "contrast", true, DataSourceUpdateMode.OnPropertyChanged);

                saturation.DataBindings.Clear();
                saturation.DataBindings.Add("Value", dev, "saturation", true, DataSourceUpdateMode.OnPropertyChanged);

                gamma.DataBindings.Clear();
                gamma.DataBindings.Add("Value", dev, "gamma", true, DataSourceUpdateMode.OnPropertyChanged);

                volume.DataBindings.Clear();
                volume.DataBindings.Add("Value", dev, "volume", true, DataSourceUpdateMode.OnPropertyChanged);

                balance.DataBindings.Clear();
                balance.DataBindings.Add("Value", dev, "balance", true, DataSourceUpdateMode.OnPropertyChanged);

                mirror.DataBindings.Clear();
                mirror.DataBindings.Add("Checked", dev, "mirror", true, DataSourceUpdateMode.OnPropertyChanged);

                flip.DataBindings.Clear();
                flip.DataBindings.Add("Checked", dev, "flip", true, DataSourceUpdateMode.OnPropertyChanged);

                mute.DataBindings.Clear();
                mute.DataBindings.Add("Checked", dev, "mute", true, DataSourceUpdateMode.OnPropertyChanged);
            }
        }

        private void OnChanged(object sender, EventArgs e)
        {
            if (sender == acap && acap.SelectedIndex == audioCap) return;
            if (sender == arender && arender.SelectedIndex == audioRenderer) return;
            if (sender == vcap && vcap.SelectedIndex == videoCap) return;

            // device changed
            DevStart();
        }

        private void OnPreview(object sender, EventArgs e)
        {
            if (sender == null || vrender.SelectedIndex != videoRenderer)
            {
                if (zoomIn)
                {
                    OnZoomin(sender, e);
                }

                if (zoomOut)
                {
                    OnZoomout(sender, e);
                }

                dev.PreviewStop();
                dev.PreviewStart(video.Handle, vrender.SelectedIndex == 0 ? Dev.uvs_disp_type_d3d : Dev.uvs_disp_type_ddraw);
                videoRenderer = vrender.SelectedIndex;
            }
        }

        private void OnZoomin(object sender, EventArgs e)
        {
            if (zoomIn)
            {
                dev.PreviewRect(IntPtr.Zero, IntPtr.Zero);
                zoomIn = false;
            }
            else
            {
                Dev.VideoFormat format;
                if (dev.GetVideoProperty(out format) == Dev.UVS_OK)
                {
                    // zoom in 2X
                    Dev.RECT rc;
                    rc.left = format.videoWidth / 4;
                    rc.top = format.videoHeight / 4;
                    rc.right = format.videoWidth * 3 / 4;
                    rc.bottom = format.videoHeight * 3 / 4;

                    GCHandle handle = GCHandle.Alloc(rc, GCHandleType.Pinned);
                    dev.PreviewRect(IntPtr.Zero, handle.AddrOfPinnedObject());
                    handle.Free();
                    zoomIn = true;
                }
            }
        }

        private void OnFullscreen(object sender, EventArgs e)
        {
            if (zoomIn)
            {
                OnZoomin(sender, e);
            }

            if (zoomOut)
            {
                OnZoomout(sender, e);
            }

            if (!fullScreen)
            {
                // save window position
                GetWindowRect(video.Handle, out rect);

                Dev.POINT pt;
                pt.x = rect.left;
                pt.y = rect.top;
                ScreenToClient(this.Handle, ref pt);

                rect.left = pt.x;
                rect.top = pt.y;

                pt.x = rect.right;
                pt.y = rect.bottom;
                ScreenToClient(this.Handle, ref pt);

                rect.right = pt.x;
                rect.bottom = pt.y;

                // change window parent
                parent = SetParent(video.Handle, IntPtr.Zero);

                // set window fullscreen
                int width = Screen.PrimaryScreen.Bounds.Width;
                int height = Screen.PrimaryScreen.Bounds.Height;
                MoveWindow(video.Handle, 0, 0, width, height, 1);
                fullScreen = true;
            }
        }

        private void OnFreeze(object sender, EventArgs e)
        {
            dev.freeze = !dev.freeze;
        }

        private void OnZoomout(object sender, EventArgs e)
        {
            if (zoomOut)
            {
                dev.PreviewRect(IntPtr.Zero, IntPtr.Zero);
                zoomOut = false;
            }
            else
            {
                // zoom out 2X
                Dev.RECT rc;
                rc.left = video.ClientSize.Width / 4;
                rc.top = video.ClientSize.Height / 4;
                rc.right = video.ClientSize.Width * 3 / 4;
                rc.bottom = video.ClientSize.Height * 3 / 4;

                GCHandle handle = GCHandle.Alloc(rc, GCHandleType.Pinned);
                dev.PreviewRect(handle.AddrOfPinnedObject(), IntPtr.Zero, Color.FromArgb(240, 240, 240).ToArgb());
                handle.Free();
                video.Invalidate();
                zoomOut = true;
            }
        }

        private void OnClick(object sender, EventArgs e)
        {
            if (fullScreen)
            {
                // restore window
                SetParent(video.Handle, parent);
                MoveWindow(video.Handle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 1);
                fullScreen = false;
            }
        }

        private Dev dev;
        private int audioCap = 0;
        private int audioRenderer = -1;
        private int videoCap = 0;
        private int videoRenderer = 0;

        private bool fullScreen = false;
        private bool zoomIn = false;
        private bool zoomOut = false;

        private IntPtr parent;
        private Dev.RECT rect;
    }
}
