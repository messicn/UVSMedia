#include "StdAfx.h"
#include "DevManager.h"

#ifndef _WIN64
#pragma comment(lib, "../../../WindowsSDK/lib/win32/UVSMedia.lib")
#else
#pragma comment(lib, "../../../WindowsSDK/lib/x64/UVSMedia.lib")
#endif

CDevSDKInit::CDevSDKInit(void)
{
	uvs_media_init(0);
}

CDevSDKInit::~CDevSDKInit(void)
{
	uvs_media_exit();
}

CDevSDKInit CDevSDK::DevSDKInit;

CDevSDK::CDevSDK(void) : m_DevObj(NULL) {}

CDevSDK::CDevSDK(int videoIndex, int audioIndex, int *result)
	: m_DevObj(NULL)
{
	int r = DeviceOpen(videoIndex);
	if (IsValid())
	{
		if (audioIndex >= 0) r = SetAudioDevice(uvs_dev_audio_capture, audioIndex);
	}

	if (result) *result = r;
}

CDevSDK::CDevSDK(const uvs_dev_info_tX &videoDevInfo, const uvs_dev_info_tX *audioDevInfo, int *result)
	: m_DevObj(NULL)
{
	int r = DeviceOpen(videoDevInfo);
	if (IsValid())
	{
		if (audioDevInfo) r = SetAudioDevice(uvs_dev_audio_capture, *audioDevInfo);
	}

	if (result) *result = r;
}

CDevSDK::~CDevSDK()
{
	DeviceClose();
}

CDevSDK* CDevSDK::CreateInstance(int videoIndex, int audioIndex)
{
	int r;
	CDevSDK *pDev = new (std::nothrow) CDevSDK(videoIndex, audioIndex, &r);
	if (r == UVS_OK)
	{
		return pDev;
	}
	
	delete pDev;
	return NULL;
}

CDevSDK* CDevSDK::CreateInstance(const uvs_dev_info_tX &videoDevInfo, const uvs_dev_info_tX *audioDevInfo)
{
	int r;
	CDevSDK *pDev = new (std::nothrow) CDevSDK(videoDevInfo, audioDevInfo, &r);
	if (r == UVS_OK)
	{
		return pDev;
	}
	
	delete pDev;
	return NULL;
}

int CDevSDK::GetDeviceCount(void)
{
	return uvs_get_device_count();
}

int CDevSDK::SetDeviceCallback(pUVSDeviceCallbackX pCB, void *pUserData)
{
#ifdef UNICODE
	return uvs_set_device_callbackW(pCB, pUserData);
#else
	return uvs_set_device_callback(pCB, pUserData);
#endif
}

int CDevSDK::QueryVideoEncoder(uvs_video_codec_e videoCodec)
{
	return uvs_query_video_encoder(NULL, videoCodec);
}

int CDevSDK::CalcBufferSize(uvs_frame_type_e frameType, int nWidth, int nHeight, int nStride)
{
	return uvs_calc_buffer_size(frameType, nWidth, nHeight, nStride);
}

int CDevSDK::SetNosignalImage(LPCTSTR szFileName, uvs_draw_mode_e drawMode, COLORREF bkColor)
{
#ifdef UNICODE
	return uvs_set_nosignal_imageW(szFileName, drawMode, bkColor);
#else
	return uvs_set_nosignal_image(szFileName, drawMode, bkColor);
#endif
}

int CDevSDK::EnumDevice(uvs_dev_type_e devType, uvs_dev_info_tX devInfo[], int &devInfoNum)
{
#ifdef UNICODE
	return uvs_enum_deviceW(devType, devInfo, &devInfoNum);
#else
	return uvs_enum_device(devType, devInfo, &devInfoNum);
#endif
}

int CDevSDK::ConvertVideoFrame(const uvs_frame_convert_t &frameConvert, const uvs_frame_info_t &src, uvs_frame_info_t &dst)
{
	return uvs_convert_video_frame(&frameConvert, &src, &dst);
}

