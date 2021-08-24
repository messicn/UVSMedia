
// UVSLib_DataFrameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UVSLib_DataFrame.h"
#include "UVSLib_DataFrameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define COPY_FRAME_TO_USER_BUFFER 0

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUVSLib_DataFrameDlg dialog

static void FrameInfoPrint(const uvs_frame_info_t &Frame)
{
	enum { NONE, YUY2, UYVY, YV12,
			I420, NV12, NV21, I422,
			I444, BGR24, RGB24, ARGB32,
			RGBA32, ABGR32, BGRA32, MJPG,
			H264IDR, H264I, H264P, H264B,
			H265IDR, H265I, H265P, H265B,
			PCM, MP3, AAC };
	LPCTSTR str[] = { _T("NONE"), _T("Video: YUY2"), _T("Video: UYVY"), _T("Video: YV12"),
					_T("Video: I420"), _T("Video: NV12"), _T("Video: NV21"), _T("Video: I422"),
					_T("Video: I444"), _T("Video: BGR24"), _T("Video: RGB24"), _T("Video: ARGB32"),
					_T("Video: RGBA32"), _T("Video: ABGR32"), _T("Video: BGRA32"), _T("Video: MJPG"),
					_T("Video: H.264(AVC) IDR"), _T("Video: H.264(AVC) I"), _T("Video: H.264(AVC) P"), _T("Video: H.264(AVC) B"),
					_T("Video: H.265(HEVC) IDR"), _T("Video: H.265(HEVC) I"), _T("Video: H.265(HEVC) P"), _T("Video: H.265(HEVC) B"),
					_T("Audio: PCM"), _T("Audio: MP3"), _T("Audio: AAC") };

	int index;
	switch (Frame.frameType)
	{
	case uvs_frame_video_YUY2:
		index = YUY2; break;
	case uvs_frame_video_UYVY:
		index = UYVY; break;
	case uvs_frame_video_YV12:
		index = YV12; break;
	case uvs_frame_video_I420:
		index = I420; break;
	case uvs_frame_video_NV12:
		index = NV12; break;
	case uvs_frame_video_NV21:
		index = NV21; break;
	case uvs_frame_video_I422:
		index = I422; break;
	case uvs_frame_video_I444:
		index = I444; break;
	case uvs_frame_video_BGR24:
		index = BGR24; break;
	case uvs_frame_video_RGB24:
		index = RGB24; break;
	case uvs_frame_video_ARGB32:
		index = ARGB32; break;
	case uvs_frame_video_RGBA32:
		index = RGBA32; break;
	case uvs_frame_video_ABGR32:
		index = ABGR32; break;
	case uvs_frame_video_BGRA32:
		index = BGRA32; break;
	case uvs_frame_video_MJPG:
		index = MJPG; break;
	case uvs_frame_video_H264_IDR:
		index = H264IDR; break;
	case uvs_frame_video_H264_I:
		index = H264I; break;
	case uvs_frame_video_H264_P:
		index = H264P; break;
	case uvs_frame_video_H264_B:
		index = H264B; break;
	case uvs_frame_video_H265_IDR:
		index = H265IDR; break;
	case uvs_frame_video_H265_I:
		index = H265I; break;
	case uvs_frame_video_H265_P:
		index = H265P; break;
	case uvs_frame_video_H265_B:
		index = H265B; break;
	case uvs_frame_audio_PCM:
		index = PCM; break;
	case uvs_frame_audio_MP3:
		index = MP3; break;
	case uvs_frame_audio_AAC:
		index = AAC; break;

	default:
		index = NONE; break;
	}

	CString s;
	if (index >= PCM)
	{ // audio
		s.Format(_T("%s channels %u bits per sample %u samples per second %u data %#p size %u timestamp %lld\n"),
			str[index],
			Frame.audioChannels,
			Frame.audioBitsPerSample,
			Frame.audioSamplesPerSec,
			Frame.frameData,
			Frame.frameDataLen,
			Frame.timeStamp);
	}
	else if (index > NONE)
	{
		s.Format(_T("%s width %u height %u stride %u %u data %#p size %u timestamp %lld\n"),
			str[index],
			Frame.videoWidth,
			Frame.videoHeight,
			Frame.videoDataStride[0],
			Frame.videoDataStride[1],
			Frame.frameData,
			Frame.frameDataLen,
			Frame.timeStamp);
	}
	else
	{
		s = str[NONE];
	}

	OutputDebugString(s);
}

static void CALLBACK DataFrameCallback(uvsobj_handle obj, const uvs_frame_info_t *pFrame, void *pUserData)
{
	if (pFrame) FrameInfoPrint(*pFrame);
}


