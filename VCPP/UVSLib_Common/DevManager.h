#pragma once

#include "../../WindowsSDK/inc/UVSMedia.h"

#ifdef UNICODE
typedef uvs_dev_info_tW uvs_dev_info_tX;
typedef pUVSDeviceCallbackW pUVSDeviceCallbackX;
typedef uvs_filename_tW uvs_filename_tX;
typedef uvs_url_tW uvs_url_tX;
typedef uvs_font_info_tW uvs_font_info_tX;
typedef uvs_rtp_multicast_tW uvs_rtp_multicast_tX;
typedef uvs_mp4_file_title_tW uvs_mp4_file_title_tX;
#else
typedef uvs_dev_info_t uvs_dev_info_tX;
typedef pUVSDeviceCallback pUVSDeviceCallbackX;
typedef uvs_filename_t uvs_filename_tX;
typedef uvs_url_t uvs_url_tX;
typedef uvs_font_info_t uvs_font_info_tX;
typedef uvs_rtp_multicast_t uvs_rtp_multicast_tX;
typedef uvs_mp4_file_title_t uvs_mp4_file_title_tX;
#endif

class CDevSDKInit {
public:
	CDevSDKInit(void);
	~CDevSDKInit();
};

class CDevSDK {
public:
	CDevSDK(void);
	CDevSDK(int videoIndex, int audioIndex=-1, int *result=NULL);
	CDevSDK(const uvs_dev_info_tX &videoDevInfo, const uvs_dev_info_tX *audioDevInfo=NULL, int *result=NULL);
	virtual ~CDevSDK();

	static CDevSDK* CreateInstance(int videoIndex, int audioIndex=-1);
	static CDevSDK* CreateInstance(const uvs_dev_info_tX &videoDevInfo, const uvs_dev_info_tX *audioDevInfo=NULL);

	static int GetDeviceCount(void);
	static int SetDeviceCallback(pUVSDeviceCallbackX pCB, void *pUserData=NULL);
	static int QueryVideoEncoder(uvs_video_codec_e videoCodec);
	static int CalcBufferSize(uvs_frame_type_e frameType, int nWidth, int nHeight, int nStride=0/* 4bytes aligned */);
	static int CreateFrame(uvs_frame_type_e frameType, int nWidth, int nHeight, uvs_frame_info_t &frame, int nStride=0/* 4bytes aligned */);
	static int DestroyFrame(uvs_frame_info_t &frame);
	static int SetNosignalImage(LPCTSTR szFileName, uvs_draw_mode_e drawMode=uvs_draw_stretch, COLORREF bkColor=RGB(0, 0, 0));
	static int EnumDevice(uvs_dev_type_e devType, uvs_dev_info_tX devInfo[], int &devInfoNum/* [IN][OUT] */);

	static int ConvertVideoFrame(const uvs_frame_convert_t &frameConvert, const uvs_frame_info_t &src, uvs_frame_info_t &dst);
	static int VideoFrameSaveFile(LPCTSTR szFileName, const uvs_frame_info_t &info, UINT jpgQuality=100, const uvs_frame_convert_t *frameConvert=NULL);

	static int RTSPServerCreate(USHORT rtspPort, LPCTSTR szUserName=NULL, LPCTSTR szPassword=NULL, USHORT httpTunnerPort=0);
	static int RTSPServerDestroy(USHORT rtspPort);

	static int MP4FileRTSPStart(LPCTSTR szFileName, USHORT rtspPort, BOOL bHasAudio, LPCTSTR szSessionName=NULL);
	static int MP4FileRTSPGetURL(LPCTSTR szFileName, uvs_url_tX &urlInfo);
	static int MP4FileRTSPStop(LPCTSTR szFileName);

	static int MP4FileRTMPSend(LPCTSTR szFileName, LPCTSTR rtmpUrl, BOOL bHasAudio);
	static int MP4FileRTMPGetProgress(LPCTSTR szFileName, int &progress);
	static int MP4FileRTMPGetSendURL(LPCTSTR szFileName, uvs_url_tX &urlInfo);
	static int MP4FileRTMPStop(LPCTSTR szFileName);