int CDevSDK::VideoFrameSaveFile(LPCTSTR szFileName, const uvs_frame_info_t &info, UINT jpgQuality, const uvs_frame_convert_t *frameConvert)
{
#ifdef UNICODE
	return uvs_save_video_frameW(szFileName, frameConvert, &info, jpgQuality);
#else
	return uvs_save_video_frame(szFileName, frameConvert, &info, jpgQuality);
#endif
}

int CDevSDK::RTSPServerCreate(USHORT rtspPort, LPCTSTR szUserName, LPCTSTR szPassword, USHORT httpTunnerPort)
{
#ifdef UNICODE
	return uvs_media_server_rtsp_createW(rtspPort, httpTunnerPort, szUserName, szPassword);
#else
	return uvs_media_server_rtsp_create(rtspPort, httpTunnerPort, szUserName, szPassword);
#endif
}

int CDevSDK::RTSPServerDestroy(USHORT rtspPort)
{
	return uvs_media_server_rtsp_destroy(rtspPort);
}

int CDevSDK::MP4FileRTSPStart(LPCTSTR szFileName, USHORT rtspPort, BOOL bHasAudio, LPCTSTR szSessionName)
{
#ifdef UNICODE
	return uvs_media_file_rtsp_startW(szFileName, rtspPort, bHasAudio, szSessionName);
#else
	return uvs_media_file_rtsp_start(szFileName, rtspPort, bHasAudio, szSessionName);
#endif
}

int CDevSDK::MP4FileRTSPGetURL(LPCTSTR szFileName, uvs_url_tX &urlInfo)
{
#ifdef UNICODE
	return uvs_media_file_rtsp_get_urlW(szFileName, &urlInfo);
#else
	return uvs_media_file_rtsp_get_url(szFileName, &urlInfo);
#endif
}

int CDevSDK::MP4FileRTSPStop(LPCTSTR szFileName)
{
#ifdef UNICODE
	return uvs_media_file_rtsp_stopW(szFileName);
#else
	return uvs_media_file_rtsp_stop(szFileName);
#endif
}

int CDevSDK::MP4FileRTMPSend(LPCTSTR szFileName, LPCTSTR rtmpUrl, BOOL bHasAudio)
{
#ifdef UNICODE
	return uvs_media_file_rtmp_sendW(szFileName, rtmpUrl, bHasAudio);
#else
	return uvs_media_file_rtmp_send(szFileName, rtmpUrl, bHasAudio);
#endif
}

int CDevSDK::MP4FileRTMPGetProgress(LPCTSTR szFileName, int &progress)
{
#ifdef UNICODE
	return uvs_media_file_rtmp_get_progressW(szFileName, &progress);
#else
	return uvs_media_file_rtmp_get_progress(szFileName, &progress);
#endif
}

int CDevSDK::MP4FileRTMPGetSendURL(LPCTSTR szFileName, uvs_url_tX &urlInfo)
{
#ifdef UNICODE
	return uvs_media_file_rtmp_get_send_urlW(szFileName, &urlInfo);
#else
	return uvs_media_file_rtmp_get_send_url(szFileName, &urlInfo);
#endif
}

int CDevSDK::MP4FileRTMPStop(LPCTSTR szFileName)
{
#ifdef UNICODE
	return uvs_media_file_rtmp_stopW(szFileName);
#else
	return uvs_media_file_rtmp_stop(szFileName);
#endif
}

int CDevSDK::MP4FileGetStatus(LPCTSTR szFileName, uvs_mp4_file_status_t &status)
{
#ifdef UNICODE
	return uvs_mp4_file_get_statusW(szFileName, &status);
#else
	return uvs_mp4_file_get_status(szFileName, &status);
#endif
}

