
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

#ifndef UVSAPI
#define UVSAPI __stdcall
#endif

typedef enum {
	uvs_property_audio_source_filter,
	uvs_property_video_crossbar,
	uvs_property_video_source_filter,
	uvs_property_video_preview_pin,
	uvs_property_video_capture_pin
} uvs_property_page_e;

typedef struct {
	DWORD devType;
	DWORD devVersion;
	char devDate[16];
	BYTE devSN[16];
} uvs_hardware_info_t;

typedef enum {
	uvs_draw_stretch,
	uvs_draw_center
} uvs_draw_mode_e;

typedef enum {
	uvs_dev_run,
	uvs_dev_pause,
	uvs_dev_stop
} uvs_dev_state_e;

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
	uvs_disp_type_ddraw,
	uvs_disp_type_d3d
} uvs_disp_type_e;

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
	uvs_target_usage_performance,
	uvs_target_usage_balance,
	uvs_target_usage_quality
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
	uvs_avc_entropy_e entropyCoding; /* AVC(h264) entropy coding mode */
	uvs_scale_usage_e scaleUsage;
	int scaleWidth; /* destination video width */
	int scaleHeight; /* destination video height */
	int cropLeft;
	int cropTop;
	int cropWidth;
	int cropHeight;
	float frameRate;
	uvs_video_rcmode_e rcMode;
	int encBitRate; /* kbits/sec */
	int maxBitRate; /* kbits/sec */
	int encQuality; /* encoder quality(1 ~ 51) */
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
	uvs_frame_video_BGR24, /* BGR little endian (rgb in memory) */
	uvs_frame_video_RGB24, /* RGB little endian (bgr in memory) */
	uvs_frame_video_ARGB32, /* ARGB little endian (bgra in memory) */
	uvs_frame_video_RGBA32, /* RGBA little endian (abgr in memory) */
	uvs_frame_video_ABGR32, /* ABGR little endian (rgba in memory) */
	uvs_frame_video_BGRA32, /* BGRA little endian (argb in memory) */
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

typedef enum {
	uvs_source_any,
	uvs_source_preview,
	uvs_source_capture
} uvs_source_type_e;

typedef struct {
	uvs_frame_type_e frameType;
	int videoWidth;
	int videoHeight;
	float frameRate;
} uvs_video_format_t;

typedef struct {
	uvs_frame_type_e frameType; /* frame type */
	union
	{
		USHORT videoWidth; /* video width in pixels */
		USHORT audioChannels; /* mono or stereo audio */
	};
	union
	{
		USHORT videoHeight; /* video height in pixels */
		USHORT audioBitsPerSample; /* audio sample bit depth */
	};
	union
	{
		USHORT videoDataStride[2]; /* one row in bytes for multiple planes */
		UINT audioSamplesPerSec; /* audio sample rate per-channel */
	};
	UINT frameDataLen; /* number of bytes */
	LONGLONG timeStamp; /* timestamp in micro seconds */
	BYTE *frameData; /* frame data */
} uvs_frame_info_t;

