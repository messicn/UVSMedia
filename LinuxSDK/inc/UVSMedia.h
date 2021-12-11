
#ifndef __UVS_MEDIA_H__6E72C738_BF82_4CCB_A785_F454D593FFF2__INCLUDED_
#define __UVS_MEDIA_H__6E72C738_BF82_4CCB_A785_F454D593FFF2__INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#define UVS_OK 0
#define UVS_ERR (-1)
#define UVS_ERR_OUTOFMEMORY (-2)
#define UVS_ERR_INVALIDARG (-3)
#define UVS_ERR_WAIT_TIMEOUT (-4)
#define UVS_ERR_NOT_INITIALIZED (-5)
#define UVS_ERR_NOT_ENOUGH_BUFFER (-6)
#define UVS_ERR_NOT_READY (-7)
#define UVS_ERR_NOT_SUPPORT (-8)
#define UVS_ERR_FILE_OPEN (-9)
#define UVS_ERR_ALREADY_EXISTS (-10)

typedef void* uvsobj_handle;
#define UVS_STREAM_ALL (-1)

typedef struct {
	int x;
	int y;
	int width;
	int height;
} uvs_rect_t;

typedef enum {
	uvs_draw_stretch,
	uvs_draw_center
} uvs_draw_mode_e;

typedef enum {
	uvs_dev_run,
	uvs_dev_stop
} uvs_dev_state_e;

typedef enum {
	uvs_sdl_event_none,
	uvs_sdl_event_window = 1,
	uvs_sdl_event_key_down = 2,
	uvs_sdl_event_key_up = 4,
	uvs_sdl_event_mouse_move = 8,
	uvs_sdl_event_mouse_down = 16,
	uvs_sdl_event_mouse_up = 32,
	uvs_sdl_event_mouse_wheel = 64
} uvs_sdl_event_e;

typedef struct {
	uvs_sdl_event_e type;
	uint32_t timestamp;
	union {
		uint8_t event;	  // SDL_WindowEventID
		uint8_t scancode; // SDL physical key code - see ::SDL_Scancode for details
		uint8_t button;	  // The mouse button index
	};
	uint8_t repeat; // Non-zero if this is a key repeat
	uint8_t clicks; // 1 for mouse single-click, 2 for double-click, etc.
	uint8_t direction; // Set to one of the SDL_MOUSEWHEEL_* defines. When FLIPPED the values in X and Y will be opposite. Multiply by -1 to change them back
	int x; // X coordinate, relative to window
	int y; // Y coordinate, relative to window
	union {
		int data1; // SDL_WindowEvent event dependent data
		int xrel;  // SDL_MouseMotionEvent The relative motion in the X direction
	};
	union {
		int data2; // SDL_WindowEvent event dependent data
		int yrel;  // SDL_MouseMotionEvent The relative motion in the Y direction
	};
} uvs_sdl_event_t;

typedef struct {
	uint32_t devType;
	uint32_t devVersion;
	char devDate[16];
	uint8_t devSN[16];
} uvs_hardware_info_t;

typedef enum {
	uvs_video_brightness,
	uvs_video_contrast,
	uvs_video_hue,
	uvs_video_saturation,
	uvs_video_sharpness,
	uvs_video_gamma,
	uvs_video_gain
} uvs_video_effect_e;

typedef enum {
	uvs_window_normal,
	uvs_window_fullscreen = 1,
	uvs_window_opengl = 2,
	uvs_window_vulkan = 4,
	uvs_window_title = 8,
	uvs_window_center = 16,
	uvs_window_always_on_top = 32,
	uvs_window_allow_highdpi = 64
} uvs_window_e;

typedef enum {
	uvs_audio_codec_none,
	uvs_audio_codec_MP3,
	uvs_audio_codec_AAC
} uvs_audio_codec_e;

typedef enum {
	uvs_video_codec_none,
	uvs_video_codec_hw_h264,
	uvs_video_codec_hw_h265,
	uvs_video_codec_hw_jpeg,
	uvs_video_codec_intel_h264,
	uvs_video_codec_intel_h265,
	uvs_video_codec_intel_jpeg,
	uvs_video_codec_nvidia_h264,
	uvs_video_codec_nvidia_h265,
	uvs_video_codec_sw_h264,
	uvs_video_codec_sw_x264
} uvs_video_codec_e;