int CDevSDK::MP4FileRepair(LPCTSTR szFileName, LPCTSTR szOutputFileName)
{
#ifdef UNICODE
	return uvs_mp4_file_repairW(szFileName, szOutputFileName);
#else
	return uvs_mp4_file_repair(szFileName, szOutputFileName);
#endif
}

int CDevSDK::MP4FileRepairCancel(void)
{
	return uvs_mp4_file_repair_cancel();
}

int CDevSDK::MP4FileGetRepairProgress(int &progress)
{
	return uvs_mp4_file_get_repair_progress(&progress);
}

int CDevSDK::MP4FileCut(LPCTSTR szFileName, int beginMilliSec, int endMilliSec, LPCTSTR szOutputFileName)
{
#ifdef UNICODE
	return uvs_mp4_file_cutW(szFileName, beginMilliSec, endMilliSec, szOutputFileName);
#else
	return uvs_mp4_file_cut(szFileName, beginMilliSec, endMilliSec, szOutputFileName);
#endif
}

int CDevSDK::MP4FileGetCutProgress(int &progress)
{
	return uvs_mp4_file_get_cut_progress(&progress);
}

int CDevSDK::MP4FileAddTitle(LPCTSTR szFileName, int beginMilliSec, const uvs_mp4_file_title_tX title[], int titleNum, int titleMilliSec, LPCTSTR szOutputFileName)
{
#ifdef UNICODE
	return uvs_mp4_file_add_titleW(szFileName, beginMilliSec, title, titleNum, titleMilliSec, szOutputFileName);
#else
	return uvs_mp4_file_add_title(szFileName, beginMilliSec, title, titleNum, titleMilliSec, szOutputFileName);
#endif
}

int CDevSDK::MP4FileGetTitleProgress(int &progress)
{
	return uvs_mp4_file_get_title_progress(&progress);
}

int CDevSDK::MP4FileMerge(LPCTSTR szFileName[], int fileNum, LPCTSTR szOutputFileName)
{
#ifdef UNICODE
	return uvs_mp4_file_mergeW(szFileName, fileNum, szOutputFileName);
#else
	return uvs_mp4_file_merge(szFileName, fileNum, szOutputFileName);
#endif
}

int CDevSDK::MP4FileGetMergeProgress(int &progress)
{
	return uvs_mp4_file_get_merge_progress(&progress);
}

int CDevSDK::DeviceOpen(int videoIndex)
{
	DeviceClose();

	// enum video capture device
	uvs_dev_info_tX dev[32];
	int num = _countof(dev);
	int r = EnumDevice(uvs_dev_video_capture, dev, num);
	if (r != UVS_OK) return r;

	if (videoIndex >= 0 && videoIndex < num)
	{
		// open device
		return DeviceOpen(dev[videoIndex]);
	}

	return UVS_ERR_INVALIDARG;
}

int CDevSDK::DeviceOpen(const uvs_dev_info_tX &videoDevInfo)
{
	DeviceClose();

	int r;
#ifdef UNICODE
	m_DevObj = uvs_dev_openW(&videoDevInfo, &r);
#else
	m_DevObj = uvs_dev_open(&videoDevInfo, &r);
#endif

	return r;
}

void CDevSDK::DeviceClose(void)
{
	if (IsValid())
	{
		uvs_dev_close(m_DevObj);
		m_DevObj = NULL;
	}
}

int CDevSDK::GetDeviceInfo(uvs_dev_info_tX &videoDevInfo)
{
#ifdef UNICODE
	return uvs_get_dev_infoW(m_DevObj, &videoDevInfo);
#else
	return uvs_get_dev_info(m_DevObj, &videoDevInfo);
#endif
}

int CDevSDK::EnumAudioFormat(uvs_audio_format_t formats[], int &formatNum)
{
	return uvs_enum_audio_format(m_DevObj, formats, &formatNum);
}

int CDevSDK::EnumVideoFormat(uvs_source_type_e sourceType, uvs_video_format_t formats[], int &formatNum)
{
	return uvs_enum_video_format(m_DevObj, sourceType, formats, &formatNum);
}