CUVSLib_DataFrameDlg::CUVSLib_DataFrameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUVSLib_DataFrameDlg::IDD, pParent)
	, m_bAudioCallback(FALSE)
	, m_bVideoCallback(FALSE)
	, m_bEncCallback(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUVSLib_DataFrameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUVSLib_DataFrameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_VIDEO_SNAPSHOT, &CUVSLib_DataFrameDlg::OnBnClickedVideoSnapshot)
	ON_BN_CLICKED(IDC_VIDEO_RAW, &CUVSLib_DataFrameDlg::OnBnClickedVideoRaw)
	ON_BN_CLICKED(IDC_AUDIO_RAW, &CUVSLib_DataFrameDlg::OnBnClickedAudioRaw)
	ON_BN_CLICKED(IDC_ENCODE_DATA, &CUVSLib_DataFrameDlg::OnBnClickedEncodeData)
	ON_BN_CLICKED(IDC_VIDEO_LOCK, &CUVSLib_DataFrameDlg::OnBnClickedVideoLock)
	ON_BN_CLICKED(IDC_AUDIO_LOCK, &CUVSLib_DataFrameDlg::OnBnClickedAudioLock)
	ON_BN_CLICKED(IDC_VIDEO_COPY, &CUVSLib_DataFrameDlg::OnBnClickedVideoCopy)
	ON_BN_CLICKED(IDC_AUDIO_COPY, &CUVSLib_DataFrameDlg::OnBnClickedAudioCopy)
END_MESSAGE_MAP()


// CUVSLib_DataFrameDlg message handlers

BOOL CUVSLib_DataFrameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	const int maxAudioDevCount = 8;
	uvs_dev_info_tX info[maxAudioDevCount];
	int count = maxAudioDevCount;
	CDevSDK::EnumDevice(uvs_dev_audio_capture, info, count);

	m_Dev.DeviceOpen(0);
	if (m_Dev)
	{
		if (count > 0)
		{
			m_Dev.SetAudioDevice(uvs_dev_audio_capture, info[0]);
		}

		m_Dev.DeviceStart();
		m_Dev.PreviewStart(GetDlgItem(IDC_VIDEO)->GetSafeHwnd());
	}

	GetDlgItem(IDC_ENCODE_AUDIO)->EnableWindow(count > 0);
	GetDlgItem(IDC_AUDIO_COPY)->EnableWindow(count > 0);
	GetDlgItem(IDC_AUDIO_RAW)->EnableWindow(count > 0);
	GetDlgItem(IDC_AUDIO_LOCK)->EnableWindow(count > 0);

	((CComboBox*)GetDlgItem(IDC_VIDEO_ROTATE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_VIDEO_SCALE))->SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUVSLib_DataFrameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUVSLib_DataFrameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUVSLib_DataFrameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUVSLib_DataFrameDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	m_Dev.DeviceClose();
}

BOOL CUVSLib_DataFrameDlg::GetVideoConvertParam(uvs_frame_convert_t &convert)
{
	static uvs_rotate_mode_e rotatemode[] = { uvs_rotate_none, uvs_rotate_90, uvs_rotate_180, uvs_rotate_270 };

	memset(&convert, 0, sizeof(uvs_frame_convert_t));

	int nSel = ((CComboBox*)GetDlgItem(IDC_VIDEO_ROTATE))->GetCurSel();
	if (nSel != CB_ERR)
	{
		// video rotate
		convert.rotateMode = rotatemode[nSel];

		// video scale
		nSel = ((CComboBox*)GetDlgItem(IDC_VIDEO_SCALE))->GetCurSel();
		if (nSel != CB_ERR)
		{
			if (nSel > 0)
			{
				convert.scaleWidth = nSel == 1 ? 640 : 3840;
				convert.scaleHeight = nSel == 1 ? 480 : 2160;
			}
		}

		// video mirror
		convert.bFlip = ((CButton*)GetDlgItem(IDC_FRAME_FLIP))->GetCheck() == BST_CHECKED;
		convert.bMirror = ((CButton*)GetDlgItem(IDC_FRAME_MIRROR))->GetCheck() == BST_CHECKED;
		return TRUE;
	}

	return FALSE;
}


void CUVSLib_DataFrameDlg::OnBnClickedVideoSnapshot()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		CFileDialog dlg(FALSE, _T(".jpg"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Jpeg Files(*.jpg);Png Files(*.png);Bitmap Files(*.bmp)|*.jpg;*.png;*.bmp||"));
		if (dlg.DoModal() == IDOK)
		{
			uvs_frame_convert_t convert;
			GetVideoConvertParam(convert);
			if (convert.frameType != uvs_frame_NONE ||
				convert.bFlip || convert.bMirror ||
				convert.rotateMode != uvs_rotate_none ||
				(convert.scaleWidth > 0 && convert.scaleHeight > 0))
			{
				m_Dev.CaptureSnapshot(dlg.GetPathName(), 100, &convert);
			}
			else
			{ // without conversion
				m_Dev.CaptureSnapshot(dlg.GetPathName());
			}
		}
	}
}