typedef enum {
	uvs_target_usage_quality,
	uvs_target_usage_balance,
	uvs_target_usage_performance
} uvs_target_usage_e;

typedef enum {
	uvs_codec_profile_auto,
	uvs_codec_profile_baseline,
	uvs_codec_profile_main,
	uvs_codec_profile_high
} uvs_codec_profile_e;

typedef enum {
	uvs_avc_entropy_CABAC,
	uvs_avc_entropy_CAVLC
} uvs_avc_entropy_e;

typedef enum {
	uvs_video_rcmode_VBR,
	uvs_video_rcmode_CBR,
	uvs_video_rcmode_CQP,
	uvs_video_rcmode_AVBR
} uvs_video_rcmode_e;

typedef enum {
	uvs_rotate_none,
	uvs_rotate_90,
	uvs_rotate_180,
	uvs_rotate_270
} uvs_rotate_mode_e;

typedef enum {
	uvs_scale_usage_performance,
	uvs_scale_usage_balance,
	uvs_scale_usage_quality,
	uvs_scale_usage_high_quality
} uvs_scale_usage_e;

typedef struct {
	uvs_target_usage_e targetUsage;
	uvs_codec_profile_e codecProfile;
	uvs_avc_entropy_e entropyCoding; // AVC(h264) entropy coding mode
	uvs_scale_usage_e scaleUsage;
	int scaleWidth; // destination picture width
	int scaleHeight; // destination picture height
	int cropLeft;
	int cropTop;
	int cropWidth;
	int cropHeight;
	float frameRate;
	uvs_video_rcmode_e rcMode;
	int encBitRate; // kbit/sec
	int maxBitRate; // kbit/sec
	int encQuality; // encoder quality
	int GOPLength;
} uvs_encode_config_t;

typedef struct {
	int inputFrames;
	int encodeFrames;
	float inputFrameRate;
	float encodeFrameRate;
} uvs_encode_status_t;

typedef enum {
	uvs_frame_NONE,
	uvs_frame_video_YUY2,
	uvs_frame_video_UYVY,
	uvs_frame_video_YV12,
	uvs_frame_video_I420,
	uvs_frame_video_NV12,
	uvs_frame_video_NV21,
	uvs_frame_video_I422,
	uvs_frame_video_I444,
	uvs_frame_video_BGR24, // BGR little endian (rgb in memory)
	uvs_frame_video_RGB24, // RGB little endian (bgr in memory)
	uvs_frame_video_ARGB32, // ARGB little endian (bgra in memory)
	uvs_frame_video_RGBA32, // RGBA little endian (abgr in memory)
	uvs_frame_video_ABGR32, // ABGR little endian (rgba in memory)
	uvs_frame_video_BGRA32, // BGRA little endian (argb in memory)
	uvs_frame_video_MJPG = 37,
	uvs_frame_video_H264_IDR = 40,
	uvs_frame_video_H264_I,
	uvs_frame_video_H264_P,
	uvs_frame_video_H264_B,
	uvs_frame_video_H265_IDR = 50,
	uvs_frame_video_H265_I,
	uvs_frame_video_H265_P,
	uvs_frame_video_H265_B,
	uvs_frame_audio_PCM = 70,
	uvs_frame_audio_MP3,
	uvs_frame_audio_AAC
} uvs_frame_type_e;

typedef struct {
	uvs_frame_type_e frameType;
	int audioChannels;
	int samplesPerSec;
	int bitsPerSample;
} uvs_audio_format_t;

typedef struct {
	uvs_frame_type_e frameType;
	int videoWidth;
	int videoHeight;
	float frameRate;
} uvs_video_format_t;

typedef struct {
	uvs_frame_type_e frameType;
	union
	{
		uint16_t videoWidth;
		uint16_t audioChannels;
	};
	union
	{
		uint16_t videoHeight;
		uint16_t audioBitsPerSample;
	};
	union
	{
		uint16_t videoDataStride[2];
		uint32_t audioSamplesPerSec;
	};
	uint32_t frameDataLen;
	int64_t timeStamp;
	uint8_t *frameData;
} uvs_frame_info_t;