int CDevSDK::SetAudioDevice(uvs_dev_type_e devType, int devIndex)
{
	if (devIndex >= 0)
	{
		// enum audio device
		uvs_dev_info_tX dev[32];
		int num = _countof(dev);
		int r = EnumDevice(devType, dev, num);
		if (r != UVS_OK) return r;

		if (devIndex < num) return SetAudioDevice(devType, dev[devIndex]);
	}

	return UVS_ERR_INVALIDARG;
}

int CDevSDK::SetAudioDevice(uvs_dev_type_e devType, const uvs_dev_info_tX &devInfo)
{
#ifdef UNICODE
	return uvs_set_audio_deviceW(m_DevObj, devType, &devInfo);
#else
	return uvs_set_audio_device(m_DevObj, devType, &devInfo);
#endif
}

int CDevSDK::GetAudioProperty(uvs_audio_format_t &audioFormat, uvs_audio_codec_e &audioCodec)
{
	return uvs_get_audio_property(m_DevObj, &audioFormat, &audioCodec);
}

int CDevSDK::SetAudioProperty(uvs_audio_codec_e audioCodec)
{
	return uvs_set_audio_property(m_DevObj, NULL, audioCodec);
}

int CDevSDK::SetAudioMute(BOOL bAudioMute)
{
	return uvs_set_audio_mute(m_DevObj, bAudioMute);
}

int CDevSDK::GetAudioVolume(int &audioVolume)
{
	return uvs_get_audio_volume(m_DevObj, &audioVolume);
}

int CDevSDK::SetAudioVolume(int audioVolume)
{
	return uvs_set_audio_volume(m_DevObj, audioVolume);
}

int CDevSDK::GetAudioBalance(int &audioBalance)
{
	return uvs_get_audio_balance(m_DevObj, &audioBalance);
}

int CDevSDK::SetAudioBalance(int audioBalance)
{
	return uvs_set_audio_balance(m_DevObj, audioBalance);
}

int CDevSDK::GetVideoProperty(uvs_video_format_t &videoFormat, uvs_source_type_e sourceType)
{
	return uvs_get_video_property(m_DevObj, sourceType, &videoFormat);
}

int CDevSDK::SetVideoProperty(const uvs_video_format_t &videoFormat, uvs_source_type_e sourceType)
{
	return uvs_set_video_property(m_DevObj, sourceType, &videoFormat);
}

int CDevSDK::GetVideoMirror(BOOL &bHorizMirror, BOOL &bVertMirror)
{
	return uvs_get_video_mirror(m_DevObj, &bHorizMirror, &bVertMirror);
}

int CDevSDK::SetVideoMirror(BOOL bHorizMirror, BOOL bVertMirror)
{
	return uvs_set_video_mirror(m_DevObj, bHorizMirror, bVertMirror);
}

int CDevSDK::GetVideoStatus(BOOL &bSignal, BOOL &bMode)
{
	return uvs_get_video_status(m_DevObj, &bSignal, &bMode);
}

int CDevSDK::GetVideoEffectRange(uvs_video_effect_e effect, int &minVal, int &maxVal, int &stepDelta, int &defaultVal)
{
	return uvs_get_video_effect_range(m_DevObj, effect, &minVal, &maxVal, &stepDelta, &defaultVal);
}

int CDevSDK::GetVideoEffect(uvs_video_effect_e effect, int &val)
{
	return uvs_get_video_effect(m_DevObj, effect, &val);
}

int CDevSDK::SetVideoEffect(uvs_video_effect_e effect, int val)
{
	return uvs_set_video_effect(m_DevObj, effect, val);
}

int CDevSDK::DeviceStart(void)
{
	return uvs_dev_control(m_DevObj, uvs_dev_run);
}

int CDevSDK::DevicePause(void)
{
	return uvs_dev_control(m_DevObj, uvs_dev_pause);
}

