
// UVSLib_RecDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UVSLib_Rec.h"
#include "UVSLib_RecDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CUVSLib_RecDlg dialog




CUVSLib_RecDlg::CUVSLib_RecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUVSLib_RecDlg::IDD, pParent)
	, m_bRecStart(FALSE)
	, m_bRecResume(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUVSLib_RecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUVSLib_RecDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_REC_CONTROL, &CUVSLib_RecDlg::OnBnClickedRecControl)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MAIN_DIR, &CUVSLib_RecDlg::OnBnClickedMainDir)
	ON_BN_CLICKED(IDC_SUB_DIR, &CUVSLib_RecDlg::OnBnClickedSubDir)
	ON_BN_CLICKED(IDC_REC_PAUSE, &CUVSLib_RecDlg::OnBnClickedRecPause)
END_MESSAGE_MAP()


// CUVSLib_RecDlg message handlers

BOOL CUVSLib_RecDlg::OnInitDialog()
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
		// init enc frame rate, default same as input
		uvs_video_format_t videoFormat;
		if (m_Dev.GetVideoProperty(videoFormat) == UVS_OK)
		{
			CComboBox *pCtrl = ((CComboBox*)GetDlgItem(IDC_ENCODE_FRAMERATE));
			pCtrl->AddString(_T("Default"));
			CString str;
			str.Format(_T("%.2f"), videoFormat.frameRate / 2);
			pCtrl->AddString(str);
		}

		if (count > 0)
		{
			m_Dev.SetAudioDevice(uvs_dev_audio_capture, info[0]);
		}
		
		m_Dev.DeviceStart();
		m_Dev.PreviewStart(GetDlgItem(IDC_VIDEO)->GetSafeHwnd());
	}

	GetDlgItem(IDC_AUDIO_ENCODER)->EnableWindow(count > 0);

	((CComboBox*)GetDlgItem(IDC_VIDEO_ENCODER))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_AUDIO_ENCODER))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_ENCODE_USAGE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_VIDEO_BITRATE))->SetCurSel(1);
	((CComboBox*)GetDlgItem(IDC_VIDEO_MAX_BITRATE))->SetCurSel(1);
	((CComboBox*)GetDlgItem(IDC_RATE_CONTROL))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_VIDEO_CROP))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_VIDEO_SCALE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_SCALE_USAGE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_ENCODE_FRAMERATE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_REC_DURATION))->SetCurSel(2);
	((CComboBox*)GetDlgItem(IDC_REC_SIZE))->SetCurSel(0);

	TCHAR str[MAX_PATH];
	GetModuleFileName(NULL, str, _countof(str));
	PathRemoveFileSpec(str);
	SetDlgItemText(IDC_REC_MAIN, str);

	SetTimer(0, 1000, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUVSLib_RecDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUVSLib_RecDlg::OnPaint()
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
HCURSOR CUVSLib_RecDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUVSLib_RecDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(0);
	m_Dev.DeviceClose();
}