typedef struct {
	uvs_frame_type_e frameType;
	BOOL bMirror;
	BOOL bFlip;
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

typedef struct {
	WCHAR szFriendlyDevName[UVS_NAME_LEN];
} uvs_dev_info_tW;

typedef enum {
	uvs_dev_video_capture,
	uvs_dev_audio_capture,
	uvs_dev_audio_renderer
} uvs_dev_type_e;

typedef enum {
	uvs_dev_closed,
	uvs_dev_changed
} uvs_dev_notify_e;

typedef void (CALLBACK *pUVSDeviceCallback)(uvs_dev_notify_e notify, const uvs_dev_info_t *info, uvsobj_handle obj, void *pUserData);
typedef void (CALLBACK *pUVSDeviceCallbackW)(uvs_dev_notify_e notify, const uvs_dev_info_tW *info, uvsobj_handle obj, void *pUserData);

#define UVS_FILENAME_LEN 260

typedef struct {
	char szFileName[UVS_FILENAME_LEN];
} uvs_filename_t;

typedef struct {
	WCHAR szFileName[UVS_FILENAME_LEN];
} uvs_filename_tW;

#define UVS_URL_LEN 256

typedef struct {
	char szURL[UVS_URL_LEN];
} uvs_url_t;

typedef struct {
	WCHAR szURL[UVS_URL_LEN];
} uvs_url_tW;

typedef void (CALLBACK *pUVSFrameCallback)(uvsobj_handle obj, const uvs_frame_info_t *pFrameData, void *pUserData);
typedef void (CALLBACK *pUVSDrawCallback)(uvsobj_handle obj, void *pUserData);

typedef enum {
	uvs_osd_index_preview_enc = 0, /* index [uvs_osd_index_preview_enc, uvs_time_osd_index_preview_enc], OSD preview + encode */
	uvs_time_osd_index_preview_enc = 255, /* time OSD preview + encode */
	uvs_osd_index_preview_only, /* index [uvs_osd_index_preview_only, uvs_time_osd_index_preview_only], OSD preview only */
	uvs_time_osd_index_preview_only = 511 /* time OSD preview only */
} uvs_osd_index_e;

#define UVS_TIMEMODE_YMD_24H "%Y-%M-%D %H:%m:%s" /* 24 hours */
#define UVS_TIMEMODE_YMD_24H_W L"%Y-%M-%D %H:%m:%s" /* 24 hours */
#define UVS_TIMEMODE_MDY_12H "%N %D %Y %h:%m:%s %t" /* 12 hours */
#define UVS_TIMEMODE_MDY_12H_W L"%N %D %Y %h:%m:%s %t" /* 12 hours */

typedef enum {
	uvs_font_style_regular,
	uvs_font_style_bold,
	uvs_font_style_italic,
	uvs_font_style_bold_italic,
	uvs_font_style_underline = 4, /* composite attribute */
	uvs_font_style_strikeout = 8, /* composite attribute */
	uvs_font_style_cleartype = 16 /* composite attribute, improves the readability of text on LCDs */
} uvs_font_style_e;

typedef enum {
	uvs_string_format_regular,
	uvs_string_rect_multiple_lines = 1, /* composite attribute */
	uvs_string_direction_vertical = 2, /* composite attribute */
	uvs_string_direction_right_to_left = 4, /* composite attribute */
	uvs_string_align_style_near = 8,
	uvs_string_align_style_center = 16,
	uvs_string_align_style_far = 32,
	uvs_string_line_align_style_near = 64,
	uvs_string_line_align_style_center = 128,
	uvs_string_line_align_style_far = 256,
	uvs_string_trmming_character = 512,
	uvs_string_trmming_word = 1024,
	uvs_string_trmming_ellipsis_character = 2048,
	uvs_string_trmming_ellipsis_word = 4096,
	uvs_string_trmming_ellipsis_path = 8192
} uvs_string_format_e;

typedef struct {
	char szFontName[UVS_NAME_LEN];
	int fontPointSize;
	uvs_font_style_e fontStyle;
	uvs_string_format_e stringFormat;
	COLORREF textColor;
	COLORREF textBkColor;
	int textOpacity;
	int textBkOpacity;
} uvs_font_info_t;

typedef struct {
	WCHAR szFontName[UVS_NAME_LEN];
	int fontPointSize;
	uvs_font_style_e fontStyle;
	uvs_string_format_e stringFormat;
	COLORREF textColor;
	COLORREF textBkColor;
	int textOpacity;
	int textBkOpacity;
} uvs_font_info_tW;

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

typedef enum {
	uvs_dash_style_solid,
	uvs_dash_style_dash,
	uvs_dash_style_dot,
	uvs_dash_style_dash_dot
} uvs_dash_style_e;

typedef struct {
	int lineSize;
	uvs_dash_style_e dashStyle;
	COLORREF edgeColor;
	COLORREF fillColor;
	int edgeOpacity;
	int fillOpacity;
} uvs_style_info_t;

typedef struct {
	int lineSize;
	uvs_dash_style_e dashStyle;
	COLORREF lineColor;
	int lineOpacity;
} uvs_line_info_t;

typedef struct {
	const char *ipAddress;
	USHORT ipPort;
} uvs_rtp_multicast_t;

typedef struct {
	const WCHAR *ipAddress;
	USHORT ipPort;
} uvs_rtp_multicast_tW;

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
} uvs_mp4_file_positon_e;