int CDevSDK::DeviceStop(void)
{
	return uvs_dev_control(m_DevObj, uvs_dev_stop);
}

int CDevSDK::SetTimeOSD(int osdIndex, int x, int y, LPCTSTR szTimeMode, const uvs_font_info_tX &info)
{
#ifdef UNICODE
	return uvs_set_time_osdW(m_DevObj, osdIndex, x, y, szTimeMode, &info);
#else
	return uvs_set_time_osd(m_DevObj, osdIndex, x, y, szTimeMode, &info);
#endif
}

int CDevSDK::SetTextOSD(int osdIndex, int x, int y, int width, int height, LPCTSTR szText, const uvs_font_info_tX &info)
{
#ifdef UNICODE
	return uvs_set_text_osdW(m_DevObj, osdIndex, x, y, width, height, szText, &info);
#else
	return uvs_set_text_osd(m_DevObj, osdIndex, x, y, width, height, szText, &info);
#endif
}

int CDevSDK::SetImageOSD(int osdIndex, int x, int y, int width, int height, int imgOpacity, LPCTSTR szFileName)
{
#ifdef UNICODE
	return uvs_set_image_osdW(m_DevObj, osdIndex, x, y, width, height, imgOpacity, szFileName);
#else
	return uvs_set_image_osd(m_DevObj, osdIndex, x, y, width, height, imgOpacity, szFileName);
#endif
}

int CDevSDK::SetRectOSD(int osdIndex, int x, int y, int width, int height, const uvs_style_info_t &info)
{
	return uvs_set_rect_osd(m_DevObj, osdIndex, x, y, width, height, &info);
}

int CDevSDK::SetEllipseOSD(int osdIndex, int x, int y, int width, int height, const uvs_style_info_t &info)
{
	return uvs_set_ellipse_osd(m_DevObj, osdIndex, x, y, width, height, &info);
}

int CDevSDK::SetLineOSD(int osdIndex, int x0, int y0, int x1, int y1, const uvs_line_info_t &info)
{
	return uvs_set_line_osd(m_DevObj, osdIndex, x0, y0, x1, y1, &info);
}

int CDevSDK::VideoOSDControl(int osdIndex, uvs_osd_cmd_e cmd, int *param0, int *param1)
{
	return uvs_osd_control(m_DevObj, osdIndex, cmd, param0, param1);
}

int CDevSDK::PreviewStart(HWND hwnd, uvs_disp_type_e disp)
{
	return uvs_start_preview(m_DevObj, hwnd, disp);
}

int CDevSDK::PreviewSetRect(LPRECT wndDispRect, LPRECT videoCropRect, COLORREF bkColor)
{
	return uvs_set_preview_rect(m_DevObj, wndDispRect, videoCropRect, bkColor);
}

int CDevSDK::PreviewFreeze(BOOL bFreeze)
{
	return uvs_set_preview_freeze(m_DevObj, bFreeze);
}

int CDevSDK::PreviewIsFreeze(BOOL &isFreeze)
{
	return uvs_get_preview_freeze(m_DevObj, &isFreeze);
}

int CDevSDK::PreviewStop(void)
{
	return uvs_stop_preview(m_DevObj);
}

int CDevSDK::SetVideoDrawCallback(pUVSDrawCallback pCB, void *pUserData)
{
	return uvs_set_video_draw_callback(m_DevObj, pCB, pUserData);
}

int CDevSDK::SetRecordMetadata(int streamIndex, LPCTSTR szTitle, LPCTSTR szComment, LPCTSTR szArtist, LPCTSTR szGenre, LPCTSTR szComposer)
{
#ifdef UNICODE
	return uvs_set_record_metadataW(m_DevObj, streamIndex, szTitle, szComment, szArtist, szGenre, szComposer);
#else
	return uvs_set_record_metadata(m_DevObj, streamIndex, szTitle, szComment, szArtist, szGenre, szComposer);
#endif
}