	static int MP4FileGetStatus(LPCTSTR szFileName, uvs_mp4_file_status_t &status);
	static int MP4FileRepair(LPCTSTR szFileName, LPCTSTR szOutputFileName);
	static int MP4FileRepairCancel(void);
	static int MP4FileGetRepairProgress(int &progress);
	static int MP4FileCut(LPCTSTR szFileName, int beginMilliSec, int endMilliSec, LPCTSTR szOutputFileName);
	static int MP4FileGetCutProgress(int &progress);
	static int MP4FileAddTitle(LPCTSTR szFileName, int beginMilliSec, const uvs_mp4_file_title_tX title[], int titleNum, int titleMilliSec, LPCTSTR szOutputFileName);
	static int MP4FileGetTitleProgress(int &progress);
	static int MP4FileMerge(LPCTSTR szFileName[], int fileNum, LPCTSTR szOutputFileName);
	static int MP4FileGetMergeProgress(int &progress);

	bool IsValid(void) const { return m_DevObj ? true : false; }
	operator bool() const { return IsValid(); }

	int DeviceOpen(int videoIndex);
	int DeviceOpen(const uvs_dev_info_tX &videoDevInfo);
	void DeviceClose(void);
	int GetDeviceInfo(uvs_dev_info_tX &videoDevInfo);

	int EnumAudioFormat(uvs_audio_format_t formats[], int &formatNum);
	int EnumVideoFormat(uvs_source_type_e sourceType, uvs_video_format_t formats[], int &formatNum);

	int SetAudioDevice(uvs_dev_type_e devType, int devIndex);
	int SetAudioDevice(uvs_dev_type_e devType, const uvs_dev_info_tX &devInfo);

	int GetAudioProperty(uvs_audio_format_t &audioFormat, uvs_audio_codec_e &audioCodec);
	int SetAudioProperty(uvs_audio_codec_e audioCodec);

	int SetAudioMute(BOOL bAudioMute);
	int GetAudioVolume(int &audioVolume);
	int SetAudioVolume(int audioVolume);
	int GetAudioBalance(int &audioBalance);
	int SetAudioBalance(int audioBalance);

	int GetVideoProperty(uvs_video_format_t &videoFormat, uvs_source_type_e sourceType=uvs_source_any);
	int SetVideoProperty(const uvs_video_format_t &videoFormat, uvs_source_type_e sourceType=uvs_source_any);

	int GetVideoMirror(BOOL &bHorizMirror, BOOL &bVertMirror);
	int SetVideoMirror(BOOL bHorizMirror, BOOL bVertMirror);
	int GetVideoStatus(BOOL &bSignal, BOOL &bMode);

	int GetVideoEffectRange(uvs_video_effect_e effect, int &minVal, int &maxVal, int &stepDelta, int &defaultVal);
	int GetVideoEffect(uvs_video_effect_e effect, int &val);
	int SetVideoEffect(uvs_video_effect_e effect, int val);

	int DeviceStart(void);
	int DevicePause(void);
	int DeviceStop(void);

	int SetTimeOSD(int osdIndex, int x, int y, LPCTSTR szTimeMode, const uvs_font_info_tX &info);
	int SetTextOSD(int osdIndex, int x, int y, int width, int height, LPCTSTR szText, const uvs_font_info_tX &info);
	int SetImageOSD(int osdIndex, int x, int y, int width, int height, int imgOpacity, LPCTSTR szFileName);
	int SetRectOSD(int osdIndex, int x, int y, int width, int height, const uvs_style_info_t &info);
	int SetEllipseOSD(int osdIndex, int x, int y, int width, int height, const uvs_style_info_t &info);
	int SetLineOSD(int osdIndex, int x0, int y0, int x1, int y1, const uvs_line_info_t &info);
	int VideoOSDControl(int osdIndex, uvs_osd_cmd_e cmd, int *param0=NULL, int *param1=NULL);

	int PreviewStart(HWND hwnd, uvs_disp_type_e disp=uvs_disp_type_d3d);
	int PreviewSetRect(LPRECT wndDispRect, LPRECT videoCropRect, COLORREF bkColor=RGB(0, 0, 0));
	int PreviewFreeze(BOOL bFreeze);
	int PreviewIsFreeze(BOOL &isFreeze);
	int PreviewStop(void);

	int SetVideoDrawCallback(pUVSDrawCallback pCB, void *pUserData=NULL);

	int SetVideoEncodeParam(int streamIndex, uvs_video_codec_e videoCodec, const uvs_encode_config_t &config);
	int GetVideoEncodeParam(int streamIndex, uvs_video_codec_e &videoCodec, uvs_encode_config_t &config);
	int EncodeStart(int streamIndex);
	int RequestVideoKeyFrame(int streamIndex);
	int GetVideoEncodeStatus(int streamIndex, uvs_encode_status_t &info);
	int EncodeStop(int streamIndex);