typedef struct {
	uvs_font_info_t textFont;
	int x, y;
	int width, height;
	int imageOpacity;
	const char *szTitleImageFile;
	const char *szTitleText;
} uvs_mp4_file_title_t;

typedef struct {
	uvs_font_info_tW textFont;
	int x, y;
	int width, height;
	int imageOpacity;
	const WCHAR *szTitleImageFile;
	const WCHAR *szTitleText;
} uvs_mp4_file_title_tW;

int UVSAPI uvs_media_init(int flags);
void UVSAPI uvs_media_exit(void);
int UVSAPI uvs_get_version(void);

int UVSAPI uvs_enum_device(uvs_dev_type_e devType, uvs_dev_info_t devInfo[], int *devNum);
int UVSAPI uvs_enum_deviceW(uvs_dev_type_e devType, uvs_dev_info_tW devInfo[], int *devNum);
int UVSAPI uvs_set_device_callback(pUVSDeviceCallback pCB, void *pUserData);
int UVSAPI uvs_set_device_callbackW(pUVSDeviceCallbackW pCB, void *pUserData);
int UVSAPI uvs_get_device_count(void);

int UVSAPI uvs_query_video_encoder(uvsobj_handle obj, uvs_video_codec_e videoCodec);
int UVSAPI uvs_calc_buffer_size(uvs_frame_type_e frameType, int videoWidth, int videoHeight, int nStride);

int UVSAPI uvs_set_nosignal_image(const char *szFileName, uvs_draw_mode_e drawMode, COLORREF bkColor);
int UVSAPI uvs_set_nosignal_imageW(const WCHAR *szFileName, uvs_draw_mode_e drawMode, COLORREF bkColor);

uvsobj_handle UVSAPI uvs_dev_open(const uvs_dev_info_t *devInfo, int *result);
uvsobj_handle UVSAPI uvs_dev_openW(const uvs_dev_info_tW *devInfo, int *result);
int UVSAPI uvs_dev_close(uvsobj_handle obj);

int UVSAPI uvs_get_dev_info(uvsobj_handle obj, uvs_dev_info_t *devInfo);
int UVSAPI uvs_get_dev_infoW(uvsobj_handle obj, uvs_dev_info_tW *devInfo);

int UVSAPI uvs_query_hardware_info(uvsobj_handle obj, uvs_hardware_info_t *hwInfo);

int UVSAPI uvs_enum_audio_format(uvsobj_handle obj, uvs_audio_format_t formats[], int *formatNum);
int UVSAPI uvs_enum_video_format(uvsobj_handle obj, uvs_source_type_e sourceType, uvs_video_format_t formats[], int *formatNum);

int UVSAPI uvs_set_audio_device(uvsobj_handle obj, uvs_dev_type_e devType, const uvs_dev_info_t *devInfo);
int UVSAPI uvs_set_audio_deviceW(uvsobj_handle obj, uvs_dev_type_e devType, const uvs_dev_info_tW *devInfo);
int UVSAPI uvs_create_property_page(uvsobj_handle obj, uvs_property_page_e propertyPage, HWND hOwner, int x, int y, const char *szCaption);
int UVSAPI uvs_create_property_pageW(uvsobj_handle obj, uvs_property_page_e propertyPage, HWND hOwner, int x, int y, const WCHAR *szCaption);

int UVSAPI uvs_dev_control(uvsobj_handle obj, uvs_dev_state_e state);

