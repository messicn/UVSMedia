using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using UVS_Media;

namespace UVS_Device
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Onload(object sender, EventArgs e)
        {
            mode.SelectedIndex = 0;
            timer1.Enabled = true;

            int r;
            dev = new Dev(0, -1, out r);
            DevStart();

            // set device callback
            context = SynchronizationContext.Current;
            callback += device_callback;
            handle = GCHandle.Alloc(this);
            Dev.uvs_set_device_callback(callback, GCHandle.ToIntPtr(handle));
        }

        private void OnTimer(object sender, EventArgs e)
        {
            string str = "";
            if (dev)
            {
                int status, mode;
                int r = dev.GetVideoStatus(out status, out mode);
                if (r == Dev.UVS_OK)
                {
                    str = status != 0 ? "Signal" : "No Signal";
                    str += mode != 0 ? "(USB3)" : "(USB2)";
                }
            }

            this.status.Text = str;
        }

        private void DevStart()
        {
            if (dev)
            {
                dev.DeviceStart();
                dev.PreviewStart(video.Handle);
            }
        }

        private static void device_callback(int notify, ref Dev.DevInfo info, IntPtr handle, IntPtr userData)
        {
            Form1 f = GCHandle.FromIntPtr(userData).Target as Form1;
            var obj = info;
            f.context.Post(x => { f.OnNotify(notify, x, handle); }, obj);
        }

        private void OnClosed(object sender, FormClosedEventArgs e)
        {
            dev.Dispose();
            if (handle.IsAllocated) handle.Free();
        }

        private void OnNotify(int notify, object obj, IntPtr handle)
        {
            if (obj is Dev.DevInfo)
            {
                var info = (Dev.DevInfo)obj;
                if (notify == Dev.uvs_dev_changed)
                {
                    // open device
                    if (!dev)
                    {
                        dev.DeviceOpen(ref info);
                        DevStart();
                    }
                }
                else if (dev.handle == handle)
                {
                    // close device
                    dev.DeviceClose();
                    video.Invalidate();
                }
            }
        }

        private void OnBrowse(object sender, EventArgs e)
        {
            openFileDialog1.FileName = "";
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                file.Text = openFileDialog1.FileName;
            }
        }

        private void OnColor(object sender, EventArgs e)
        {
            colorDialog1.Color = bkcolor;
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {
                bkcolor = colorDialog1.Color;
            }
        }

        private void OnApply(object sender, EventArgs e)
        {
            if (file.Text == string.Empty)
            {
                // nosignal image disabled
                Dev.uvs_set_nosignal_image(null, 0, 0);
            }
            else
            {
                Dev.uvs_set_nosignal_image(file.Text, mode.SelectedIndex, Dev.ToCOLORREF(bkcolor.ToArgb()));
            }
        }

        private Dev dev;
        private Dev.uvs_device_callback callback;
        private GCHandle handle;
        private SynchronizationContext context;
        private Color bkcolor;
    }
}