	int SetVideoRawFrameCallback(pUVSFrameCallback pCB, void *pUserData=NULL);
	int SetVideoEncodeFrameCallback(int streamIndex, pUVSFrameCallback pCB, void *pUserData=NULL);

	int LockVideoRawFrame(uvs_frame_info_t &info, UINT waitMilliSec=1000);
	int UnlockVideoRawFrame(void);
	int CopyVideoFrame(uvs_frame_info_t &info, UINT waitMilliSec=1000, const uvs_frame_convert_t *frameConvert=NULL);

	int SetAudioRawFrameCallback(pUVSFrameCallback pCB, void *pUserData=NULL);
	int SetAudioEncodeFrameCallback(pUVSFrameCallback pCB, void *pUserData=NULL);

	int LockAudioRawFrame(uvs_frame_info_t &info, UINT waitMilliSec=1000);
	int UnlockAudioRawFrame(void);
	int CopyAudioRawFrame(uvs_frame_info_t &info, UINT waitMilliSec=1000);

	int SetRecordMetadata(int streamIndex, LPCTSTR szTitle, LPCTSTR szComment=NULL, LPCTSTR szArtist=NULL, LPCTSTR szGenre=NULL, LPCTSTR szComposer=NULL);
	int RecordStart(int streamIndex, LPCTSTR szFile1, LPCTSTR szFile2=NULL, BOOL bRecAudio=TRUE, BOOL bRepairSupport=TRUE, UINT maxKBytes=0, UINT maxMilliSec=0);
	int GetRecordFilename(int streamIndex, uvs_filename_tX fileName[], int &fileNum);
	int RecordPause(int streamIndex, BOOL bResume, BOOL bRequestKeyFrame=TRUE);
	int RecordStop(int streamIndex);

	int RTSPStart(int streamIndex, USHORT rtspPort, BOOL bHasAudio, LPCTSTR szSessionName=NULL, const uvs_rtp_multicast_tX *rtpMulticast=NULL);
	int RTSPGetURL(int streamIndex, uvs_url_tX &urlInfo);
	int RTSPStop(int streamIndex);

	int RTMPSend(int streamIndex, LPCTSTR rtmpUrl, BOOL bHasAudio);
	int RTMPGetSendURL(int streamIndex, uvs_url_tX &urlInfo);
	int RTMPStop(int streamIndex);

	int NDICreate(LPCTSTR szSourceName, LPCTSTR szGroupName, LPCTSTR szXMLMetadata=NULL, BOOL bAsync=TRUE);
	int NDIConfig(const uvs_frame_convert_t *frameConvert, int skipFrameRate=0);
	int NDIStart(BOOL bHasAudio);
	int NDIStop(void);
	int NDIDestroy(void);

	int CaptureSnapshot(LPCTSTR szFileName, UINT jpgQuality=100, const uvs_frame_convert_t *frameConvert=NULL);
	int CreatePropertyPage(uvs_property_page_e propertyPage, HWND hOwner, int x, int y, LPCTSTR szCaption=NULL);

	uvsobj_handle m_DevObj;

private:

	static CDevSDKInit DevSDKInit;
};

class CFramePreview
{
public:
	CFramePreview(HWND hwnd, uvs_disp_type_e dispType=uvs_disp_type_d3d);
	virtual ~CFramePreview();

	int Preview(const uvs_frame_info_t *info);
	int PreviewRect(LPRECT wndRect, LPRECT cropRect, COLORREF bkColor);

private:
	uvsobj_handle m_Handle;
};

class CFileRTSP
{
public:
	CFileRTSP(LPCTSTR szFileName, USHORT rtspPort, BOOL bHasAudio, LPCTSTR szSessionName=NULL, int *result=NULL);
	virtual ~CFileRTSP();

	static CFileRTSP* CreateInstance(LPCTSTR szFileName, USHORT rtspPort, BOOL bHasAudio, LPCTSTR szSessionName=NULL);

	int GetURL(uvs_url_tX &urlInfo);

private:
	LPTSTR m_FileName;
};

class CFileRTMP
{
public:
	CFileRTMP(LPCTSTR szFileName, LPCTSTR rtmpUrl, BOOL bHasAudio, int *result=NULL);
	virtual ~CFileRTMP();

	static CFileRTMP* CreateInstance(LPCTSTR szFileName, LPCTSTR rtmpUrl, BOOL bHasAudio);

	int GetProgress(int &progress);
	int GetURL(uvs_url_tX &urlInfo);

private:
	LPTSTR m_FileName;
};