int CDevSDK::RecordStart(int streamIndex, LPCTSTR szFile1, LPCTSTR szFile2, BOOL bRecAudio, BOOL bRepairSupport, UINT maxKBytes, UINT maxMilliSec)
{
#ifdef UNICODE
	return uvs_start_recordW(m_DevObj, streamIndex, szFile1, szFile2, bRecAudio, bRepairSupport, maxKBytes, maxMilliSec);
#else
	return uvs_start_record(m_DevObj, streamIndex, szFile1, szFile2, bRecAudio, bRepairSupport, maxKBytes, maxMilliSec);
#endif
}

int CDevSDK::GetRecordFilename(int streamIndex, uvs_filename_tX fileName[], int &fileNum)
{
#ifdef UNICODE
	return uvs_get_record_filenameW(m_DevObj, streamIndex, fileName, &fileNum);
#else
	return uvs_get_record_filename(m_DevObj, streamIndex, fileName, &fileNum);
#endif
}

int CDevSDK::SetVideoEncodeParam(int streamIndex, uvs_video_codec_e videoCodec, const uvs_encode_config_t &config)
{
	return uvs_set_video_encode_config(m_DevObj, streamIndex, videoCodec, &config);
}

int CDevSDK::GetVideoEncodeParam(int streamIndex, uvs_video_codec_e &videoCodec, uvs_encode_config_t &config)
{
	return uvs_get_video_encode_config(m_DevObj, streamIndex, &videoCodec, &config);
}

int CDevSDK::EncodeStart(int streamIndex)
{
	return uvs_start_encode(m_DevObj, streamIndex);
}

int CDevSDK::RequestVideoKeyFrame(int streamIndex)
{
	return uvs_request_video_key_frame(m_DevObj, streamIndex);
}

int CDevSDK::GetVideoEncodeStatus(int streamIndex, uvs_encode_status_t &info)
{
	return uvs_get_video_encode_status(m_DevObj, streamIndex, &info);
}

int CDevSDK::EncodeStop(int streamIndex)
{
	return uvs_stop_encode(m_DevObj, streamIndex);
}

int CDevSDK::SetVideoRawFrameCallback(pUVSFrameCallback pCB, void *pUserData)
{
	return uvs_set_video_raw_frame_callback(m_DevObj, pCB, pUserData);
}

int CDevSDK::SetVideoEncodeFrameCallback(int streamIndex, pUVSFrameCallback pCB, void *pUserData)
{
	return uvs_set_video_enc_frame_callback(m_DevObj, streamIndex, pCB, pUserData);
}

int CDevSDK::LockVideoRawFrame(uvs_frame_info_t &info, UINT waitMilliSec)
{
	return uvs_lock_video_raw_frame(m_DevObj, &info, waitMilliSec);
}

int CDevSDK::UnlockVideoRawFrame(void)
{
	return uvs_unlock_video_raw_frame(m_DevObj);
}

int CDevSDK::CopyVideoFrame(uvs_frame_info_t &info, UINT waitMilliSec, const uvs_frame_convert_t *frameConvert)
{
	return uvs_copy_video_frame(m_DevObj, frameConvert, &info, waitMilliSec);
}

int CDevSDK::SetAudioRawFrameCallback(pUVSFrameCallback pCB, void *pUserData)
{
	return uvs_set_audio_raw_frame_callback(m_DevObj, pCB, pUserData);
}

int CDevSDK::SetAudioEncodeFrameCallback(pUVSFrameCallback pCB, void *pUserData)
{
	return uvs_set_audio_enc_frame_callback(m_DevObj, pCB, pUserData);
}

int CDevSDK::LockAudioRawFrame(uvs_frame_info_t &info, UINT waitMilliSec)
{
	return uvs_lock_audio_raw_frame(m_DevObj, &info, waitMilliSec);
}

int CDevSDK::UnlockAudioRawFrame(void)
{
	return uvs_unlock_audio_raw_frame(m_DevObj);
}