void CUVSLib_RecDlg::OnBnClickedRecControl()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		if (m_bRecStart)
		{
			m_Dev.RecordStop(UVS_STREAM_ALL);
			m_Dev.EncodeStop(UVS_STREAM_ALL);
			m_bRecStart = FALSE;
			m_bRecResume = FALSE;
			SetDlgItemText(IDC_REC_PAUSE, _T("Rec Pause"));
		}
		else
		{
			static uvs_video_codec_e venc[] = { uvs_video_codec_intel_h264, uvs_video_codec_intel_h265, uvs_video_codec_nvidia_h264,
												uvs_video_codec_nvidia_h265, uvs_video_codec_sw_h264, uvs_video_codec_sw_x264 };
			static uvs_audio_codec_e aenc[] = { uvs_audio_codec_none, uvs_audio_codec_AAC, uvs_audio_codec_MP3 };
			static uvs_target_usage_e encusage[] = { uvs_target_usage_performance, uvs_target_usage_balance, uvs_target_usage_quality };
			static int encKbps[] = { 4000, 8000, 10000 };
			static int maxKbps[] = { 8000, 12000 };
			static uvs_video_rcmode_e rcmode[] = { uvs_video_rcmode_CBR, uvs_video_rcmode_CQP, uvs_video_rcmode_VBR };
			static int croprc[][4] = { { 0, 0, 0, 0 }/* None */, { 160, 120, 640, 480 }/* VGA */, { 160, 120, 1280, 720 }/* 720P */ };
			static int scalesz[][2] = { { 0, 0 }/* None */, { 640, 480 }/* VGA */, { 1920, 1080 }/* 1080P */ };
			static uvs_scale_usage_e scaleusage[] = { uvs_scale_usage_performance, uvs_scale_usage_balance, uvs_scale_usage_quality, uvs_scale_usage_high_quality };

			static UINT recDur[] = { 0, 60 * 1000, 5 * 60 * 1000, 15 * 60 * 1000 };
			static UINT recKB[] = { 0, 128 * 1024, 256 * 1024, 512 * 1024 };

			const int mainstream = 0;
			const int substream = 1;

			do {
				uvs_video_codec_e vcodec = uvs_video_codec_none;
				uvs_audio_codec_e acodec = uvs_audio_codec_none;
				uvs_encode_config_t config;
				memset(&config, 0, sizeof(uvs_encode_config_t));
				config.encQuality = 28;
				config.entropyCoding = uvs_avc_entropy_CABAC;

				int nSel = ((CComboBox*)GetDlgItem(IDC_VIDEO_ENCODER))->GetCurSel();
				if (nSel == CB_ERR || nSel >= _countof(venc)) break;
				vcodec = venc[nSel];

				nSel = ((CComboBox*)GetDlgItem(IDC_AUDIO_ENCODER))->GetCurSel();
				if (nSel == CB_ERR || nSel >= _countof(aenc)) break;
				acodec = aenc[nSel];

				// enc usage quality or performance related to encoding framerate
				nSel = ((CComboBox*)GetDlgItem(IDC_ENCODE_USAGE))->GetCurSel();
				if (nSel == CB_ERR || nSel >= _countof(encusage)) break;
				config.targetUsage = encusage[nSel];

				// enc bitrate control
				nSel = ((CComboBox*)GetDlgItem(IDC_VIDEO_BITRATE))->GetCurSel();
				if (nSel == CB_ERR || nSel >= _countof(encKbps)) break;
				config.encBitRate = encKbps[nSel];

				nSel = ((CComboBox*)GetDlgItem(IDC_VIDEO_MAX_BITRATE))->GetCurSel();
				if (nSel == CB_ERR || nSel >= _countof(maxKbps)) break;
				config.maxBitRate = maxKbps[nSel];

				nSel = ((CComboBox*)GetDlgItem(IDC_RATE_CONTROL))->GetCurSel();
				if (nSel == CB_ERR || nSel >= _countof(rcmode)) break;
				config.rcMode = rcmode[nSel];

				// enc video crop
				nSel = ((CComboBox*)GetDlgItem(IDC_VIDEO_CROP))->GetCurSel();
				if (nSel == CB_ERR || nSel >= _countof(croprc)) break;
				config.cropLeft = croprc[nSel][0];
				config.cropTop = croprc[nSel][1];
				config.cropWidth = croprc[nSel][2];
				config.cropHeight = croprc[nSel][3];

				// enc video scale
				nSel = ((CComboBox*)GetDlgItem(IDC_VIDEO_SCALE))->GetCurSel();
				if (nSel == CB_ERR || nSel >= _countof(scalesz)) break;
				config.scaleWidth = scalesz[nSel][0];
				config.scaleHeight = scalesz[nSel][1];

				nSel = ((CComboBox*)GetDlgItem(IDC_SCALE_USAGE))->GetCurSel();
				if (nSel == CB_ERR || nSel >= _countof(scaleusage)) break;
				config.scaleUsage = scaleusage[nSel];

				// enc frame rate, 0 same as input
				uvs_video_format_t videoFormat;
				if (m_Dev.GetVideoProperty(videoFormat) != UVS_OK) break;

				nSel = ((CComboBox*)GetDlgItem(IDC_ENCODE_FRAMERATE))->GetCurSel();
				if (nSel == CB_ERR) break;
				config.frameRate = nSel == 0 ? 0 : videoFormat.frameRate / 2;
				
				// auto rec limit duration(ms), 0 manual control
				nSel = ((CComboBox*)GetDlgItem(IDC_REC_DURATION))->GetCurSel();
				if (nSel == CB_ERR || nSel >= _countof(recDur)) break;
				UINT dur = recDur[nSel];

				// auto rec limit file size(KB), 0 manual control
				nSel = ((CComboBox*)GetDlgItem(IDC_REC_SIZE))->GetCurSel();
				if (nSel == CB_ERR || nSel >= _countof(recKB)) break;
				UINT sz = recKB[nSel];

				// rec file repair support
				BOOL bRepair = ((CButton*)GetDlgItem(IDC_REPAIR))->GetCheck() == BST_CHECKED;

				// main stream config
				CString dir;
				GetDlgItemText(IDC_REC_MAIN, dir);
				if (!dir.IsEmpty())
				{
					if (m_Dev.SetVideoEncodeParam(mainstream, vcodec, config) != UVS_OK)
					{
						if (CDevSDK::QueryVideoEncoder(vcodec) != UVS_OK)
						{
							MessageBox(_T("HW not support or codec library not found!"));
						}
						break;
					}

					/* %M month, %D month of day, %H 24 hours, %h 12 hours, %m minute, %s second, %Y year,
					 * %t AM/PM, %N month name, %n month short name, %W week name, %w week short name, %i stream index, %% % */
					PathAppend(dir.GetBuffer(MAX_PATH), _T("%Y%M%D_%H%m%s_%i.mp4"));
					dir.ReleaseBuffer();

					if (m_Dev.SetRecordMetadata(mainstream, _T("Main Stream"), _T("UVSLib_Rec"), _T("UVSLib"), _T("Main")) != UVS_OK) break;
					if (m_Dev.RecordStart(mainstream, dir, NULL, acodec != uvs_audio_codec_none, bRepair, sz, dur) != UVS_OK) break;
				}

				// sub stream config
				GetDlgItemText(IDC_REC_SUB, dir);
				if (!dir.IsEmpty())
				{
					config.scaleWidth = 640;
					config.scaleHeight = 480;
					config.encBitRate /= 2;
					config.maxBitRate /= 2;
					if (m_Dev.SetVideoEncodeParam(substream, vcodec, config) != UVS_OK)
					{
						if (CDevSDK::QueryVideoEncoder(vcodec) != UVS_OK)
						{
							MessageBox(_T("HW not support or codec library not found!"));
						}
						break;
					}

					PathAppend(dir.GetBuffer(MAX_PATH), _T("%Y%M%D_%H%m%s_%i.mp4"));
					dir.ReleaseBuffer();

					if (m_Dev.SetRecordMetadata(substream, _T("Sub Stream"), _T("UVSLib_Rec"), _T("UVSLib"), _T("480P")) != UVS_OK) break;
					if (m_Dev.RecordStart(substream, dir, NULL, acodec != uvs_audio_codec_none, bRepair, sz, dur) != UVS_OK) break;
				}

				// audio stream config
				if (acodec != uvs_audio_codec_none)
				{
					m_Dev.SetAudioProperty(acodec);
				}

				if (m_Dev.EncodeStart(UVS_STREAM_ALL) != UVS_OK) break;
				m_bRecStart = TRUE;
			} while (0);
		}

		SetDlgItemText(IDC_REC_CONTROL, m_bRecStart ? _T("Rec Stop") : _T("Rec Start"));
	}
}


