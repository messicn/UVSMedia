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
using System.Diagnostics;
using UVS_Media;

namespace UVS_DataFrame
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private Dev dev;
        private Dev.uvs_frame_callback framecallback;
        private GCHandle handle;
        private bool audiocallback;
        private bool videocallback;
        private bool enccallback;

        private void OnLoad(object sender, EventArgs e)
        {
            dev = new Dev();

            rotate.SelectedIndex = 0;
            scale.SelectedIndex = 0;

            framecallback += frame_callback;
            handle = GCHandle.Alloc(this);

            // has audio capture ?
            var num = Dev.max_dev_num;
            var info = new Dev.DevInfo[num];
            Dev.uvs_enum_device(Dev.uvs_dev_audio_capture, info, ref num);
            audio.Enabled = num > 0;
            dev.DeviceOpen(0, num > 0 ? 0 : -1);
            if (dev)
            {
                dev.DeviceStart();
                dev.PreviewStart(video.Handle);
            }
        }

        private void OnClosed(object sender, FormClosedEventArgs e)
        {
            // callback disabled
            if (audiocallback)
            {
                OnAudioCallback(sender, e);
            }

            if (videocallback)
            {
                OnVideoCallback(sender, e);
            }

            if (enccallback)
            {
                OnEncCallback(sender, e);
            }

            dev.Dispose();
            if (handle.IsAllocated) handle.Free();
        }

        private static void frame_callback(IntPtr handle, ref Dev.FrameInfo frame, IntPtr userData)
        {
            Form1 f = GCHandle.FromIntPtr(userData).Target as Form1;
            f.PrintFrameInfo(frame);
        }

        enum Frame
        {
            NONE, YUY2, UYVY, YV12,
            I420, NV12, NV21, I422,
            I444, BGR24, RGB24, ARGB32,
            RGBA32, ABGR32, BGRA32, MJPG,
            H264IDR, H264I, H264P, H264B,
            H265IDR, H265I, H265P, H265B,
            PCM, MP3, AAC
        };

        private void PrintFrameInfo(Dev.FrameInfo info)
        {
            string[] str = { "NONE", "Video: YUY2", "Video: UYVY", "Video: YV12",
                        "Video: I420", "Video: NV12", "Video: NV21", "Video: I422",
                        "Video: I444", "Video: BGR24", "Video: RGB24", "Video: ARGB32",
                        "Video: RGBA32", "Video: ABGR32", "Video: BGRA32", "Video: MJPG",
                        "Video: H.264(AVC) IDR", "Video: H.264(AVC) I", "Video: H.264(AVC) P", "Video: H.264(AVC) B",
                        "Video: H.265(HEVC) IDR", "Video: H.265(HEVC) I", "Video: H.265(HEVC) P", "Video: H.265(HEVC) B",
                        "Audio: PCM", "Audio: MP3", "Audio: AAC" };

            int index;
            switch (info.frameType)
            {
                case Dev.uvs_frame_video_YUY2:
                    index = (int)Frame.YUY2; break;
                case Dev.uvs_frame_video_UYVY:
                    index = (int)Frame.UYVY; break;
                case Dev.uvs_frame_video_YV12:
                    index = (int)Frame.YV12; break;
                case Dev.uvs_frame_video_I420:
                    index = (int)Frame.I420; break;
                case Dev.uvs_frame_video_NV12:
                    index = (int)Frame.NV12; break;
                case Dev.uvs_frame_video_NV21:
                    index = (int)Frame.NV21; break;
                case Dev.uvs_frame_video_I422:
                    index = (int)Frame.I422; break;
                case Dev.uvs_frame_video_I444:
                    index = (int)Frame.I444; break;
                case Dev.uvs_frame_video_BGR24:
                    index = (int)Frame.BGR24; break;
                case Dev.uvs_frame_video_RGB24:
                    index = (int)Frame.RGB24; break;
                case Dev.uvs_frame_video_ARGB32:
                    index = (int)Frame.ARGB32; break;
                case Dev.uvs_frame_video_RGBA32:
                    index = (int)Frame.RGBA32; break;
                case Dev.uvs_frame_video_ABGR32:
                    index = (int)Frame.ABGR32; break;
                case Dev.uvs_frame_video_BGRA32:
                    index = (int)Frame.BGRA32; break;
                case Dev.uvs_frame_video_MJPG:
                    index = (int)Frame.MJPG; break;
                case Dev.uvs_frame_video_H264_IDR:
                    index = (int)Frame.H264IDR; break;
                case Dev.uvs_frame_video_H264_I:
                    index = (int)Frame.H264I; break;
                case Dev.uvs_frame_video_H264_P:
                    index = (int)Frame.H264P; break;
                case Dev.uvs_frame_video_H264_B:
                    index = (int)Frame.H264B; break;
                case Dev.uvs_frame_video_H265_IDR:
                    index = (int)Frame.H265IDR; break;
                case Dev.uvs_frame_video_H265_I:
                    index = (int)Frame.H265I; break;
                case Dev.uvs_frame_video_H265_P:
                    index = (int)Frame.H265P; break;
                case Dev.uvs_frame_video_H265_B:
                    index = (int)Frame.H265B; break;
                case Dev.uvs_frame_audio_PCM:
                    index = (int)Frame.PCM; break;
                case Dev.uvs_frame_audio_MP3:
                    index = (int)Frame.MP3; break;
                case Dev.uvs_frame_audio_AAC:
                    index = (int)Frame.AAC; break;

                default:
                    index = (int)Frame.NONE; break;
            }

            if (index >= (int)Frame.PCM)
            { // audio
                Debug.WriteLine("{0} channels {1} bits per sample {2} samples per second {3} data {4} size {5} ts {6}",
                        str[index], info.audioChannels, info.audioBitsPerSample, info.audioSamplesPerSec,
                        info.frameData.ToString("X"), info.frameDataLen, info.timeStamp);
            }
            else if (index > (int)Frame.NONE)
            {
                Debug.WriteLine("{0} width {1} height {2} stride {3} {4} data {5} size {6} ts {7}",
                        str[index], info.videoWidth, info.videoHeight, info.videoDataStride0, info.videoDataStride1,
                        info.frameData.ToString("X"), info.frameDataLen, info.timeStamp);
            }
            else
            {
                Debug.WriteLine(str[(int)Frame.NONE]);
            }
        }

        private void GetFrameConvert(ref Dev.FrameConvert convert)
        {
            convert.frameType = Dev.uvs_frame_NONE;
            // video mirror
            convert.videoMirror = mirror.Checked ? 1 : 0;
            // video flip
            convert.videoFlip = flip.Checked ? 1 : 0;
            // without video crop
            convert.cropLeft = convert.cropTop = convert.cropWidth = convert.cropHeight = 0;
            // video scale
            convert.scaleWidth = scale.SelectedIndex == 0 ? 0 : (scale.SelectedIndex == 1 ? 640 : 3840);
            convert.scaleHeight = scale.SelectedIndex == 0 ? 0 : (scale.SelectedIndex == 1 ? 480 : 2160);
            convert.scaleUsage = Dev.uvs_scale_usage_balance;
            // video rotate
            int[] val = new int[] { Dev.uvs_rotate_none, Dev.uvs_rotate_90, Dev.uvs_rotate_180, Dev.uvs_rotate_270 };
            convert.videoRotate = val[rotate.SelectedIndex];
        }

        private void OnVideoCopy(object sender, EventArgs e)
        {
            if (dev)
            {
                var convert = new Dev.FrameConvert();
                GetFrameConvert(ref convert);

                var frame = new Dev.FrameInfo();
                int r;
                if (convert.frameType != Dev.uvs_frame_NONE ||
                    convert.videoRotate != Dev.uvs_rotate_none ||
                    convert.videoMirror != 0 || convert.videoFlip != 0 ||
                    (convert.scaleWidth > 0 && convert.scaleHeight > 0))
                {
                    GCHandle handle = GCHandle.Alloc(convert, GCHandleType.Pinned);
                    r = dev.CopyVideoFrame(handle.AddrOfPinnedObject(), ref frame);
                    handle.Free();
                }
                else
                {
                    // without conversion
                    r = dev.CopyVideoFrame(IntPtr.Zero, ref frame);
                }

                if (r == Dev.UVS_OK)
                {
                    PrintFrameInfo(frame);
                }
            }
        }

        private void OnSnapshot(object sender, EventArgs e)
        {
            if (dev)
            {
                saveFileDialog1.FileName = "";
                if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    var convert = new Dev.FrameConvert();
                    GetFrameConvert(ref convert);

                    if (convert.frameType != Dev.uvs_frame_NONE ||
                        convert.videoRotate != Dev.uvs_rotate_none ||
                        convert.videoMirror != 0 || convert.videoFlip != 0 ||
                        (convert.scaleWidth > 0 && convert.scaleHeight > 0))
                    {
                        GCHandle handle = GCHandle.Alloc(convert, GCHandleType.Pinned);
                        dev.CaptureSnapshot(saveFileDialog1.FileName, handle.AddrOfPinnedObject());
                        handle.Free();
                    }
                    else
                    {
                        // without conversion
                        dev.CaptureSnapshot(saveFileDialog1.FileName, IntPtr.Zero);
                    }
                }
            }
        }

        private void OnEncCallback(object sender, EventArgs e)
        {
            if (dev)
            {
                const int streamIndex = 0;
                if (enccallback)
                {
                    dev.SetAudioEncodeFrameCallback(null, IntPtr.Zero);
                    dev.SetVideoEncodeFrameCallback(streamIndex, null, IntPtr.Zero);
                    dev.EncodeStop(streamIndex);
                    enccallback = false;
                }
                else
                {
                    Dev.EncodeConfig config = new Dev.EncodeConfig();
                    config.targetUsage = Dev.uvs_target_usage_performance;
                    config.rcControl = Dev.uvs_video_rcmode_VBR;
                    config.encQuality = 28;
                    config.encBitrate = 3000;
                    config.maxBitrate = 5000;

                    int r = dev.SetVideoEncodeConfig(streamIndex, Dev.uvs_video_codec_sw_h264, ref config);
                    if (r != Dev.UVS_OK) return;

                    r = dev.SetVideoEncodeFrameCallback(streamIndex, framecallback, GCHandle.ToIntPtr(handle));
                    if (r != Dev.UVS_OK) return;

                    if (audio.Checked)
                    {
                        dev.audioCodec = Dev.uvs_audio_codec_AAC;
                        dev.SetAudioEncodeFrameCallback(framecallback, GCHandle.ToIntPtr(handle));
                    }

                    dev.EncodeStart(streamIndex);
                    enccallback = true;
                }

                callback.Text = enccallback ? "Callback Stop" : "Encode Frame Callback";
            }
        }

        private void OnVideoCallback(object sender, EventArgs e)
        {
            if (dev)
            {
                // set video callback
                dev.SetVideoRawFrameCallback(videocallback ? null : framecallback, videocallback ? IntPtr.Zero : GCHandle.ToIntPtr(handle));
                videocallback = !videocallback;
                vcallback.Text = videocallback ? "Callback Stop" : "Video Frame Callback";
            }
        }

        private void OnVideoLock(object sender, EventArgs e)
        {
            if (dev)
            {
                Dev.FrameInfo frame;
                if (dev.LockVideoRawFrame(out frame) == Dev.UVS_OK)
                {
                    PrintFrameInfo(frame);
                    dev.UnlockVideoRawFrame();
                }
            }
        }

        private void OnAudioCopy(object sender, EventArgs e)
        {
            if (dev)
            {
                var frame = new Dev.FrameInfo();
                if (dev.CopyAudioRawFrame(ref frame) == Dev.UVS_OK)
                {
                    PrintFrameInfo(frame);
                }
            }
        }

        private void OnAudioCallback(object sender, EventArgs e)
        {
            if (dev)
            {
                // set audio callback
                dev.SetAudioRawFrameCallback(audiocallback ? null : framecallback, audiocallback ? IntPtr.Zero : GCHandle.ToIntPtr(handle));
                audiocallback = !audiocallback;
                acallback.Text = audiocallback ? "Callback Stop" : "Audio Frame Callback";
            }
        }

        private void OnAudioLock(object sender, EventArgs e)
        {
            if (dev)
            {
                Dev.FrameInfo frame;
                if (dev.LockAudioRawFrame(out frame) == Dev.UVS_OK)
                {
                    PrintFrameInfo(frame);
                    dev.UnlockAudioRawFrame();
                }
            }
        }
    }
}