int UVSAPI uvs_get_audio_property(uvsobj_handle obj, uvs_audio_format_t *format, uvs_audio_codec_e *audioCodec);
int UVSAPI uvs_set_audio_property(uvsobj_handle obj, const uvs_audio_format_t *format, uvs_audio_codec_e audioCodec);

int UVSAPI uvs_set_audio_mute(uvsobj_handle obj, BOOL bMute);
int UVSAPI uvs_get_audio_volume(uvsobj_handle obj, int *volume);
int UVSAPI uvs_set_audio_volume(uvsobj_handle obj, int volume);
int UVSAPI uvs_get_audio_balance(uvsobj_handle obj, int *balance);
int UVSAPI uvs_set_audio_balance(uvsobj_handle obj, int balance);

int UVSAPI uvs_get_video_input(uvsobj_handle obj, int *currentIndex, int inputTypes[], int *inputNum);
int UVSAPI uvs_set_video_input(uvsobj_handle obj, int inputIndex);

int UVSAPI uvs_get_video_property(uvsobj_handle obj, uvs_source_type_e sourceType, uvs_video_format_t *format);
int UVSAPI uvs_set_video_property(uvsobj_handle obj, uvs_source_type_e sourceType, const uvs_video_format_t *format);

int UVSAPI uvs_get_video_mirror(uvsobj_handle obj, BOOL *bHorizMirror, BOOL *bVertMirror);
int UVSAPI uvs_set_video_mirror(uvsobj_handle obj, BOOL bHorizMirror, BOOL bVertMirror);
int UVSAPI uvs_get_video_status(uvsobj_handle obj, BOOL *bSignal, BOOL *bMode);

int UVSAPI uvs_get_video_effect_range(uvsobj_handle obj, uvs_video_effect_e effect, int *minVal, int *maxVal, int *stepDelta, int *defaultVal);
int UVSAPI uvs_get_video_effect(uvsobj_handle obj, uvs_video_effect_e effect, int *param);
int UVSAPI uvs_set_video_effect(uvsobj_handle obj, uvs_video_effect_e effect, int param);

int UVSAPI uvs_set_video_encode_config(uvsobj_handle obj, int streamIndex, uvs_video_codec_e videoCodec, const uvs_encode_config_t *config);
int UVSAPI uvs_get_video_encode_config(uvsobj_handle obj, int streamIndex, uvs_video_codec_e *videoCodec, uvs_encode_config_t *config);

int UVSAPI uvs_request_video_key_frame(uvsobj_handle obj, int streamIndex);
int UVSAPI uvs_get_video_encode_status(uvsobj_handle obj, int streamIndex, uvs_encode_status_t *info);

int UVSAPI uvs_start_encode(uvsobj_handle obj, int streamIndex);
int UVSAPI uvs_stop_encode(uvsobj_handle obj, int streamIndex);

int UVSAPI uvs_set_record_metadata(uvsobj_handle obj, int streamIndex, const char *szTitle, const char *szComment, const char *szArtist, const char *szGenre, const char *szComposer);
int UVSAPI uvs_set_record_metadataW(uvsobj_handle obj, int streamIndex, const WCHAR *szTitle, const WCHAR *szComment, const WCHAR *szArtist, const WCHAR *szGenre, const WCHAR *szComposer);
int UVSAPI uvs_start_record(uvsobj_handle obj, int streamIndex, const char *szSaveFile1, const char *szSaveFile2, BOOL bRecAudio, BOOL bRepairSupport, UINT uKBData, UINT uMilliSec);
int UVSAPI uvs_start_recordW(uvsobj_handle obj, int streamIndex, const WCHAR *szSaveFile1, const WCHAR *szSaveFile2, BOOL bRecAudio, BOOL bRepairSupport, UINT uKBData, UINT uMilliSec);
int UVSAPI uvs_get_record_filename(uvsobj_handle obj, int streamIndex, uvs_filename_t fileName[], int *fileNum);
int UVSAPI uvs_get_record_filenameW(uvsobj_handle obj, int streamIndex, uvs_filename_tW fileName[], int *fileNum);
int UVSAPI uvs_pause_record(uvsobj_handle obj, int streamIndex, BOOL bRecResume, BOOL bRequestKeyFrame);
int UVSAPI uvs_stop_record(uvsobj_handle obj, int streamIndex);