typedef struct {
	uvs_frame_type_e frameType;
	bool bMirror;
	bool bFlip;
	int cropLeft;
	int cropTop;
	int cropWidth;
	int cropHeight;
	int scaleWidth;
	int scaleHeight;
	uvs_scale_usage_e scaleUsage;
	uvs_rotate_mode_e rotateMode;
} uvs_frame_convert_t;

#define UVS_NAME_LEN 128

typedef struct {
	char szFriendlyDevName[UVS_NAME_LEN];
} uvs_dev_info_t;

typedef enum {
	uvs_dev_video_capture,
	uvs_dev_audio_capture,
	uvs_dev_audio_renderer
} uvs_dev_type_e;

typedef enum {
	uvs_dev_closed,
	uvs_dev_changed
} uvs_dev_notify_e;

typedef void (*pUVSDeviceCallback)(uvs_dev_notify_e notify, const uvs_dev_info_t *info, uvsobj_handle obj, void *pUserData);

#define UVS_FILENAME_LEN 260

typedef struct {
	char szFileName[UVS_FILENAME_LEN];
} uvs_filename_t;

#define UVS_URL_LEN 256

typedef struct {
	char szURL[UVS_URL_LEN];
} uvs_url_t;

typedef void (*pUVSEventCallback)(uvsobj_handle obj, const uvs_sdl_event_t *event, void *pUserData);
typedef void (*pUVSFrameCallback)(uvsobj_handle obj, const uvs_frame_info_t *frame, void *pUserData);

typedef enum {
	uvs_osd_index_preview_enc = 0, /* index [uvs_osd_index_preview_enc, uvs_time_osd_index_preview_enc], OSD preview + encode */
	uvs_time_osd_index_preview_enc = 255, /* time OSD preview + encode */
	uvs_osd_index_preview_only, /* index [uvs_osd_index_preview_only, uvs_time_osd_index_preview_only], OSD preview only */
	uvs_time_osd_index_preview_only = 511, /* time OSD preview only */
	uvs_osd_index_frame_preview, /* index [uvs_osd_index_frame_preview, uvs_time_osd_index_frame_preview], OSD frame preview */
	uvs_time_osd_index_frame_preview = 767 /* time OSD frame preview */
} uvs_osd_index_e;

#define UVS_TIMEMODE_YMD_24H "%Y-%M-%D %H:%m:%s" /* 24 hours */
#define UVS_TIMEMODE_MDY_12H "%N %D %Y %h:%m:%s %t" /* 12 hours */

typedef enum {
	uvs_font_style_regular,
	uvs_font_style_bold,
	uvs_font_style_italic,
	uvs_font_style_bold_italic,
	uvs_font_style_underline = 4, /* composite attribute */
	uvs_font_style_strikeout = 8, /* composite attribute */
} uvs_font_style_e;

typedef enum {
	uvs_string_format_regular,
	uvs_string_rect_multiple_lines = 1
} uvs_string_format_e;

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t alpha;
} uvs_color_t;

typedef struct {
	char szFontName[UVS_NAME_LEN];
	int fontPointSize;
	int fontStyle; /* uvs_font_style_e */
	int stringFormat; /* uvs_string_format_e */
	uvs_color_t textColor;
	uvs_color_t textBkColor;
} uvs_font_info_t;

typedef enum {
	uvs_osd_enable,
	uvs_osd_delete,
	uvs_osd_delete_all,
	uvs_osd_get_count,
	uvs_osd_get_size,
	uvs_osd_get_position,
	uvs_osd_set_position,
	uvs_osd_get_font_size,
	uvs_osd_set_font_size,
	uvs_osd_get_color,
	uvs_osd_set_color,
	uvs_osd_get_opacity,
	uvs_osd_set_opacity,
	uvs_osd_get_clip_position, /* clip x, y position */
	uvs_osd_set_clip_position,
	uvs_osd_get_clip_size, /* clip width & height */
	uvs_osd_set_clip_size,
	uvs_osd_get_blink,
	uvs_osd_set_blink
} uvs_osd_cmd_e;

typedef struct {
	int lineSize;
	uvs_color_t edgeColor;
	uvs_color_t fillColor;
} uvs_style_info_t;

typedef struct {
	int lineSize;
	uvs_color_t lineColor;
} uvs_line_info_t;

typedef struct {
	const char *ipAddress;
	uint16_t ipPort;
} uvs_rtp_multicast_t;

