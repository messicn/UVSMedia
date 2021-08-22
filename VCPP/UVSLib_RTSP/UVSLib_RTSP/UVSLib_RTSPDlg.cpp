
// UVSLib_RTSPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UVSLib_RTSP.h"
#include "UVSLib_RTSPDlg.h"
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


// CUVSLib_RTSPDlg dialog



CUVSLib_RTSPDlg::CUVSLib_RTSPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUVSLib_RTSPDlg::IDD, pParent)
	, m_nPort(0)
	, m_pFile(NULL)
	, m_bLive(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUVSLib_RTSPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUVSLib_RTSPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_MP4_BROWSE, &CUVSLib_RTSPDlg::OnBnClickedMp4Browse)
	ON_BN_CLICKED(IDC_RTSP_LIVE, &CUVSLib_RTSPDlg::OnBnClickedRtspLive)
	ON_BN_CLICKED(IDC_RTSP_FILE, &CUVSLib_RTSPDlg::OnBnClickedRtspFile)
END_MESSAGE_MAP()


// CUVSLib_RTSPDlg message handlers

BOOL CUVSLib_RTSPDlg::OnInitDialog()
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

	GetDlgItem(IDC_LIVE_AUDIO)->EnableWindow(count > 0);

	((CComboBox*)GetDlgItem(IDC_RTSP_PORT))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_STREAM_MODE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_HTTP_TUNER_PORT))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_RTP_MULTICAST))->SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUVSLib_RTSPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUVSLib_RTSPDlg::OnPaint()
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
HCURSOR CUVSLib_RTSPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUVSLib_RTSPDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	if (m_bLive) OnBnClickedRtspLive();
	FileRTSPStreamClose();
	m_Dev.DeviceClose();
}

BOOL CUVSLib_RTSPDlg::RTSPServerCreate()
{
	if (m_nPort == 0)
	{
		do {
			int nSel = ((CComboBox*)GetDlgItem(IDC_RTSP_PORT))->GetCurSel();
			if (nSel == CB_ERR) break;
			m_nPort = nSel == 0 ? 554 : 8554;

			nSel = ((CComboBox*)GetDlgItem(IDC_HTTP_TUNER_PORT))->GetCurSel();
			if (nSel == CB_ERR) break;
			USHORT nHttpTunerPort = nSel == 0 ? 0 : 8080;

			CString strUser;
			CString strPassword;
			GetDlgItemText(IDC_RTSP_USERNAME, strUser);
			GetDlgItemText(IDC_RTSP_PASSWORD, strPassword);

			LPCTSTR username = NULL;
			LPCTSTR password = NULL;
			if (!(strUser.IsEmpty() || strPassword.IsEmpty()))
			{
				username = strUser;
				password = strPassword;
			}

			int r = CDevSDK::RTSPServerCreate(m_nPort, username, password, nHttpTunerPort);
			if (r == UVS_OK) return TRUE;
		} while (0);
		
		m_nPort = 0;
	}

	return m_nPort > 0;
}


void CUVSLib_RTSPDlg::RTSPServerDestroy()
{
	if (m_bLive || m_pFile) return;

	if (m_nPort > 0)
	{
		CDevSDK::RTSPServerDestroy(m_nPort);
		m_nPort = 0;
	}
}


void CUVSLib_RTSPDlg::FileRTSPStreamClose()
{
	if (m_pFile)
	{
		delete m_pFile;
		m_pFile = NULL;
	}
}


void CUVSLib_RTSPDlg::OnBnClickedMp4Browse()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("MP4 Files|*.mp4||"));
	if (dlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_MP4_FILE, dlg.GetPathName());
	}
}