int UVSAPI uvs_start_preview(uvsobj_handle obj, HWND hwnd, uvs_disp_type_e dispType);
int UVSAPI uvs_get_preview_freeze(uvsobj_handle obj, BOOL *bFreeze);
int UVSAPI uvs_set_preview_freeze(uvsobj_handle obj, BOOL bFreeze);
int UVSAPI uvs_set_preview_rect(uvsobj_handle obj, LPCRECT wndRect, LPCRECT cropRect, COLORREF bkColor);
int UVSAPI uvs_stop_preview(uvsobj_handle obj);

int UVSAPI uvs_set_time_osd(uvsobj_handle obj, int osdIndex, int x, int y, const char *szTimeFormat, const uvs_font_info_t *info);
int UVSAPI uvs_set_time_osdW(uvsobj_handle obj, int osdIndex, int x, int y, const WCHAR *szTimeFormat, const uvs_font_info_tW *info);
int UVSAPI uvs_set_text_osd(uvsobj_handle obj, int osdIndex, int x, int y, int width, int height, const char *szText, const uvs_font_info_t *info);
int UVSAPI uvs_set_text_osdW(uvsobj_handle obj, int osdIndex, int x, int y, int width, int height, const WCHAR *szText, const uvs_font_info_tW *info);
int UVSAPI uvs_set_image_osd(uvsobj_handle obj, int osdIndex, int x, int y, int width, int height, int imgOpacity, const char *szFileName);
int UVSAPI uvs_set_image_osdW(uvsobj_handle obj, int osdIndex, int x, int y, int width, int height, int imgOpacity, const WCHAR *szFileName);
int UVSAPI uvs_set_rect_osd(uvsobj_handle obj, int osdIndex, int x, int y, int width, int height, const uvs_style_info_t *info);
int UVSAPI uvs_set_ellipse_osd(uvsobj_handle obj, int osdIndex, int x, int y, int width, int height, const uvs_style_info_t *info);
int UVSAPI uvs_set_line_osd(uvsobj_handle obj, int osdIndex, int x0, int y0, int x1, int y1, const uvs_line_info_t *info);
int UVSAPI uvs_osd_control(uvsobj_handle obj, int osdIndex, uvs_osd_cmd_e cmd, int *param0, int *param1);

uvsobj_handle UVSAPI uvs_create_frame_preview(HWND hwnd, uvs_disp_type_e dispType);
int UVSAPI uvs_frame_preview(uvsobj_handle handle, const uvs_frame_info_t *info);
int UVSAPI uvs_set_frame_preview_rect(uvsobj_handle handle, LPCRECT wndRect, LPCRECT cropRect, COLORREF bkColor);
int UVSAPI uvs_destroy_frame_preview(uvsobj_handle handle);

int UVSAPI uvs_set_video_raw_frame_callback(uvsobj_handle obj, pUVSFrameCallback pCB, void *pUserData);
int UVSAPI uvs_set_video_enc_frame_callback(uvsobj_handle obj, int streamIndex, pUVSFrameCallback pCB, void *pUserData);
int UVSAPI uvs_set_video_draw_callback(uvsobj_handle obj, pUVSDrawCallback pCB, void *pUserData);

int UVSAPI uvs_convert_video_frame(const uvs_frame_convert_t *frameConvert, const uvs_frame_info_t *src, uvs_frame_info_t *dst);
int UVSAPI uvs_save_video_frame(const char *szFileName, const uvs_frame_convert_t *frameConvert, const uvs_frame_info_t *info, UINT jpgQuality);
int UVSAPI uvs_save_video_frameW(const WCHAR *szFileName, const uvs_frame_convert_t *frameConvert, const uvs_frame_info_t *info, UINT jpgQuality);
int UVSAPI uvs_save_video_snapshot(uvsobj_handle obj, const char *szFileName, const uvs_frame_convert_t *frameConvert, UINT jpgQuality);
int UVSAPI uvs_save_video_snapshotW(uvsobj_handle obj, const WCHAR *szFileName, const uvs_frame_convert_t *frameConvert, UINT jpgQuality);