typedef struct {
	uvs_audio_codec_e audioCodec;
	uvs_video_codec_e videoCodec;
	int audioDuration; /* audio track duration in milliseconds */
	int videoDuration; /* video track duration in milliseconds */
	int videoWidth;
	int videoHeight;
	float videoFrameRate;
} uvs_mp4_file_status_t;

typedef enum {
	uvs_mp4_file_begining,
	uvs_mp4_file_ending = -1
} mp4_file_positon_e;

typedef struct {
	uvs_font_info_t textFont;
	int x, y;
	int width, height;
	int imageOpacity;
	const char *szTitleImageFile;
	const char *szTitleText;
} uvs_mp4_file_title_t;

int uvs_media_init(int flags);
void uvs_media_exit(void);
int uvs_get_version(void);

int uvs_enum_device(uvs_dev_type_e devType, uvs_dev_info_t devInfo[], int *devNum);
int uvs_set_device_callback(pUVSDeviceCallback pCB, void *pUserData);
int uvs_get_device_count(void);

int uvs_query_video_encoder(uvsobj_handle obj, uvs_video_codec_e videoCodec);
int uvs_calc_buffer_size(uvs_frame_type_e frameType, int videoWidth, int videoHeight, int stride);

int uvs_set_nosignal_image(const char *szFileName, uvs_draw_mode_e drawMode, const uvs_color_t *bkColor);

uvsobj_handle uvs_dev_open(const uvs_dev_info_t *devInfo, int *result);
int uvs_dev_close(uvsobj_handle obj);

int uvs_get_dev_info(uvsobj_handle obj, uvs_dev_info_t *devInfo);
int uvs_query_hardware_info(uvsobj_handle obj, uvs_hardware_info_t *hwInfo);

int uvs_enum_audio_format(uvsobj_handle obj, uvs_audio_format_t formats[], int *formatNum);
int uvs_enum_video_format(uvsobj_handle obj, uvs_video_format_t formats[], int *formatNum);

int uvs_set_audio_device(uvsobj_handle obj, uvs_dev_type_e devType, const uvs_dev_info_t *devInfo);

int uvs_dev_control(uvsobj_handle obj, uvs_dev_state_e state);

int uvs_get_audio_property(uvsobj_handle obj, uvs_audio_format_t *format, uvs_audio_codec_e *audioCodec);
int uvs_set_audio_property(uvsobj_handle obj, const uvs_audio_format_t *format, uvs_audio_codec_e audioCodec);

int uvs_set_audio_mute(uvsobj_handle obj, bool bMute);
int uvs_get_audio_volume(uvsobj_handle obj, int *volume);
int uvs_set_audio_volume(uvsobj_handle obj, int volume);
int uvs_get_audio_balance(uvsobj_handle obj, int *balance);
int uvs_set_audio_balance(uvsobj_handle obj, int balance);

int uvs_get_video_input(uvsobj_handle obj, int *currentIndex, int inputTypes[], int *inputNum);
int uvs_set_video_input(uvsobj_handle obj, int inputIndex);

int uvs_get_video_effect_range(uvsobj_handle obj, uvs_video_effect_e effect, int *minVal, int *maxVal, int *stepDelta, int *defaultVal);
int uvs_get_video_effect(uvsobj_handle obj, uvs_video_effect_e effect, int *param);
int uvs_set_video_effect(uvsobj_handle obj, uvs_video_effect_e effect, int param);

int uvs_get_video_property(uvsobj_handle obj, uvs_video_format_t *format);
int uvs_set_video_property(uvsobj_handle obj, const uvs_video_format_t *format);

int uvs_get_video_mirror(uvsobj_handle obj, bool *horizMirror, bool *vertMirror);
int uvs_set_video_mirror(uvsobj_handle obj, bool horizMirror, bool vertMirror);
int uvs_get_video_status(uvsobj_handle obj, bool *videoSignal, bool *videoMode);

int uvs_set_video_encode_config(uvsobj_handle obj, int streamIndex, uvs_video_codec_e videoCodec, const uvs_encode_config_t *config);
int uvs_get_video_encode_config(uvsobj_handle obj, int streamIndex, uvs_video_codec_e *videoCodec, uvs_encode_config_t *config);

int uvs_start_encode(uvsobj_handle obj, int streamIndex);
int uvs_stop_encode(uvsobj_handle obj, int streamIndex);