void CUVSLib_RTSPDlg::OnBnClickedRtspLive()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		do {
			if (m_bLive)
			{
				m_Dev.RTSPStop(UVS_STREAM_ALL);
				m_Dev.EncodeStop(UVS_STREAM_ALL);
				SetDlgItemText(IDC_LIVE_URL, _T(""));
				SetDlgItemText(IDC_LIVE_480P_URL, _T(""));
				m_bLive = FALSE;

				RTSPServerDestroy();
				break;
			}

			const int mainstream = 0;
			const int substream = 1;

			// rtsp server create
			if (!RTSPServerCreate()) break;

			// audio stream config
			int nSel = ((CComboBox*)GetDlgItem(IDC_LIVE_AUDIO))->GetCurSel();
			if (nSel == CB_ERR) break;

			BOOL bAudio = nSel != 0;
			if (bAudio)
			{
				bAudio = m_Dev.SetAudioProperty(nSel == 1 ? uvs_audio_codec_AAC : uvs_audio_codec_MP3) == UVS_OK; /* Audio is exist */
			}

			// rtp multicast config
			nSel = ((CComboBox*)GetDlgItem(IDC_RTP_MULTICAST))->GetCurSel();
			if (nSel == CB_ERR) break;
			BOOL bMulticast = nSel != 0;
			uvs_rtp_multicast_tX info;
			if (bMulticast)
			{
				info.ipAddress = _T("233.233.233.233");
				info.ipPort = 18888;
			}

			// main stream config
			uvs_encode_config_t config = { uvs_target_usage_performance };
			config.codecProfile = uvs_codec_profile_auto;
			config.rcMode = uvs_video_rcmode_VBR;
			config.encBitRate = 4000;
			config.maxBitRate = 10000;
			config.encQuality = 28;
			config.frameRate = 30;
			int r = m_Dev.SetVideoEncodeParam(mainstream, uvs_video_codec_sw_h264, config);
			if (r != UVS_OK) break;

			// sub stream config
			BOOL bSubStream = ((CButton*)GetDlgItem(IDC_SUBSTREAM))->GetCheck() == BST_CHECKED;
			if (bSubStream)
			{
				config.scaleWidth = 640;
				config.scaleHeight = 480;
				config.encBitRate = 1000;
				config.maxBitRate = 3000;
				r = m_Dev.SetVideoEncodeParam(substream, uvs_video_codec_intel_h264, config);
				if (r != UVS_OK) break;
			}

			// rtsp start
			r = m_Dev.RTSPStart(mainstream, m_nPort, bAudio, _T("main"), bMulticast ? &info : NULL);
			if (r != UVS_OK) break;

			if (bSubStream)
			{
				r = m_Dev.RTSPStart(substream, m_nPort, bAudio, _T("sub"), bMulticast ? &info : NULL);
				if (r != UVS_OK) break;
			}

			r = m_Dev.EncodeStart(UVS_STREAM_ALL);
			if (r != UVS_OK) break;

			uvs_url_tX url;
			if (m_Dev.RTSPGetURL(0, url) == UVS_OK)
			{
				SetDlgItemText(IDC_LIVE_URL, url.szURL);
			}

			if (bSubStream)
			{
				if (m_Dev.RTSPGetURL(1, url) == UVS_OK)
				{
					SetDlgItemText(IDC_LIVE_480P_URL, url.szURL);
				}
			}

			m_bLive = TRUE;
		} while (0);

		SetDlgItemText(IDC_RTSP_LIVE, m_bLive ? _T("RTSP Live Stop") : _T("RTSP Live Start"));
	}
}


void CUVSLib_RTSPDlg::OnBnClickedRtspFile()
{
	// TODO: Add your control notification handler code here
	do {
		if (m_pFile)
		{
			FileRTSPStreamClose();
			SetDlgItemText(IDC_FILE_URL, _T(""));
			RTSPServerDestroy();
			break;
		}

		if (!RTSPServerCreate()) break;

		CString strFile;
		GetDlgItemText(IDC_MP4_FILE, strFile);
		if (strFile.IsEmpty()) break;
		
		BOOL bAudio = ((CButton*)GetDlgItem(IDC_MP4_AUDIO))->GetCheck() == BST_CHECKED;
		m_pFile = CFileRTSP::CreateInstance(strFile, m_nPort, bAudio, NULL);
		if (m_pFile)
		{
			uvs_url_tX url;
			if (m_pFile->GetURL(url) == UVS_OK)
			{
				SetDlgItemText(IDC_FILE_URL, url.szURL);
			}
		}
	} while (0);

	SetDlgItemText(IDC_RTSP_FILE, m_pFile ? _T("RTSP File Stop") : _T("RTSP File Start"));
}