void CUVSLib_DataFrameDlg::OnBnClickedVideoRaw()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		if (m_Dev.SetVideoRawFrameCallback(m_bVideoCallback ? NULL : DataFrameCallback) == UVS_OK)
		{
			m_bVideoCallback = !m_bVideoCallback;
		}
		
		SetDlgItemText(IDC_VIDEO_RAW, m_bVideoCallback ? _T("Video Raw Data Stop") : _T("Video Raw Data Callback"));
	}
}


void CUVSLib_DataFrameDlg::OnBnClickedAudioRaw()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		if (m_Dev.SetAudioRawFrameCallback(m_bAudioCallback ? NULL : DataFrameCallback) == UVS_OK)
		{
			m_bAudioCallback = !m_bAudioCallback;
		}

		SetDlgItemText(IDC_AUDIO_RAW, m_bAudioCallback ? _T("Audio Raw Data Stop") : _T("Audio Raw Data Callback"));
	}
}


void CUVSLib_DataFrameDlg::OnBnClickedEncodeData()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		do {
			if (m_bEncCallback)
			{
				m_Dev.SetAudioEncodeFrameCallback(NULL);
				m_Dev.SetVideoEncodeFrameCallback(0, NULL);
				m_Dev.EncodeStop(0);
				m_bEncCallback = FALSE;
				break;
			}

			// video stream config
			uvs_encode_config_t config = { uvs_target_usage_performance };
			config.codecProfile = uvs_codec_profile_auto;
			config.rcMode = uvs_video_rcmode_VBR;
			config.encBitRate = 4000;
			config.maxBitRate = 8000;
			config.encQuality = 28;
			int r = m_Dev.SetVideoEncodeParam(0, uvs_video_codec_sw_h264, config);
			if (r != UVS_OK) break;

			r = m_Dev.SetVideoEncodeFrameCallback(0, DataFrameCallback);
			if (r != UVS_OK) break;

			// audio stream config
			BOOL bAudioStream = ((CButton*)GetDlgItem(IDC_ENCODE_AUDIO))->GetCheck() == BST_CHECKED;
			if (bAudioStream)
			{
				if (m_Dev.SetAudioProperty(uvs_audio_codec_AAC) == UVS_OK)
				{
					m_Dev.SetAudioEncodeFrameCallback(DataFrameCallback);
				}
			}

			r = m_Dev.EncodeStart(0);
			if (r != UVS_OK) break;

			m_bEncCallback = TRUE;
		} while (0);

		SetDlgItemText(IDC_ENCODE_DATA, m_bEncCallback ? _T("Encode Data Stop") : _T("Encode Data Callback"));
	}
}


void CUVSLib_DataFrameDlg::OnBnClickedVideoLock()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		uvs_frame_info_t info;
		if (m_Dev.LockVideoRawFrame(info) == UVS_OK)
		{
			FrameInfoPrint(info);
			m_Dev.UnlockVideoRawFrame();
		}
	}
}


void CUVSLib_DataFrameDlg::OnBnClickedAudioLock()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		uvs_frame_info_t info;
		if (m_Dev.LockAudioRawFrame(info) == UVS_OK)
		{
			FrameInfoPrint(info);
			m_Dev.UnlockAudioRawFrame();
		}
	}
}


void CUVSLib_DataFrameDlg::OnBnClickedVideoCopy()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		uvs_frame_convert_t convert;
		GetVideoConvertParam(convert);

		uvs_frame_info_t info = { uvs_frame_NONE };

	#if COPY_FRAME_TO_USER_BUFFER
		static BYTE buf[4 * 3840 * 2160];

		uvs_video_format_t format;
		if (m_Dev.GetVideoProperty(format) != UVS_OK) return;

		/* Calc buffer size */
		int width = max(format.videoWidth, convert.scaleWidth);
		int height = max(format.videoHeight, convert.scaleHeight);
		int sz = CDevSDK::CalcBufferSize(format.frameType, width, height);

		/* Set user buffer */
		info.frameData = buf;
		info.frameDataLen = sz;
	#endif

		if (convert.frameType != uvs_frame_NONE ||
			convert.bFlip || convert.bMirror ||
			convert.rotateMode != uvs_rotate_none ||
			(convert.scaleWidth > 0 && convert.scaleHeight > 0))
		{
			if (m_Dev.CopyVideoFrame(info, 1000, &convert) != UVS_OK) return;
		}
		else if (m_Dev.CopyVideoFrame(info) != UVS_OK) return;  // without conversion

		FrameInfoPrint(info);
	}
}


void CUVSLib_DataFrameDlg::OnBnClickedAudioCopy()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		uvs_frame_info_t info = { uvs_frame_NONE };

	#if COPY_FRAME_TO_USER_BUFFER
		static BYTE UserFrameBuffer[256 * 1024];
		/* Set user buffer */
		info.frameData = UserFrameBuffer;
		info.frameDataLen = sizeof(UserFrameBuffer);
	#endif

		if (m_Dev.CopyAudioRawFrame(info) == UVS_OK)
		{
			FrameInfoPrint(info);
		}
	}
}