int uvs_request_video_key_frame(uvsobj_handle obj, int streamIndex);
int uvs_get_video_encode_status(uvsobj_handle obj, int streamIndex, uvs_encode_status_t *info);

int uvs_set_record_metadata(uvsobj_handle obj, int streamIndex, const char *szTitle, const char *szComment, const char *szArtist, const char *szGenre, const char *szComposer);
int uvs_start_record(uvsobj_handle obj, int streamIndex, const char *szSaveFile1, const char *szSaveFile2, bool bRecAudio, bool bRepairSupport, uint32_t uKBData, uint32_t uMilliSec);
int uvs_get_record_filename(uvsobj_handle obj, int streamIndex, uvs_filename_t fileName[], int *fileNum);
int uvs_pause_record(uvsobj_handle obj, int streamIndex, bool bRecResume, bool bRequestKeyFrame);
int uvs_stop_record(uvsobj_handle obj, int streamIndex);

int uvs_start_preview(uvsobj_handle obj, const void *wnd);
int uvs_rect_preview(uvsobj_handle obj, const uvs_rect_t *rect, uvs_window_e style, const char *title, uvs_rect_t *rc);
int uvs_set_preview_callback(uvsobj_handle obj, uvs_sdl_event_e eventMask, pUVSEventCallback pCB, void *pUserData);
int uvs_set_preview_freeze(uvsobj_handle obj, bool bFreeze);
int uvs_get_preview_freeze(uvsobj_handle obj, bool *isFreeze);
int uvs_set_preview_rect(uvsobj_handle obj, const uvs_rect_t *wndRect, const uvs_rect_t *cropRect, const uvs_color_t *bkColor);
int uvs_stop_preview(uvsobj_handle obj);

int uvs_set_time_osd(uvsobj_handle obj, int osdIndex, int x, int y, const char *szTimeMode, const uvs_font_info_t *info);
int uvs_set_text_osd(uvsobj_handle obj, int osdIndex, int x, int y, int width, int height, const char *szText, const uvs_font_info_t *info);
int uvs_set_image_osd(uvsobj_handle obj, int osdIndex, int x, int y, int width, int height, int imgOpacity, const char *szFileName);
int uvs_set_rect_osd(uvsobj_handle obj, int osdIndex, int x, int y, int width, int height, const uvs_style_info_t *info);
int uvs_set_ellipse_osd(uvsobj_handle obj, int osdIndex, int x, int y, int width, int height, const uvs_style_info_t *info);
int uvs_set_line_osd(uvsobj_handle obj, int osdIndex, int x0, int y0, int x1, int y1, const uvs_line_info_t *info);
int uvs_osd_control(uvsobj_handle obj, int osdIndex, uvs_osd_cmd_e cmd, void *param0, void *param1);

uvsobj_handle uvs_create_frame_preview(const void *wnd, bool bAsync);
uvsobj_handle uvs_create_rect_preview(const uvs_rect_t *rect, uvs_window_e style, bool bAsync, const char *title, uvs_rect_t *rc);
int uvs_set_frame_preview_callback(uvsobj_handle handle, uvs_sdl_event_e eventMask, pUVSEventCallback pCB, void *pUserData);
int uvs_frame_preview(uvsobj_handle handle, const uvs_frame_info_t *info);
int uvs_image_preview(uvsobj_handle handle, const char *szFileName);
int uvs_set_frame_preview_rect(uvsobj_handle handle, const uvs_rect_t *wndRect, const uvs_rect_t *cropRect, const uvs_color_t *bkColor);
int uvs_destroy_frame_preview(uvsobj_handle handle);

int uvs_set_video_raw_frame_callback(uvsobj_handle obj, pUVSFrameCallback pCB, void *pUserData);
int uvs_set_video_enc_frame_callback(uvsobj_handle obj, int streamIndex, pUVSFrameCallback pCB, void *pUserData);

int uvs_convert_video_frame(const uvs_frame_convert_t *frameConvert, const uvs_frame_info_t *src, uvs_frame_info_t *dst);
int uvs_save_video_frame(const char *szFileName, const uvs_frame_convert_t *frameConvert, const uvs_frame_info_t *info, int jpegParam);
int uvs_save_video_snapshot(uvsobj_handle obj, const char *szFileName, const uvs_frame_convert_t *frameConvert, int jpegParam);

