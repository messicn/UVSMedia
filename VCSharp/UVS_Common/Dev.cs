using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace UVS_Media
{
    public class Dev
    {
        public const string uvsdll = "UVSMedia.dll";

        public const int max_dev_num = 16;

        public const int UVS_OK = 0;
        public const int UVS_ERR = -1;
        public const int UVS_ERR_OUTOFMEMORY = -2;
        public const int UVS_ERR_INVALIDARG = -3;
        public const int UVS_ERR_WAIT_TIMEOUT = -4;
        public const int UVS_ERR_NOT_INITIALIZED = -5;
        public const int UVS_ERR_NOT_ENOUGH_BUFFER = -6;
        public const int UVS_ERR_NOT_READY = -7;
        public const int UVS_ERR_NOT_SUPPORT = -8;
        public const int UVS_ERR_FILE_OPEN = -9;
        public const int UVS_ERR_ALREADY_EXISTS = -10;

        public const int UVS_STREAM_ALL = -1;

        public const int UVS_NAME_LEN = 128;
        public const int UVS_FILENAME_LEN = 260;
        public const int UVS_URL_LEN = 256;

        public const int uvs_draw_stretch = 0;
        public const int uvs_draw_center = 1;

        public const int uvs_dev_video_capture = 0;
        public const int uvs_dev_audio_capture = 1;
        public const int uvs_dev_audio_renderer = 2;

        public const int uvs_dev_closed = 0;
        public const int uvs_dev_changed = 1;

        public const int uvs_dev_run = 0;
        public const int uvs_dev_pause = 1;
        public const int uvs_dev_stop = 2;

        public const int uvs_video_brightness = 0;
        public const int uvs_video_contrast = 1;
        public const int uvs_video_saturation = 3;
        public const int uvs_video_gamma = 5;

        public const int uvs_source_any = 0;
        public const int uvs_source_preview = 1;
        public const int uvs_source_capture = 2;

        public const int uvs_disp_type_ddraw = 0;
        public const int uvs_disp_type_d3d = 1;

        public const int uvs_audio_codec_none = 0;
        public const int uvs_audio_codec_MP3 = 0;
        public const int uvs_audio_codec_AAC = 0;

        public const int uvs_video_codec_none = 0;
        public const int uvs_video_codec_intel_h264 = 4;
        public const int uvs_video_codec_intel_h265 = 5;
        public const int uvs_video_codec_intel_jpeg = 6;
        public const int uvs_video_codec_nvidia_h264 = 7;
        public const int uvs_video_codec_nvidia_h265 = 8;
        public const int uvs_video_codec_sw_h264 = 9;

        public const int uvs_target_usage_performance = 0;
        public const int uvs_target_usage_balance = 1;
        public const int uvs_target_usage_quality = 2;

        public const int uvs_codec_profile_auto = 0;
        public const int uvs_codec_profile_baseline = 1;
        public const int uvs_codec_profile_main = 2;
        public const int uvs_codec_profile_high = 3;

        public const int uvs_avc_entropy_CABAC = 0;
        public const int uvs_avc_entropy_CAVLC = 1;

        public const int uvs_video_rcmode_VBR = 0;
        public const int uvs_video_rcmode_CBR = 1;
        public const int uvs_video_rcmode_CQP = 2;
        public const int uvs_video_rcmode_AVBR = 3;

        public const int uvs_rotate_none = 0;
        public const int uvs_rotate_90 = 1;
        public const int uvs_rotate_180 = 2;
        public const int uvs_rotate_270 = 3;

        public const int uvs_scale_usage_performance = 0;
        public const int uvs_scale_usage_balance = 1;
        public const int uvs_scale_usage_quality = 2;
        public const int uvs_scale_usage_high_quality = 3;

        public const int uvs_frame_NONE = 0;
        public const int uvs_frame_video_YUY2 = 1;
        public const int uvs_frame_video_UYVY = 2;
        public const int uvs_frame_video_YV12 = 3;
        public const int uvs_frame_video_I420 = 4;
        public const int uvs_frame_video_NV12 = 5;
        public const int uvs_frame_video_NV21 = 6;
        public const int uvs_frame_video_I422 = 7;
        public const int uvs_frame_video_I444 = 8;
        public const int uvs_frame_video_BGR24 = 9; /* BGR little endian (rgb in memory) */
        public const int uvs_frame_video_RGB24 = 10; /* RGB little endian (bgr in memory) */
        public const int uvs_frame_video_ARGB32 = 11; /* ARGB little endian (bgra in memory) */
        public const int uvs_frame_video_RGBA32 = 12; /* RGBA little endian (abgr in memory) */
        public const int uvs_frame_video_ABGR32 = 13; /* ABGR little endian (rgba in memory) */
        public const int uvs_frame_video_BGRA32 = 14; /* BGRA little endian (argb in memory) */
        public const int uvs_frame_video_MJPG = 37;
        public const int uvs_frame_video_H264_IDR = 40;
        public const int uvs_frame_video_H264_I = 41;
        public const int uvs_frame_video_H264_P = 42;
        public const int uvs_frame_video_H264_B = 43;
        public const int uvs_frame_video_H265_IDR = 50;
        public const int uvs_frame_video_H265_I = 51;
        public const int uvs_frame_video_H265_P = 52;
        public const int uvs_frame_video_H265_B = 53;
        public const int uvs_frame_audio_PCM = 70;
        public const int uvs_frame_audio_MP3 = 71;
        public const int uvs_frame_audio_AAC = 72;

        /* index [uvs_osd_index_preview_enc, max_uvs_osd_index_preview_enc], OSD preview + encode */
        public const int uvs_osd_index_preview_enc = 0;
        public const int uvs_time_osd_index_preview_enc = 255;
        /* index [uvs_osd_index_preview_only, uvs_time_osd_index_preview_only], OSD preview only */
        public const int uvs_osd_index_preview_only = 256;
        public const int uvs_time_osd_index_preview_only = 511;

        public const int uvs_font_style_regular = 0;
        public const int uvs_font_style_bold = 1;
        public const int uvs_font_style_italic = 2;
        public const int uvs_font_style_bold_italic = 3;
        public const int uvs_font_style_underline = 4; /* composite attribute */
        public const int uvs_font_style_strikeout = 8; /* composite attribute */
        public const int uvs_font_style_cleartype = 16; /* composite attribute, improves the readability of text on LCDs */

        public const int uvs_string_format_regular = 0;
        public const int uvs_string_rect_multiple_lines = 1; /* composite attribute */
        public const int uvs_string_direction_vertical = 2; /* composite attribute */
        public const int uvs_string_direction_right_to_left = 4; /* composite attribute */
        public const int uvs_string_align_style_near = 8;
        public const int uvs_string_align_style_center = 16;
        public const int uvs_string_align_style_far = 32;
        public const int uvs_string_line_align_style_near = 64;
        public const int uvs_string_line_align_style_center = 128;
        public const int uvs_string_line_align_style_far = 256;
        public const int uvs_string_trmming_character = 512;
        public const int uvs_string_trmming_word = 1024;
        public const int uvs_string_trmming_ellipsis_character = 2048;
        public const int uvs_string_trmming_ellipsis_word = 4096;
        public const int uvs_string_trmming_ellipsis_path = 8192;

        public const int uvs_osd_enable = 0;
        public const int uvs_osd_delete = 1;
        public const int uvs_osd_delete_all = 2;
        public const int uvs_osd_get_count = 3;
        public const int uvs_osd_get_size = 4;
        public const int uvs_osd_get_position = 5;
        public const int uvs_osd_set_position = 6;
        public const int uvs_osd_get_font_size = 7;
        public const int uvs_osd_set_font_size = 8;
        public const int uvs_osd_get_color = 9;
        public const int uvs_osd_set_color = 10;
        public const int uvs_osd_get_opacity = 11;
        public const int uvs_osd_set_opacity = 12;
        public const int uvs_osd_get_clip_position = 13;
        public const int uvs_osd_set_clip_position = 14; /* clip x, y position */
        public const int uvs_osd_get_clip_size = 15;
        public const int uvs_osd_set_clip_size = 16; /* clip width & height */
        public const int uvs_osd_get_blink = 17;
        public const int uvs_osd_set_blink = 18;

        public const int uvs_dash_style_solid = 0;
        public const int uvs_dash_style_dash = 1;
        public const int uvs_dash_style_dot = 2;
        public const int uvs_dash_style_dash_dot = 3;

        public const int uvs_mp4_file_begining = 0;
        public const int uvs_mp4_file_ending = -1;

        [StructLayout(LayoutKind.Sequential)]
        public struct POINT
        {
            public int x;
            public int y;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct RECT
        {
            public int left;
            public int top;
            public int right;
            public int bottom;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct DevInfo
        {
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = UVS_NAME_LEN)]
            public string szFriendlyDevName;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct VideoFormat
        {
            public int frameType;
            public int videoWidth;
            public int videoHeight;
            public float frameRate;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct AudioFormat
        {
            public int frameType;
            public int audioChannels;
            public int samplesPreSEc;
            public int bitsPreSample;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct EncodeConfig
        {
            public int targetUsage;
            public int encProfile;
            public int entropyCoding;
            public int scaleUsage;
            public int scaleWidth;
            public int scaleHeight;
            public int cropLeft;
            public int cropTop;
            public int cropWidth;
            public int cropHeight;
            public float frameRate;
            public int rcControl;
            public int encBitrate;
            public int maxBitrate;
            public int encQuality;
            public int GOPLength;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct EncodeStatus
        {
            public int inputFrames;
            public int encodeFrames;
            public float inputFrameRate;
            public float encodeFrameRate;
        }

        [StructLayout(LayoutKind.Explicit)]
        public struct FrameInfo
        {
            [FieldOffset(0)]
            public int frameType;
            [FieldOffset(4)]
            public UInt16 videoWidth; /* video width in pixels */
            [FieldOffset(6)]
            public UInt16 videoHeight; /* video height in pixels */
            [FieldOffset(4)]
            public UInt16 audioChannels; /* mono or stereo audio */
            [FieldOffset(6)]
            public UInt16 audioBitsPerSample; /* audio sample bit depth */
            [FieldOffset(8)]
            public UInt16 videoDataStride0; /* one row in bytes for multiple planes */
            [FieldOffset(10)]
            public UInt16 videoDataStride1; /* one row in bytes for multiple planes */
            [FieldOffset(8)]
            public uint audioSamplesPerSec; /* audio sample rate per-channel */
            [FieldOffset(12)]
            public uint frameDataLen; /* number of bytes */
            [FieldOffset(16)]
            public Int64 timeStamp; /* timestamp in micro seconds */
            [FieldOffset(24)]
            public IntPtr frameData; /* frame data */
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FrameConvert
        {
            public int frameType;
            public int videoMirror;
            public int videoFlip;
            public int cropLeft;
            public int cropTop;
            public int cropWidth;
            public int cropHeight;
            public int scaleWidth;
            public int scaleHeight;
            public int scaleUsage;
            public int videoRotate;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct RecFileName
        {
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = UVS_FILENAME_LEN)]
            public string szFileName;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct FontInfo
        {
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = UVS_NAME_LEN)]
            public string szFontName;
            public int fontPointSize;
            public int fontStyle;
            public int stringFormat;
            public int textColor;
            public int textBkColor;
            public int textOpacity;
            public int textBkOpacity;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct StyleInfo
        {
            public int lineSize;
            public int dashStyle;
            public int edgeColor;
            public int fillColor;
            public int edgeOpacity;
            public int fillOpacity;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct LineInfo
        {
            public int lineSize;
            public int dashStyle;
            public int lineColor;
            public int lineOpacity;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct URLInfo
        {
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = UVS_URL_LEN)]
            public string szURL;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FileStatus
        {
            public int audioCodec;
            public int videoCodec;
            public int audioDuration;
            public int videoDuration;
            public int videoWidth;
            public int videoHeight;
            public float videoFrameRate;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct TitleInfo
        {
            public FontInfo textFont;
            public int x;
            public int y;
            public int width;
            public int height;
            public int imageOpacity;
            [MarshalAs(UnmanagedType.LPTStr)]
            string imageFile;
            [MarshalAs(UnmanagedType.LPTStr)]
            string text;
        }

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void uvs_device_callback(int notify, ref DevInfo info, IntPtr handle, IntPtr userData);

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void uvs_frame_callback(IntPtr handle, ref FrameInfo frame, IntPtr userData);

        [DllImport(uvsdll)]
        public static extern int uvs_media_init(int flags);

        [DllImport(uvsdll)]
        public static extern int uvs_media_exit();

        [DllImport(uvsdll, EntryPoint = "uvs_enum_deviceW")]
        public static extern int uvs_enum_device(int devType, [In, Out] DevInfo[] info, ref int num);

        [DllImport(uvsdll, EntryPoint = "uvs_set_device_callbackW")]
        public static extern int uvs_set_device_callback([MarshalAs(UnmanagedType.FunctionPtr)] uvs_device_callback cb, IntPtr userData);

        [DllImport(uvsdll)]
        public static extern int uvs_get_device_count();

        [DllImport(uvsdll)]
        public static extern int uvs_query_video_encoder(IntPtr handle, int codec);

        [DllImport(uvsdll)]
        public static extern int uvs_calc_buffer_size(int frameType, int width, int height, int stride);

        [DllImport(uvsdll)]
        public static extern int uvs_create_frame(int frameType, int width, int height, int stride, out FrameInfo frame);

        [DllImport(uvsdll)]
        public static extern int uvs_destroy_frame(ref FrameInfo frame);

        [DllImport(uvsdll, EntryPoint = "uvs_set_nosignal_imageW")]
        public static extern int uvs_set_nosignal_image([MarshalAs(UnmanagedType.LPTStr)] string filename, int mode, int backgroundColor);

        [DllImport(uvsdll, EntryPoint = "uvs_dev_openW")]
        public static extern IntPtr uvs_dev_open(ref DevInfo info, out int result);

        [DllImport(uvsdll)]
        public static extern int uvs_dev_close(IntPtr handle);

        [DllImport(uvsdll, EntryPoint = "uvs_set_audio_deviceW")]
        public static extern int uvs_set_audio_device(IntPtr handle, int devType, ref DevInfo info);

        [DllImport(uvsdll)]
        public static extern int uvs_dev_control(IntPtr handle, int state);

        [DllImport(uvsdll)]
        public static extern int uvs_get_audio_property(IntPtr handle, out AudioFormat format, out int codec);

        [DllImport(uvsdll)]
        public static extern int uvs_set_audio_property(IntPtr handle, IntPtr format, int codec);

        [DllImport(uvsdll)]
        public static extern int uvs_set_audio_mute(IntPtr handle, int mute);

        [DllImport(uvsdll)]
        public static extern int uvs_get_audio_volume(IntPtr handle, out int volume);

        [DllImport(uvsdll)]
        public static extern int uvs_set_audio_volume(IntPtr handle, int state);

        [DllImport(uvsdll)]
        public static extern int uvs_get_audio_balance(IntPtr handle, out int balance);

        [DllImport(uvsdll)]
        public static extern int uvs_set_audio_balance(IntPtr handle, int balance);

        [DllImport(uvsdll)]
        public static extern int uvs_get_video_property(IntPtr handle, int source, out VideoFormat format);

        [DllImport(uvsdll)]
        public static extern int uvs_set_video_property(IntPtr handle, int source, ref VideoFormat format);

        [DllImport(uvsdll)]
        public static extern int uvs_get_video_mirror(IntPtr handle, out int horzMirror, out int vertMirror);

        [DllImport(uvsdll)]
        public static extern int uvs_set_video_mirror(IntPtr handle, int horzMirror, int vertMirror);

        [DllImport(uvsdll)]
        public static extern int uvs_get_video_status(IntPtr handle, out int signal, out int mode);

        [DllImport(uvsdll)]
        public static extern int uvs_get_video_effect_range(IntPtr handle,
                                                            int effect,
                                                            out int minValue,
                                                            out int maxValue,
                                                            out int step,
                                                            out int defaultValue);

        [DllImport(uvsdll)]
        public static extern int uvs_get_video_effect(IntPtr handle, int effect, out int value);

        [DllImport(uvsdll)]
        public static extern int uvs_set_video_effect(IntPtr handle, int effect, int value);

        [DllImport(uvsdll)]
        public static extern int uvs_set_video_encode_config(IntPtr handle, int streamIndex, int codec, ref EncodeConfig config);

        [DllImport(uvsdll)]
        public static extern int uvs_get_video_encode_config(IntPtr handle, int streamIndex, out int codec, out EncodeConfig config);

        [DllImport(uvsdll)]
        public static extern int uvs_request_video_key_frame(IntPtr handle, int streamIndex);

        [DllImport(uvsdll)]
        public static extern int uvs_get_video_encode_status(IntPtr handle, int streamIndex, out EncodeStatus status);

        [DllImport(uvsdll)]
        public static extern int uvs_start_encode(IntPtr handle, int streamIndex);

        [DllImport(uvsdll)]
        public static extern int uvs_stop_encode(IntPtr handle, int streamIndex);

        [DllImport(uvsdll, EntryPoint = "uvs_set_record_metadataW")]
        public static extern int uvs_set_record_metadata(IntPtr handle, int streamIndex,
                                                         [MarshalAs(UnmanagedType.LPTStr)] string title,
                                                         [MarshalAs(UnmanagedType.LPTStr)] string comment,
                                                         [MarshalAs(UnmanagedType.LPTStr)] string artist,
                                                         [MarshalAs(UnmanagedType.LPTStr)] string genre,
                                                         [MarshalAs(UnmanagedType.LPTStr)] string composer);

        [DllImport(uvsdll, EntryPoint = "uvs_start_recordW")]
        public static extern int uvs_start_record(IntPtr handle, int streamIndex,
                                                  [MarshalAs(UnmanagedType.LPTStr)] string saveFilename1,
                                                  [MarshalAs(UnmanagedType.LPTStr)] string saveFilename2,
                                                  int recAudio, int repairSupport, uint fileSize, uint fileDuration);

        [DllImport(uvsdll, EntryPoint = "uvs_get_record_filenameW")]
        public static extern int uvs_get_record_filename(IntPtr handle, int streamIndex, [In, Out] RecFileName[] file, ref int num);

        [DllImport(uvsdll)]
        public static extern int uvs_pause_record(IntPtr handle, int streamIndex, int resume, int requestKeyframe);

        [DllImport(uvsdll)]
        public static extern int uvs_stop_record(IntPtr handle, int streamIndex);

        [DllImport(uvsdll)]
        public static extern int uvs_start_preview(IntPtr handle, IntPtr hwnd, int dispType);

        [DllImport(uvsdll)]
        public static extern int uvs_get_preview_freeze(IntPtr handle, out int freeze);

        [DllImport(uvsdll)]
        public static extern int uvs_set_preview_freeze(IntPtr handle, int freeze);

        [DllImport(uvsdll)]
        public static extern int uvs_set_preview_rect(IntPtr handle, IntPtr wndRect, IntPtr videoRect, int fillColor);

        [DllImport(uvsdll)]
        public static extern int uvs_stop_preview(IntPtr handle);

        [DllImport(uvsdll, EntryPoint = "uvs_set_time_osdW")]
        public static extern int uvs_set_time_osd(IntPtr handle,
                                                  int osdIndex,
                                                  int x, int y,
                                                  [MarshalAs(UnmanagedType.LPTStr)] string szTimeFormat,
                                                  ref FontInfo info);

        [DllImport(uvsdll, EntryPoint = "uvs_set_text_osdW")]
        public static extern int uvs_set_text_osd(IntPtr handle,
                                                  int osdIndex,
                                                  int x, int y, int width, int height,
                                                  [MarshalAs(UnmanagedType.LPTStr)] string szText,
                                                  ref FontInfo info);

        [DllImport(uvsdll, EntryPoint = "uvs_set_image_osdW")]
        public static extern int uvs_set_image_osd(IntPtr handle,
                                                   int osdIndex,
                                                   int x, int y, int width, int height,
                                                   int imgOpacity,
                                                   [MarshalAs(UnmanagedType.LPTStr)] string szFileName);

        [DllImport(uvsdll)]
        public static extern int uvs_set_rect_osd(IntPtr handle,
                                                  int osdIndex,
                                                  int x, int y, int width, int height,
                                                  ref StyleInfo info);

        [DllImport(uvsdll)]
        public static extern int uvs_set_ellipse_osd(IntPtr handle,
                                                     int osdIndex,
                                                     int x, int y, int width, int height,
                                                     ref StyleInfo info);

        [DllImport(uvsdll)]
        public static extern int uvs_set_line_osd(IntPtr handle,
                                                  int osdIndex,
                                                  int x0, int y0, int x1, int y1,
                                                  ref LineInfo info);

        [DllImport(uvsdll)]
        public static extern int uvs_osd_control(IntPtr handle, int osdIndex, int osdCmd, ref int param0, ref int param1);

        [DllImport(uvsdll)]
        public static extern IntPtr uvs_create_frame_preview(IntPtr hwnd, int dispType);

        [DllImport(uvsdll)]
        public static extern int uvs_frame_preview(IntPtr obj, ref FrameInfo info);

        [DllImport(uvsdll)]
        public static extern int uvs_set_frame_preview_rect(IntPtr obj, IntPtr wndRect, IntPtr videoRect, int fillColor);

        [DllImport(uvsdll)]
        public static extern int uvs_destroy_frame_preview(IntPtr obj);

        [DllImport(uvsdll)]
        public static extern int uvs_set_video_raw_frame_callback(IntPtr handle,
                                                                  [MarshalAs(UnmanagedType.FunctionPtr)] uvs_frame_callback cb,
                                                                  IntPtr userData);

        [DllImport(uvsdll)]
        public static extern int uvs_set_video_enc_frame_callback(IntPtr handle,
                                                                  int streamIndex,
                                                                  [MarshalAs(UnmanagedType.FunctionPtr)] uvs_frame_callback cb,
                                                                  IntPtr userData);

        [DllImport(uvsdll)]
        public static extern int uvs_convert_video_frame(ref FrameConvert convert, ref FrameInfo src, ref FrameInfo dest);

        [DllImport(uvsdll, EntryPoint = "uvs_save_video_frameW")]
        public static extern int uvs_save_video_frame([MarshalAs(UnmanagedType.LPTStr)] string filename,
                                                      IntPtr convert,
                                                      ref FrameInfo info,
                                                      uint jpegQuality);

        [DllImport(uvsdll, EntryPoint = "uvs_save_video_snapshotW")]
        public static extern int uvs_save_video_snapshot(IntPtr handle,
                                                         [MarshalAs(UnmanagedType.LPTStr)] string filename,
                                                         IntPtr convert,
                                                         uint jpegQuality);

        [DllImport(uvsdll)]
        public static extern int uvs_lock_video_raw_frame(IntPtr handle, out FrameInfo info, uint waitMilliSec);

        [DllImport(uvsdll)]
        public static extern int uvs_unlock_video_raw_frame(IntPtr handle);

        [DllImport(uvsdll)]
        public static extern int uvs_copy_video_frame(IntPtr handle, IntPtr convert, ref FrameInfo info, uint waitMilliSec);

        [DllImport(uvsdll)]
        public static extern int uvs_set_audio_raw_frame_callback(IntPtr handle,
                                                                  [MarshalAs(UnmanagedType.FunctionPtr)] uvs_frame_callback cb,
                                                                  IntPtr userData);

        [DllImport(uvsdll)]
        public static extern int uvs_set_audio_enc_frame_callback(IntPtr handle,
                                                                  [MarshalAs(UnmanagedType.FunctionPtr)] uvs_frame_callback cb,
                                                                  IntPtr userData);

        [DllImport(uvsdll)]
        public static extern int uvs_lock_audio_raw_frame(IntPtr handle, out FrameInfo info, uint waitMilliSec);

        [DllImport(uvsdll)]
        public static extern int uvs_unlock_audio_raw_frame(IntPtr handle);

        [DllImport(uvsdll)]
        public static extern int uvs_copy_audio_raw_frame(IntPtr handle, ref FrameInfo info, uint waitMilliSec);

        [DllImport(uvsdll, EntryPoint = "uvs_media_server_rtsp_createW")]
        public static extern int uvs_media_server_rtsp_create(UInt16 rtspPort,
                                                              UInt16 httpTunnerPort,
                                                              [MarshalAs(UnmanagedType.LPTStr)] string username,
                                                              [MarshalAs(UnmanagedType.LPTStr)] string password);

        [DllImport(uvsdll)]
        public static extern int uvs_media_server_rtsp_destroy(UInt16 rtspPort);

        [DllImport(uvsdll, EntryPoint = "uvs_media_stream_rtsp_startW")]
        public static extern int uvs_media_stream_rtsp_start(IntPtr handle,
                                                             int streamIndex,
                                                             UInt16 rtspPort,
                                                             int hasAudio,
                                                             [MarshalAs(UnmanagedType.LPTStr)] string sessionName,
                                                             IntPtr rtpMulticast);

        [DllImport(uvsdll)]
        public static extern int uvs_media_stream_rtsp_stop(IntPtr handle, int streamIndex);

        [DllImport(uvsdll, EntryPoint = "uvs_media_stream_rtsp_get_urlW")]
        public static extern int uvs_media_stream_rtsp_get_url(IntPtr handle, int streamIndex, out URLInfo info);

        [DllImport(uvsdll, EntryPoint = "uvs_media_file_rtsp_startW")]
        public static extern int uvs_media_file_rtsp_start([MarshalAs(UnmanagedType.LPTStr)] string filename,
                                                           UInt16 rtspPort,
                                                           int hasAudio,
                                                           [MarshalAs(UnmanagedType.LPTStr)] string sessionName);

        [DllImport(uvsdll, EntryPoint = "uvs_media_file_rtsp_stopW")]
        public static extern int uvs_media_file_rtsp_stop([MarshalAs(UnmanagedType.LPTStr)] string filename);

        [DllImport(uvsdll, EntryPoint = "uvs_media_file_rtsp_get_urlW")]
        public static extern int uvs_media_file_rtsp_get_url([MarshalAs(UnmanagedType.LPTStr)] string filename, out URLInfo info);

        [DllImport(uvsdll, EntryPoint = "uvs_media_stream_rtmp_sendW")]
        public static extern int uvs_media_stream_rtmp_send(IntPtr handle,
                                                            int streamIndex,
                                                            [MarshalAs(UnmanagedType.LPTStr)] string rtmpURL,
                                                            int hasAudio);

        [DllImport(uvsdll)]
        public static extern int uvs_media_stream_rtmp_stop(IntPtr handle, int streamIndex);

        [DllImport(uvsdll, EntryPoint = "uvs_media_stream_rtmp_get_send_urlW")]
        public static extern int uvs_media_stream_rtmp_get_send_url(IntPtr handle, int streamIndex, out URLInfo info);

        [DllImport(uvsdll, EntryPoint = "uvs_media_file_rtmp_sendW")]
        public static extern int uvs_media_file_rtmp_send([MarshalAs(UnmanagedType.LPTStr)] string filename,
                                                          [MarshalAs(UnmanagedType.LPTStr)] string rtmpURL,
                                                          int hasAudio);

        [DllImport(uvsdll, EntryPoint = "uvs_media_file_rtmp_get_progressW")]
        public static extern int uvs_media_file_rtmp_get_progress([MarshalAs(UnmanagedType.LPTStr)] string filename, out int progress);

        [DllImport(uvsdll, EntryPoint = "uvs_media_file_rtmp_stopW")]
        public static extern int uvs_media_file_rtmp_stop(IntPtr handle);

        [DllImport(uvsdll, EntryPoint = "uvs_media_file_rtmp_get_send_urlW")]
        public static extern int uvs_media_file_rtmp_get_send_url(IntPtr handle, out URLInfo info);

        [DllImport(uvsdll, EntryPoint = "uvs_media_stream_ndi_createW")]
        public static extern int uvs_media_stream_ndi_create(IntPtr handle,
                                                             [MarshalAs(UnmanagedType.LPTStr)] string filename,
                                                             [MarshalAs(UnmanagedType.LPTStr)] string sourceName,
                                                             [MarshalAs(UnmanagedType.LPTStr)] string groupName,
                                                             int asyncMode);

        [DllImport(uvsdll)]
        public static extern int uvs_media_stream_ndi_config(IntPtr handle, IntPtr convert, int skipFrameRate);

        [DllImport(uvsdll)]
        public static extern int uvs_media_stream_ndi_start(IntPtr handle, int hasAudio);

        [DllImport(uvsdll)]
        public static extern int uvs_media_stream_ndi_stop(IntPtr handle);

        [DllImport(uvsdll)]
        public static extern int uvs_media_stream_ndi_destroy(IntPtr handle);

        [DllImport(uvsdll, EntryPoint = "uvs_mp4_file_get_statusW")]
        public static extern int uvs_mp4_file_get_status([MarshalAs(UnmanagedType.LPTStr)] string filename, out FileStatus status);

        [DllImport(uvsdll, EntryPoint = "uvs_mp4_file_repairW")]
        public static extern int uvs_mp4_file_repair([MarshalAs(UnmanagedType.LPTStr)] string filename,
                                                     [MarshalAs(UnmanagedType.LPTStr)] string saveFilename);

        [DllImport(uvsdll)]
        public static extern int uvs_mp4_file_repair_cancel();

        [DllImport(uvsdll)]
        public static extern int uvs_mp4_file_get_repair_progress(out int progress);

        [DllImport(uvsdll, EntryPoint = "uvs_mp4_file_cutW")]
        public static extern int uvs_mp4_file_cut([MarshalAs(UnmanagedType.LPTStr)] string filename,
                                                  int beginMilliSec, int endMilliSec,
                                                  [MarshalAs(UnmanagedType.LPTStr)] string saveFilename);

        [DllImport(uvsdll)]
        public static extern int uvs_mp4_file_get_cut_progress(out int progress);

        [DllImport(uvsdll, EntryPoint = "uvs_mp4_file_add_titleW")]
        public static extern int uvs_mp4_file_add_title([MarshalAs(UnmanagedType.LPTStr)] string filename,
                                                        int beginMilliSec,
                                                        [In, Out] TitleInfo[] title,
                                                        int titleNum,
                                                        int titleMilliSec,
                                                        [MarshalAs(UnmanagedType.LPTStr)] string saveFilename);

        [DllImport(uvsdll)]
        public static extern int uvs_mp4_file_get_title_progress(out int progress);

        [DllImport(uvsdll, EntryPoint = "uvs_mp4_file_mergeW")]
        public static extern int uvs_mp4_file_merge(IntPtr[] fileArray,
                                                    int arrayNum,
                                                    [MarshalAs(UnmanagedType.LPTStr)] string saveFilename);

        [DllImport(uvsdll)]
        public static extern int uvs_mp4_file_get_merge_progress(out int progress);

        public static implicit operator bool(Dev dev)
        {
            return dev.IsValid();
        }

        public static int ToCOLORREF(int argb)
        {
            return ((argb & 0xff) << 16) | (argb & 0xff00) | ((argb >> 16) & 0xff);
        }

        public Dev()
        {
            // sdk init
            uvs_media_init(0);
        }

        public Dev(int videoIndex, int audioIndex, out int result) : this()
        {
            result = DeviceOpen(videoIndex, audioIndex);
        }

        public void Dispose()
        {
            DeviceClose();

            // sdk deinit
            uvs_media_exit();
        }

        public bool IsValid()
        {
            return handle != IntPtr.Zero;
        }

        public int DeviceOpen(int videoIndex, int audioIndex)
        {
            if (videoIndex >= 0)
            {
                // enum video capture device
                var num = max_dev_num;
                var videoDev = new DevInfo[num];
                var r = uvs_enum_device(uvs_dev_video_capture, videoDev, ref num);
                if (r == UVS_OK && videoIndex < num)
                {
                    // enum audio capture device
                    num = max_dev_num;
                    var audioDev = new DevInfo[num];
                    r = uvs_enum_device(uvs_dev_audio_capture, audioDev, ref num);
                    if (audioIndex < 0 || (r == UVS_OK && audioIndex < num))
                    {
                        r = DeviceOpen(ref videoDev[videoIndex]);
                        if (r == UVS_OK && audioIndex >= 0)
                        {
                            // set audio capture device
                            r = SetAudioDevice(uvs_dev_audio_capture, ref audioDev[audioIndex]);
                        }
                        return r;
                    }
                }
            }

            return UVS_ERR_INVALIDARG;
        }

        public int DeviceOpen(ref DevInfo info)
        {
            int r;
            handle = uvs_dev_open(ref info, out r);
            return r;
        }

        public void DeviceClose()
        {
            uvs_dev_close(handle);
            handle = IntPtr.Zero;
        }

        public int SetAudioDevice(int devType, ref DevInfo info)
        {
            return uvs_set_audio_device(handle, devType, ref info);
        }

        public int DeviceStart()
        {
            return uvs_dev_control(handle, uvs_dev_run);
        }

        public int DevicePause()
        {
            return uvs_dev_control(handle, uvs_dev_pause);
        }

        public int DeviceStop()
        {
            return uvs_dev_control(handle, uvs_dev_stop);
        }

        public int audioCodec
        {
            get { AudioFormat dummy; int x; return uvs_get_audio_property(handle, out dummy, out x) == UVS_OK ? x : uvs_audio_codec_none; }
            set { uvs_set_audio_property(handle, IntPtr.Zero, value); }
        }

        public bool mute
        {
            get { return volume == 0; }
            set { uvs_set_audio_mute(handle, value ? 1 : 0); }
        }

        public int GetVideoEffectRange(int effect, out int minValue, out int maxValue, out int step, out int defaultValue)
        {
            return uvs_get_video_effect_range(handle, effect, out minValue, out maxValue, out step, out defaultValue);
        }

        public int volume
        {
            get { int x; return uvs_get_audio_volume(handle, out x) == UVS_OK ? x : 0; }
            set { uvs_set_audio_volume(handle, value); }
        }

        public int balance
        {
            get { int x; return uvs_get_audio_balance(handle, out x) == UVS_OK ? x : 0; }
            set { uvs_set_audio_balance(handle, value); }
        }

        public int GetVideoProperty(out VideoFormat format)
        {
            return uvs_get_video_property(handle, uvs_source_any, out format);
        }

        public int SetVideoProperty(ref VideoFormat format)
        {
            return uvs_set_video_property(handle, uvs_source_any, ref format);
        }

        public bool mirror
        {
            get { int x, dummy; return uvs_get_video_mirror(handle, out x, out dummy) == UVS_OK ? x != 0 : false; }
            set { int x, dummy; uvs_get_video_mirror(handle, out x, out dummy); uvs_set_video_mirror(handle, value ? 1 : 0, dummy); }
        }

        public bool flip
        {
            get { int x, dummy; return uvs_get_video_mirror(handle, out dummy, out x) == UVS_OK ? x != 0: false; }
            set { int x, dummy; uvs_get_video_mirror(handle, out dummy, out x); uvs_set_video_mirror(handle, dummy, value ? 1 : 0); }
        }

        public int GetVideoStatus(out int status, out int mode)
        {
            return uvs_get_video_status(handle, out status, out mode);
        }

        public int brightness
        {
            get { int x; return uvs_get_video_effect(handle, uvs_video_brightness, out x) == UVS_OK ? x : 0; }
            set { uvs_set_video_effect(handle, uvs_video_brightness, value); }
        }

        public int contrast
        {
            get { int x; return uvs_get_video_effect(handle, uvs_video_contrast, out x) == UVS_OK ? x : 0; }
            set { uvs_set_video_effect(handle, uvs_video_contrast, value); }
        }

        public int saturation
        {
            get { int x; return uvs_get_video_effect(handle, uvs_video_saturation, out x) == UVS_OK ? x : 0; }
            set { uvs_set_video_effect(handle, uvs_video_saturation, value); }
        }

        public int gamma
        {
            get { int x; return uvs_get_video_effect(handle, uvs_video_gamma, out x) == UVS_OK ? x : 0; }
            set { uvs_set_video_effect(handle, uvs_video_gamma, value); }
        }

        public int SetVideoEncodeConfig(int streamIndex, int codec, ref EncodeConfig config)
        {
            return uvs_set_video_encode_config(handle, streamIndex, codec, ref config);
        }

        public int GetVideoEncodeConfig(int streamIndex, out int codec, out EncodeConfig config)
        {
            return uvs_get_video_encode_config(handle, streamIndex, out codec, out config);
        }

        public int RequestVideoKeyframe(int streamIndex)
        {
            return uvs_request_video_key_frame(handle, streamIndex);
        }

        public int GetVideoEncodeStatus(int streamIndex, out EncodeStatus status)
        {
            return uvs_get_video_encode_status(handle, streamIndex, out status);
        }

        public int EncodeStart(int streamIndex)
        {
            return uvs_start_encode(handle, streamIndex);
        }

        public int EncodeStop(int streamIndex)
        {
            return uvs_stop_encode(handle, streamIndex);
        }

        public int SetRecMetaData(int streamIndex, string title = null, string comment = null, string artist = null, string genre = null, string composer = null)
        {
            return uvs_set_record_metadata(handle, streamIndex, title, comment, artist, genre, composer);
        }

        public int RecordStart(int streamIndex, string filename1, bool recAudio, string filename2 = null, bool repairSupport = true, uint fileSize = 0, uint fileDuration = 0)
        {
            return uvs_start_record(handle, streamIndex, filename1, filename2, recAudio ? 1 : 0, repairSupport ? 1 : 0, fileSize, fileDuration);
        }

        public int RecordPause(int streamIndex, bool recPause, bool requestKeyframe = true)
        {
            return uvs_pause_record(handle, streamIndex, recPause ? 0 : 1, requestKeyframe ? 1 : 0);
        }

        public int RecordStop(int streamIndex)
        {
            return uvs_stop_encode(handle, streamIndex);
        }

        public int GetRecFilename(int streamIndex, [In, Out] RecFileName[] filename, ref int num)
        {
            return uvs_get_record_filename(handle, streamIndex, filename, ref num);
        }

        public int PreviewStart(IntPtr hwnd, int dispType = uvs_disp_type_d3d)
        {
            return uvs_start_preview(handle, hwnd, dispType);
        }

        public bool freeze
        {
            get { int x; return uvs_get_preview_freeze(handle, out x) == UVS_OK ? x != 0 : false; }
            set { uvs_set_preview_freeze(handle, value ? 1 : 0); }
        }

        public int PreviewRect(IntPtr wndRect, IntPtr videoRect, int fillColor = 0)
        {
            return uvs_set_preview_rect(handle, wndRect, videoRect, fillColor);
        }

        public int PreviewStop()
        {
            return uvs_stop_preview(handle);
        }

        public int SetTimeOSD(int osdIndex, int x, int y, string timeFormat, ref FontInfo info)
        {
            return uvs_set_time_osd(handle, osdIndex, x, y, timeFormat, ref info);
        }

        public int SetTextOSD(int osdIndex, int x, int y, int width, int height, string text, ref FontInfo info)
        {
            return uvs_set_text_osd(handle, osdIndex, x, y, width, height, text, ref info);
        }

        public int SetImageOSD(int osdIndex, int x, int y, int width, int height, int opacity, string filename)
        {
            return uvs_set_image_osd(handle, osdIndex, x, y, width, height, opacity, filename);
        }

        public int SetRectOSD(int osdIndex, int x, int y, int width, int height, ref StyleInfo info)
        {
            return uvs_set_rect_osd(handle, osdIndex, x, y, width, height, ref info);
        }

        public int SetEllipseOSD(int osdIndex, int x, int y, int width, int height, ref StyleInfo info)
        {
            return uvs_set_ellipse_osd(handle, osdIndex, x, y, width, height, ref info);
        }

        public int SetLineOSD(int osdIndex, int x0, int y0, int x1, int y1, ref LineInfo info)
        {
            return uvs_set_line_osd(handle, osdIndex, x0, y0, x1, y1, ref info);
        }

        public int VideoOSDControl(int osdIndex, int cmd, ref int param0, ref int param1)
        {
            return uvs_osd_control(handle, osdIndex, cmd, ref param0, ref param1);
        }

        public int CaptureSnapshot(string filename, IntPtr convert, uint jpegQuality = 100)
        {
            return uvs_save_video_snapshot(handle, filename, convert, jpegQuality);
        }

        public int SetVideoRawFrameCallback([MarshalAs(UnmanagedType.FunctionPtr)] uvs_frame_callback cb, IntPtr userData)
        {
            return uvs_set_video_raw_frame_callback(handle, cb, userData);
        }

        public int SetVideoEncodeFrameCallback(int streamIndex, [MarshalAs(UnmanagedType.FunctionPtr)] uvs_frame_callback cb, IntPtr userData)
        {
            return uvs_set_video_enc_frame_callback(handle, streamIndex, cb, userData);
        }

        public int LockVideoRawFrame(out FrameInfo info, uint waitMilliSec = 1000)
        {
            return uvs_lock_video_raw_frame(handle, out info, waitMilliSec);
        }

        public int UnlockVideoRawFrame()
        {
            return uvs_unlock_video_raw_frame(handle);
        }

        public int CopyVideoFrame(IntPtr convert, ref FrameInfo info, uint waitMilliSec = 1000)
        {
            return uvs_copy_video_frame(handle, convert, ref info, waitMilliSec);
        }

        public int SetAudioRawFrameCallback([MarshalAs(UnmanagedType.FunctionPtr)] uvs_frame_callback cb, IntPtr userData)
        {
            return uvs_set_audio_raw_frame_callback(handle, cb, userData);
        }

        public int SetAudioEncodeFrameCallback([MarshalAs(UnmanagedType.FunctionPtr)] uvs_frame_callback cb, IntPtr userData)
        {
            return uvs_set_audio_enc_frame_callback(handle, cb, userData);
        }

        public int LockAudioRawFrame(out FrameInfo info, uint waitMilliSec = 1000)
        {
            return uvs_lock_audio_raw_frame(handle, out info, waitMilliSec);
        }

        public int UnlockAudioRawFrame()
        {
            return uvs_unlock_audio_raw_frame(handle);
        }

        public int CopyAudioRawFrame(ref FrameInfo info, uint waitMilliSec = 1000)
        {
            return uvs_copy_audio_raw_frame(handle, ref info, waitMilliSec);
        }

        public IntPtr handle { get; private set; }
    }
}