int UVSAPI uvs_lock_video_raw_frame(uvsobj_handle obj, uvs_frame_info_t *info, UINT waitMilliSec);
int UVSAPI uvs_unlock_video_raw_frame(uvsobj_handle obj);
int UVSAPI uvs_copy_video_frame(uvsobj_handle obj, const uvs_frame_convert_t *frameConvert, uvs_frame_info_t *info, UINT waitMilliSec);

int UVSAPI uvs_set_audio_raw_frame_callback(uvsobj_handle obj, pUVSFrameCallback pCB, void *pUserData);
int UVSAPI uvs_set_audio_enc_frame_callback(uvsobj_handle obj, pUVSFrameCallback pCB, void *pUserData);

int UVSAPI uvs_lock_audio_raw_frame(uvsobj_handle obj, uvs_frame_info_t *info, UINT waitMilliSec);
int UVSAPI uvs_unlock_audio_raw_frame(uvsobj_handle obj);
int UVSAPI uvs_copy_audio_raw_frame(uvsobj_handle obj, uvs_frame_info_t *info, UINT waitMilliSec);

int UVSAPI uvs_media_server_rtsp_create(USHORT rtspPort, USHORT httpTunnerPort, const char *szUserName, const char *szPassword);
int UVSAPI uvs_media_server_rtsp_createW(USHORT rtspPort, USHORT httpTunnerPort, const WCHAR *szUserName, const WCHAR *szPassword);
int UVSAPI uvs_media_server_rtsp_destroy(USHORT rtspPort);

int UVSAPI uvs_media_stream_rtsp_start(uvsobj_handle obj, int streamIndex, USHORT rtspPort, BOOL bHasAudio, const char *szSessionName, const uvs_rtp_multicast_t *rtpMulticast);
int UVSAPI uvs_media_stream_rtsp_startW(uvsobj_handle obj, int streamIndex, USHORT rtspPort, BOOL bHasAudio, const WCHAR *szSessionName, const uvs_rtp_multicast_tW *rtpMulticast);
int UVSAPI uvs_media_stream_rtsp_stop(uvsobj_handle obj, int streamIndex);
int UVSAPI uvs_media_stream_rtsp_get_url(uvsobj_handle obj, int streamIndex, uvs_url_t *urlInfo);
int UVSAPI uvs_media_stream_rtsp_get_urlW(uvsobj_handle obj, int streamIndex, uvs_url_tW *urlInfo);

int UVSAPI uvs_media_file_rtsp_start(const char *szFileName, USHORT rtspPort, BOOL bHasAudio, const char *szSessionName);
int UVSAPI uvs_media_file_rtsp_startW(const WCHAR *szFileName, USHORT rtspPort, BOOL bHasAudio, const WCHAR *szSessionName);
int UVSAPI uvs_media_file_rtsp_stop(const char *szFileName);
int UVSAPI uvs_media_file_rtsp_stopW(const WCHAR *szFileName);
int UVSAPI uvs_media_file_rtsp_get_url(const char *szFileName, uvs_url_t *urlInfo);
int UVSAPI uvs_media_file_rtsp_get_urlW(const WCHAR *szFileName, uvs_url_tW *urlInfo);

int UVSAPI uvs_media_stream_rtmp_send(uvsobj_handle obj, int streamIndex, const char *rtmpUrl, BOOL bHasAudio);
int UVSAPI uvs_media_stream_rtmp_sendW(uvsobj_handle obj, int streamIndex, const WCHAR *rtmpUrl, BOOL bHasAudio);
int UVSAPI uvs_media_stream_rtmp_stop(uvsobj_handle obj, int streamIndex);
int UVSAPI uvs_media_stream_rtmp_get_send_url(uvsobj_handle obj, int streamIndex, uvs_url_t *urlInfo);
int UVSAPI uvs_media_stream_rtmp_get_send_urlW(uvsobj_handle obj, int streamIndex, uvs_url_tW *urlInfo);