int uvs_lock_video_raw_frame(uvsobj_handle obj, uvs_frame_info_t *info, uint32_t waitMilliSec);
int uvs_unlock_video_raw_frame(uvsobj_handle obj);
int uvs_copy_video_frame(uvsobj_handle obj, const uvs_frame_convert_t *frameConvert, uvs_frame_info_t *info, uint32_t waitMilliSec);

int uvs_set_audio_raw_frame_callback(uvsobj_handle obj, pUVSFrameCallback pCB, void *pUserData);
int uvs_set_audio_enc_frame_callback(uvsobj_handle obj, pUVSFrameCallback pCB, void *pUserData);

int uvs_lock_audio_raw_frame(uvsobj_handle obj, uvs_frame_info_t *info, uint32_t waitMilliSec);
int uvs_unlock_audio_raw_frame(uvsobj_handle obj);
int uvs_copy_audio_raw_frame(uvsobj_handle obj, uvs_frame_info_t *info, uint32_t waitMilliSec);

int uvs_media_server_rtsp_create(uint16_t rtspPort, uint16_t httpTunnerPort, const char *szUserName, const char *szPassword);
int uvs_media_server_rtsp_destroy(uint16_t rtspPort);

int uvs_media_stream_rtsp_start(uvsobj_handle obj, int streamIndex, uint16_t rtspPort, bool bHasAudio, const char *szSessionName, const uvs_rtp_multicast_t *rtpMulticast);
int uvs_media_stream_rtsp_stop(uvsobj_handle obj, int streamIndex);
int uvs_media_stream_rtsp_get_url(uvsobj_handle obj, int streamIndex, uvs_url_t *urlInfo);

int uvs_media_file_rtsp_start(const char *szFileName, uint16_t rtspPort, bool bHasAudio, const char *szSessionName);
int uvs_media_file_rtsp_stop(const char *szFileName);
int uvs_media_file_rtsp_get_url(const char *szFileName, uvs_url_t *urlInfo);

int uvs_media_stream_rtmp_send(uvsobj_handle obj, int streamIndex, const char *rtmpUrl, bool bHasAudio);
int uvs_media_stream_rtmp_stop(uvsobj_handle obj, int streamIndex);
int uvs_media_stream_rtmp_get_send_url(uvsobj_handle obj, int streamIndex, uvs_url_t *urlInfo);

int uvs_media_file_rtmp_send(const char *szFileName, const char *rtmpUrl, bool bHasAudio);
int uvs_media_file_rtmp_get_progress(const char *szFileName, int *progress);
int uvs_media_file_rtmp_stop(const char *szFileName);
int uvs_media_file_rtmp_get_send_url(const char *szFileName, uvs_url_t *urlInfo);

int uvs_media_stream_ndi_create(uvsobj_handle obj, const char *szSourceName, const char *szGroupName, const char *szXMLMetadata, bool bAsync);
int uvs_media_stream_ndi_config(uvsobj_handle obj, const uvs_frame_convert_t *frameConvert, int skipFrameRate);
int uvs_media_stream_ndi_start(uvsobj_handle obj, bool bHasAudio);
int uvs_media_stream_ndi_stop(uvsobj_handle obj);
int uvs_media_stream_ndi_destroy(uvsobj_handle obj);

int uvs_mp4_file_get_status(const char *szFileName, uvs_mp4_file_status_t *status);
int uvs_mp4_file_repair(const char *szFileName, const char *szOutputFile);
int uvs_mp4_file_repair_cancel(void);
int uvs_mp4_file_get_repair_progress(int *progress);
int uvs_mp4_file_cut(const char *szFileName, int beginMilliSec, int endMilliSec, const char *szOutputFile);
int uvs_mp4_file_get_cut_progress(int *progress);
int uvs_mp4_file_add_title(const char *szFileName, int beginMilliSec, const uvs_mp4_file_title_t title[], int titleNum, int titleMilliSec, const char *szOutputFile);
int uvs_mp4_file_get_title_progress(int *progress);
int uvs_mp4_file_merge(const char* const szFileName[], int fileNum, const char *szOutputFile);
int uvs_mp4_file_get_merge_progress(int *progress);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef __UVS_MEDIA_H__6E72C738_BF82_4CCB_A785_F454D593FFF2__INCLUDED_ */