void CUVSLib_RecDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (m_Dev)
	{
		if (m_bRecStart)
		{
			uvs_encode_status_t info;
			if (m_Dev.GetVideoEncodeStatus(0, info) == UVS_OK)
			{
				CString str;
				str.Format(_T("Input Frames:%d (%.2ffps)\nEncode Frames:%d (%.2ffps)"), info.inputFrames, info.inputFrameRate, info.encodeFrames, info.encodeFrameRate);
				SetDlgItemText(IDC_STATUS, str);
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CUVSLib_RecDlg::BrowseFolder(UINT nID)
{
	LPMALLOC lpMalloc;
	if (::SHGetMalloc(&lpMalloc) != NOERROR)
		return;

	TCHAR szDisplayName[_MAX_PATH];
	TCHAR szBuffer[_MAX_PATH];
	BROWSEINFO browseInfo;
	browseInfo.hwndOwner = GetSafeHwnd();
	browseInfo.pidlRoot = NULL;
	browseInfo.pszDisplayName = szDisplayName;
	browseInfo.lpszTitle = _T("Choose File Save Folder");
	browseInfo.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
	browseInfo.lpfn = NULL;
	browseInfo.lParam = 0;

	LPITEMIDLIST lpItemIDList;
	if ((lpItemIDList = ::SHBrowseForFolder(&browseInfo)) != NULL)
	{
		// Get the path of the selected folder from the item ID list.
		if (::SHGetPathFromIDList(lpItemIDList, szBuffer))
		{
			if (szBuffer[0] != '\0') 
			{
				SetDlgItemText(nID, szBuffer);
			}
		}
	}

	if (lpItemIDList)
	{
		lpMalloc->Free(lpItemIDList);
	}

	lpMalloc->Release();
}


void CUVSLib_RecDlg::OnBnClickedMainDir()
{
	// TODO: Add your control notification handler code here
	BrowseFolder(IDC_REC_MAIN);
}


void CUVSLib_RecDlg::OnBnClickedSubDir()
{
	// TODO: Add your control notification handler code here
	BrowseFolder(IDC_REC_SUB);
}


void CUVSLib_RecDlg::OnBnClickedRecPause()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		if (m_bRecStart)
		{
			m_Dev.RecordPause(UVS_STREAM_ALL, m_bRecResume);
			m_bRecResume = !m_bRecResume;
			SetDlgItemText(IDC_REC_PAUSE, m_bRecResume ? _T("Rec Resume") : _T("Rec Pause"));
		}
	}
}