int CDevSDK::CopyAudioRawFrame(uvs_frame_info_t &info, UINT waitMilliSec)
{
	return uvs_copy_audio_raw_frame(m_DevObj, &info, waitMilliSec);
}

int CDevSDK::RecordPause(int streamIndex, BOOL bResume, BOOL bRequestKeyFrame)
{
	return uvs_pause_record(m_DevObj, streamIndex, bResume, bRequestKeyFrame);
}

int CDevSDK::RecordStop(int streamIndex)
{
	return uvs_stop_record(m_DevObj, streamIndex);
}

int CDevSDK::RTSPStart(int streamIndex, USHORT rtspPort, BOOL bHasAudio, LPCTSTR szSessionName, const uvs_rtp_multicast_tX *rtpMulticast)
{
#ifdef UNICODE
	return uvs_media_stream_rtsp_startW(m_DevObj, streamIndex, rtspPort, bHasAudio, szSessionName, rtpMulticast);
#else
	return uvs_media_stream_rtsp_start(m_DevObj, streamIndex, rtspPort, bHasAudio, szSessionName, rtpMulticast);
#endif
}

int CDevSDK::RTSPGetURL(int streamIndex, uvs_url_tX &urlInfo)
{
#ifdef UNICODE
	return uvs_media_stream_rtsp_get_urlW(m_DevObj, streamIndex, &urlInfo);
#else
	return uvs_media_stream_rtsp_get_url(m_DevObj, streamIndex, &urlInfo);
#endif
}

int CDevSDK::RTSPStop(int streamIndex)
{
	return uvs_media_stream_rtsp_stop(m_DevObj, streamIndex);
}

int CDevSDK::RTMPSend(int streamIndex, LPCTSTR rtmpUrl, BOOL bHasAudio)
{
#ifdef UNICODE
	return uvs_media_stream_rtmp_sendW(m_DevObj, streamIndex, rtmpUrl, bHasAudio);
#else
	return uvs_media_stream_rtmp_send(m_DevObj, streamIndex, rtmpUrl, bHasAudio);
#endif
}

int CDevSDK::RTMPGetSendURL(int streamIndex, uvs_url_tX &urlInfo)
{
#ifdef UNICODE
	return uvs_media_stream_rtmp_get_send_urlW(m_DevObj, streamIndex, &urlInfo);
#else
	return uvs_media_stream_rtmp_get_send_url(m_DevObj, streamIndex, &urlInfo);
#endif
}

int CDevSDK::RTMPStop(int streamIndex)
{
	return uvs_media_stream_rtmp_stop(m_DevObj, streamIndex);
}

int CDevSDK::NDICreate(LPCTSTR szSourceName, LPCTSTR szGroupName, LPCTSTR szXMLMetadata, BOOL bAsync)
{
#ifdef UNICODE
	return uvs_media_stream_ndi_createW(m_DevObj, szSourceName, szGroupName, szXMLMetadata, bAsync);
#else
	return uvs_media_stream_ndi_create(m_DevObj, szSourceName, szGroupName, szXMLMetadata, bAsync);
#endif
}

int CDevSDK::NDIConfig(const uvs_frame_convert_t *frameConvert, int skipFrameRate)
{
	return uvs_media_stream_ndi_config(m_DevObj, frameConvert, skipFrameRate);
}

int CDevSDK::NDIStart(BOOL bHasAudio)
{
	return uvs_media_stream_ndi_start(m_DevObj, bHasAudio);
}

int CDevSDK::NDIStop(void)
{
	return uvs_media_stream_ndi_stop(m_DevObj);
}

int CDevSDK::NDIDestroy(void)
{
	return uvs_media_stream_ndi_destroy(m_DevObj);
}

int CDevSDK::CaptureSnapshot(LPCTSTR szFileName, UINT jpgQuality, const uvs_frame_convert_t *frameConvert)
{
#ifdef UNICODE
	return uvs_save_video_snapshotW(m_DevObj, szFileName, frameConvert, jpgQuality);
#else
	return uvs_save_video_snapshot(m_DevObj, szFileName, frameConvert, jpgQuality);
#endif
}

