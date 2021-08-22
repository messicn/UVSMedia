
// UVSLib_RTMPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UVSLib_RTMP.h"
#include "UVSLib_RTMPDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <memory>
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


// CUVSLib_RTMPDlg dialog




CUVSLib_RTMPDlg::CUVSLib_RTMPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUVSLib_RTMPDlg::IDD, pParent)
	, m_pFile(NULL)
	, m_bLive(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUVSLib_RTMPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUVSLib_RTMPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BROWSE, &CUVSLib_RTMPDlg::OnBnClickedBrowse)
	ON_BN_CLICKED(IDC_RTMP_LIVE, &CUVSLib_RTMPDlg::OnBnClickedRtmpLive)
	ON_BN_CLICKED(IDC_RTMP_FILE, &CUVSLib_RTMPDlg::OnBnClickedRtmpFile)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CUVSLib_RTMPDlg message handlers

BOOL CUVSLib_RTMPDlg::OnInitDialog()
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
		m_Dev.PreviewStart(GetDlgItem(IDC_VIDEO)->GetSafeHwnd(), uvs_disp_type_d3d);
	}

	GetDlgItem(IDC_LIVE_AUDIO)->EnableWindow(count > 0);

	SetDlgItemText(IDC_LIVE_URL, _T("rtmp://localhost:1920/live/0"));
	SetDlgItemText(IDC_FILE_URL, _T("rtmp://localhost:1920/live/1"));

	((CProgressCtrl*)GetDlgItem(IDC_SEND_PROGRESS))->SetRange(0, 100);
	SetTimer(0, 100, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUVSLib_RTMPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUVSLib_RTMPDlg::OnPaint()
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
HCURSOR CUVSLib_RTMPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUVSLib_RTMPDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(0);
	FileRTMPStop();
	m_Dev.DeviceClose();
}


void CUVSLib_RTMPDlg::FileRTMPStop()
{
	if (m_pFile)
	{
		delete m_pFile;
		m_pFile = NULL;
	}
}


void CUVSLib_RTMPDlg::OnBnClickedBrowse()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("MP4 Files|*.mp4||"));
	if (dlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_MP4_FILE, dlg.GetPathName());
	}
}


void CUVSLib_RTMPDlg::OnBnClickedRtmpLive()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		do {
			if (m_bLive)
			{
				m_Dev.RTMPStop(UVS_STREAM_ALL);
				m_Dev.EncodeStop(UVS_STREAM_ALL);
				m_bLive = FALSE;
				break;
			}

			const int mainstream = 0;
			const int substream = 1;

			CString url;
			GetDlgItemText(IDC_LIVE_URL, url);

			BOOL bAudio = ((CButton*)GetDlgItem(IDC_LIVE_AUDIO))->GetCheck() == BST_CHECKED;
			if (bAudio)
			{
				bAudio = m_Dev.SetAudioProperty(uvs_audio_codec_AAC) == UVS_OK; /* Audio is exist */
			}

			uvs_encode_config_t config = { uvs_target_usage_performance };
			config.codecProfile = uvs_codec_profile_auto;
			config.rcMode = uvs_video_rcmode_VBR;
			config.encBitRate = 6000;
			config.maxBitRate = 10000;
			config.encQuality = 28;
			config.frameRate = 30;

			// main stream config
			int r;
			if (!url.IsEmpty())
			{
				r = m_Dev.SetVideoEncodeParam(mainstream, uvs_video_codec_sw_h264, config);
				if (r != UVS_OK) break;

				r = m_Dev.RTMPSend(mainstream, url, bAudio);
				if (r != UVS_OK) break;
			}

			// sub stream config
			GetDlgItemText(IDC_LIVE_480P_URL, url);
			if (!url.IsEmpty())
			{
				config.scaleWidth = 640;
				config.scaleHeight = 480;
				config.encBitRate = 1000;
				config.maxBitRate = 3000;
				r = m_Dev.SetVideoEncodeParam(substream, uvs_video_codec_sw_h264, config);
				if (r != UVS_OK) break;

				r = m_Dev.RTMPSend(substream, url, bAudio);
				if (r != UVS_OK) break;
			}

			r = m_Dev.EncodeStart(UVS_STREAM_ALL);
			if (r != UVS_OK) break;

			m_bLive = TRUE;
		} while (0);

		SetDlgItemText(IDC_RTMP_LIVE, m_bLive ? _T("RTMP Live Stop") : _T("RTMP Live Start"));
	}
}


void CUVSLib_RTMPDlg::OnBnClickedRtmpFile()
{
	// TODO: Add your control notification handler code here
	do {
		if (m_pFile)
		{
			FileRTMPStop();
			((CProgressCtrl*)GetDlgItem(IDC_SEND_PROGRESS))->SetPos(0);
			break;
		}

		CString strFile;
		GetDlgItemText(IDC_MP4_FILE, strFile);
		if (strFile.IsEmpty()) break;

		CString strUrl;
		GetDlgItemText(IDC_FILE_URL, strUrl);
		if (strUrl.IsEmpty()) break;

		BOOL bAudio = ((CButton*)GetDlgItem(IDC_FILE_AUDIO))->GetCheck() == BST_CHECKED;
		m_pFile = CFileRTMP::CreateInstance(strFile, strUrl, bAudio);
	} while (0);

	SetDlgItemText(IDC_RTMP_FILE, m_pFile ? _T("RTMP File Stop") : _T("RTMP File Start"));
}


void CUVSLib_RTMPDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (m_pFile)
	{
		int nPos;
		int r = m_pFile->GetProgress(nPos);
		if (r == UVS_OK && nPos >= 0)
		{
			((CProgressCtrl*)GetDlgItem(IDC_SEND_PROGRESS))->SetPos(nPos);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