int UVSAPI uvs_media_file_rtmp_send(const char *szFileName, const char *rtmpUrl, BOOL bHasAudio);
int UVSAPI uvs_media_file_rtmp_sendW(const WCHAR *szFileName, const WCHAR *rtmpUrl, BOOL bHasAudio);
int UVSAPI uvs_media_file_rtmp_get_progress(const char *szFileName, int *progress);
int UVSAPI uvs_media_file_rtmp_get_progressW(const WCHAR *szFileName, int *progress);
int UVSAPI uvs_media_file_rtmp_stop(const char *szFileName);
int UVSAPI uvs_media_file_rtmp_stopW(const WCHAR *szFileName);
int UVSAPI uvs_media_file_rtmp_get_send_url(const char *szFileName, uvs_url_t *urlInfo);
int UVSAPI uvs_media_file_rtmp_get_send_urlW(const WCHAR *szFileName, uvs_url_tW *urlInfo);

int UVSAPI uvs_media_stream_ndi_create(uvsobj_handle obj, const char *szSourceName, const char *szGroupName, const char *szXMLMetadata, BOOL bAsync);
int UVSAPI uvs_media_stream_ndi_createW(uvsobj_handle obj, const WCHAR *szSourceName, const WCHAR *szGroupName, const WCHAR *szXMLMetadata, BOOL bAsync);
int UVSAPI uvs_media_stream_ndi_config(uvsobj_handle obj, const uvs_frame_convert_t *frameConvert, int skipFrameRate);
int UVSAPI uvs_media_stream_ndi_start(uvsobj_handle obj, BOOL bHasAudio);
int UVSAPI uvs_media_stream_ndi_stop(uvsobj_handle obj);
int UVSAPI uvs_media_stream_ndi_destroy(uvsobj_handle obj);

int UVSAPI uvs_mp4_file_get_status(const char *szFileName, uvs_mp4_file_status_t *status);
int UVSAPI uvs_mp4_file_get_statusW(const WCHAR *szFileName, uvs_mp4_file_status_t *status);
int UVSAPI uvs_mp4_file_repair(const char *szFileName, const char *szOutputFile);
int UVSAPI uvs_mp4_file_repairW(const WCHAR *szFileName, const WCHAR *szOutputFile);
int UVSAPI uvs_mp4_file_repair_cancel(void);
int UVSAPI uvs_mp4_file_get_repair_progress(int *progress);
int UVSAPI uvs_mp4_file_cut(const char *szFileName, int beginMilliSec, int endMilliSec, const char *szOutputFile);
int UVSAPI uvs_mp4_file_cutW(const WCHAR *szFileName, int beginMilliSec, int endMilliSec, const WCHAR *szOutputFile);
int UVSAPI uvs_mp4_file_get_cut_progress(int *progress);
int UVSAPI uvs_mp4_file_add_title(const char *szFileName, int beginMilliSec, const uvs_mp4_file_title_t title[], int titleNum, int titleMilliSec, const char *szOutputFile);
int UVSAPI uvs_mp4_file_add_titleW(const WCHAR *szFileName, int beginMilliSec, const uvs_mp4_file_title_tW title[], int titleNum, int titleMilliSec, const WCHAR *szOutputFile);
int UVSAPI uvs_mp4_file_get_title_progress(int *progress);
int UVSAPI uvs_mp4_file_merge(const char *szFileName[], int fileNum, const char *szOutputFile);
int UVSAPI uvs_mp4_file_mergeW(const WCHAR *szFileName[], int fileNum, const WCHAR *szOutputFile);
int UVSAPI uvs_mp4_file_get_merge_progress(int *progress);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef __UVS_MEDIA_H__6E72C738_BF82_4CCB_A785_F454D593FFF2__INCLUDED_ */