int CDevSDK::CreatePropertyPage(uvs_property_page_e propertyPage, HWND hOwner, int x, int y, LPCTSTR szCaption)
{
#ifdef UNICODE
	return uvs_create_property_pageW(m_DevObj, propertyPage, hOwner, x, y, szCaption);
#else
	return uvs_create_property_page(m_DevObj, propertyPage, hOwner, x, y, szCaption);
#endif
}

CFramePreview::CFramePreview(HWND hwnd, uvs_disp_type_e dispType)
{
	m_Handle = uvs_create_frame_preview(hwnd, dispType);
}

CFramePreview::~CFramePreview()
{
	if (m_Handle)
	{
		uvs_destroy_frame_preview(m_Handle);
	}
}

int CFramePreview::Preview(const uvs_frame_info_t *info)
{
	return uvs_frame_preview(m_Handle, info);
}

int CFramePreview::PreviewRect(LPRECT wndRect, LPRECT cropRect, COLORREF bkColor)
{
	return uvs_set_frame_preview_rect(m_Handle, wndRect, cropRect, bkColor);
}

CFileRTSP::CFileRTSP(LPCTSTR szFileName, USHORT rtspPort, BOOL bHasAudio, LPCTSTR szSessionName, int *result)
	: m_FileName(NULL)
{
	int r = CDevSDK::MP4FileRTSPStart(szFileName, rtspPort, bHasAudio, szSessionName);
	if (r == UVS_OK)
	{
		m_FileName = _tcsdup(szFileName);
	}

	if (result) *result = r;
}

CFileRTSP::~CFileRTSP()
{
	if (m_FileName)
	{
		CDevSDK::MP4FileRTSPStop(m_FileName);
		free(m_FileName);
	}
}

CFileRTSP* CFileRTSP::CreateInstance(LPCTSTR szFileName, USHORT rtspPort, BOOL bHasAudio, LPCTSTR szSessionName)
{
	int r;
	CFileRTSP *pFile = new (std::nothrow) CFileRTSP(szFileName, rtspPort, bHasAudio, szSessionName, &r);
	if (r == UVS_OK)
	{
		return pFile;
	}

	delete pFile;
	return NULL;
}

int CFileRTSP::GetURL(uvs_url_tX &urlInfo)
{
	return CDevSDK::MP4FileRTSPGetURL(m_FileName, urlInfo);
}

CFileRTMP::CFileRTMP(LPCTSTR szFileName, LPCTSTR rtmpUrl, BOOL bHasAudio, int *result)
	: m_FileName(NULL)
{
	int r = CDevSDK::MP4FileRTMPSend(szFileName, rtmpUrl, bHasAudio);
	if (r == UVS_OK)
	{
		m_FileName = _tcsdup(szFileName);
	}

	if (result) *result = r;
}

CFileRTMP::~CFileRTMP()
{
	if (m_FileName)
	{
		CDevSDK::MP4FileRTMPStop(m_FileName);
		free(m_FileName);
	}
}

CFileRTMP* CFileRTMP::CreateInstance(LPCTSTR szFileName, LPCTSTR rtmpUrl, BOOL bHasAudio)
{
	int r;
	CFileRTMP *pFile = new (std::nothrow) CFileRTMP(szFileName, rtmpUrl, bHasAudio, &r);
	if (r == UVS_OK)
	{
		return pFile;
	}

	delete pFile;
	return NULL;
}

int CFileRTMP::GetProgress(int &progress)
{
	return CDevSDK::MP4FileRTMPGetProgress(m_FileName, progress);
}

int CFileRTMP::GetURL(uvs_url_tX &urlInfo)
{
	return CDevSDK::MP4FileRTMPGetSendURL(m_FileName, urlInfo);
}
