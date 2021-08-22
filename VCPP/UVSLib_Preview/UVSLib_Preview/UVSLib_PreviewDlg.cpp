
// UVSLib_PreviewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UVSLib_Preview.h"
#include "UVSLib_PreviewDlg.h"
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


// CUVSLib_PreviewDlg dialog


CUVSLib_PreviewDlg::CUVSLib_PreviewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUVSLib_PreviewDlg::IDD, pParent)
	, m_nAudioIndex(-1)
	, m_nVideoIndex(-1)
	, m_nAudioRender(-1)
	, m_pVideoWnd(NULL)
	, m_pParentWnd(NULL)
	, m_bFullScreen(FALSE)
	, m_bDigitalZoom(FALSE)
	, m_bDispRect(FALSE)
{
	SetRectEmpty(&m_VideoRect);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUVSLib_PreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUVSLib_PreviewDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_AUDIO_INPUT, &CUVSLib_PreviewDlg::OnSelchangeAudioInput)
	ON_CBN_SELCHANGE(IDC_VIDEO_INPUT, &CUVSLib_PreviewDlg::OnSelchangeVideoInput)
	ON_BN_CLICKED(IDC_DISP_D3D, &CUVSLib_PreviewDlg::OnClickedDisp)
	ON_BN_CLICKED(IDC_DISP_DDRAW, &CUVSLib_PreviewDlg::OnClickedDisp)
	ON_BN_CLICKED(IDC_FULL_SCREEN, &CUVSLib_PreviewDlg::OnBnClickedFullScreen)
	ON_BN_CLICKED(IDC_DIGITAL_ZOOM, &CUVSLib_PreviewDlg::OnBnClickedDigitalZoom)
	ON_BN_CLICKED(IDC_DISP_RECT, &CUVSLib_PreviewDlg::OnBnClickedDispRect)
	ON_BN_CLICKED(IDC_DISP_FREEZE, &CUVSLib_PreviewDlg::OnBnClickedDispFreeze)
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_AUDIO_OUTPUT, &CUVSLib_PreviewDlg::OnCbnSelchangeAudioOutput)
	ON_BN_CLICKED(IDC_MUTE, &CUVSLib_PreviewDlg::OnBnClickedMute)
	ON_BN_CLICKED(IDC_FLIP, &CUVSLib_PreviewDlg::OnClickedFlip)
	ON_BN_CLICKED(IDC_MIRROR, &CUVSLib_PreviewDlg::OnClickedMirror)
END_MESSAGE_MAP()


// CUVSLib_PreviewDlg message handlers

BOOL CUVSLib_PreviewDlg::OnInitDialog()
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
	// enum video capture device
	uvs_dev_info_tX info[16];
	int num = _countof(info);
	CDevSDK::EnumDevice(uvs_dev_video_capture, info, num);
	CComboBox *pVideoIn = (CComboBox*)GetDlgItem(IDC_VIDEO_INPUT);
	for (int i=0; i<num; i++)
	{
		pVideoIn->AddString(info[i].szFriendlyDevName);
	}
	pVideoIn->SetCurSel(0);

	// enum audio capture device
	num = _countof(info);
	CDevSDK::EnumDevice(uvs_dev_audio_capture, info, num);
	CComboBox *pAudioIn = (CComboBox*)GetDlgItem(IDC_AUDIO_INPUT);
	for (int i=0; i<num; i++)
	{
		pAudioIn->AddString(info[i].szFriendlyDevName);
	}
	pAudioIn->SetCurSel(0);

	// enum audio renderer device
	num = _countof(info);
	CDevSDK::EnumDevice(uvs_dev_audio_renderer, info, num);
	CComboBox *pAudioRender = (CComboBox*)GetDlgItem(IDC_AUDIO_OUTPUT);
	for (int i=0; i<num; i++)
	{
		pAudioRender->AddString(info[i].szFriendlyDevName);
	}
	/* Use default audio render if not selected */

	((CButton*)GetDlgItem(IDC_DISP_D3D))->SetCheck(BST_CHECKED);

	uvs_video_effect_e effect[] = { uvs_video_brightness, uvs_video_contrast,
									uvs_video_saturation, uvs_video_gamma };
	int slider[] = { IDC_BRIGHTNESS, IDC_CONTRAST, IDC_SATURATION, IDC_GAMMA };
	for (int i=0; i<_countof(effect); i++)
	{
		m_map[slider[i]] = effect[i];
	}

	((CSliderCtrl*)GetDlgItem(IDC_VOLUME))->SetRange(0, 100, TRUE);
	((CSliderCtrl*)GetDlgItem(IDC_BALANCE))->SetRange(-100, 100, TRUE);

	m_pVideoWnd = GetDlgItem(IDC_VIDEO);
	DevStart();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUVSLib_PreviewDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUVSLib_PreviewDlg::OnPaint()
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
HCURSOR CUVSLib_PreviewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUVSLib_PreviewDlg::DevStart(void)
{	
	int nVideoIndex = ((CComboBox*)GetDlgItem(IDC_VIDEO_INPUT))->GetCurSel();
	m_Dev.DeviceOpen(nVideoIndex);
	if (m_Dev)
	{
		// set audio capture
		int nAudioIndex = ((CComboBox*)GetDlgItem(IDC_AUDIO_INPUT))->GetCurSel();
		if (nAudioIndex >= 0)
		{
			m_Dev.SetAudioDevice(uvs_dev_audio_capture, nAudioIndex);
		}

		// set audio renderer
		int nAudioRender = ((CComboBox*)GetDlgItem(IDC_AUDIO_OUTPUT))->GetCurSel();
		if (nAudioRender >= 0)
		{
			uvs_dev_info_tX info[32];
			int num = _countof(info);
			int r = CDevSDK::EnumDevice(uvs_dev_audio_renderer, info, num);
			if (r == UVS_OK && nAudioRender < num)
			{
				m_Dev.SetAudioDevice(uvs_dev_audio_renderer, info[nAudioRender]);
			}
		}

		m_Dev.DeviceStart();

		// set video renderer
		OnClickedDisp();

		for (auto it=std::begin(m_map); it!=std::end(m_map); it++)
		{
			int nMin, nMax, nStep, nVal;
			if (m_Dev.GetVideoEffectRange(it->second, nMin, nMax, nStep, nVal) == UVS_OK)
			{
				m_Dev.GetVideoEffect(it->second, nVal);

				CSliderCtrl *pSlider = (CSliderCtrl*)GetDlgItem(it->first);
				if (pSlider != NULL)
				{
					pSlider->SetRange(nMin, nMax, TRUE);
					pSlider->SetPos(nVal);
				}
			}
		}

		int nVolume = 0;
		m_Dev.GetAudioVolume(nVolume);
		((CSliderCtrl*)GetDlgItem(IDC_VOLUME))->SetPos(nVolume);

		int nBalance = 0;
		m_Dev.GetAudioBalance(nBalance);
		((CSliderCtrl*)GetDlgItem(IDC_BALANCE))->SetPos(nBalance);

		m_nAudioIndex = nAudioIndex;
		m_nVideoIndex = nVideoIndex;
		m_nAudioRender = nAudioRender;
	}
}


void CUVSLib_PreviewDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	m_Dev.DeviceClose();
}


void CUVSLib_PreviewDlg::OnSelchangeAudioInput()
{
	// TODO: Add your control notification handler code here
	int nIndex = ((CComboBox*)GetDlgItem(IDC_AUDIO_INPUT))->GetCurSel();
	if (nIndex != CB_ERR)
	{
		if (m_nAudioIndex == nIndex) return;
		DevStart();
	}
}


void CUVSLib_PreviewDlg::OnSelchangeVideoInput()
{
	// TODO: Add your control notification handler code here
	int nIndex = ((CComboBox*)GetDlgItem(IDC_VIDEO_INPUT))->GetCurSel();
	if (nIndex != CB_ERR)
	{
		if (m_nVideoIndex == nIndex) return;
		DevStart();
	}
}


void CUVSLib_PreviewDlg::OnClickedDisp()
{
	// TODO: Add your control notification handler code here
	if (m_bDispRect)
	{
		OnBnClickedDispRect();
	}

	if (m_bDigitalZoom)
	{
		OnBnClickedDigitalZoom();
	}

	BOOL bChecked = ((CButton*)GetDlgItem(IDC_DISP_D3D))->GetCheck() == BST_CHECKED;
	m_Dev.PreviewStart(m_pVideoWnd->GetSafeHwnd(), bChecked ? uvs_disp_type_d3d : uvs_disp_type_ddraw);
}


void CUVSLib_PreviewDlg::OnBnClickedFullScreen()
{
	// TODO: Add your control notification handler code here
	if (m_bDispRect)
	{
		OnBnClickedDispRect();
	}

	if (m_bDigitalZoom)
	{
		OnBnClickedDigitalZoom();
	}

	m_pVideoWnd->GetWindowRect(&m_VideoRect);
	m_pVideoWnd->GetParent()->ScreenToClient(&m_VideoRect);
	m_pParentWnd = m_pVideoWnd->SetParent(NULL);

	RECT rc = { 0, 0, ::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN) };
	m_pVideoWnd->MoveWindow(&rc);
	m_bFullScreen = TRUE;
}


BOOL CUVSLib_PreviewDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_bFullScreen)
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			if (pMsg->wParam == VK_ESCAPE)
			{ // Full Screen Restore
				m_pVideoWnd->SetParent(m_pParentWnd);
				m_pVideoWnd->MoveWindow(&m_VideoRect);
				m_bFullScreen = FALSE;
				return TRUE;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CUVSLib_PreviewDlg::OnBnClickedDigitalZoom()
{
	// TODO: Add your control notification handler code here
	if (m_bDigitalZoom)
	{
		m_Dev.PreviewSetRect(NULL, NULL);
		m_bDigitalZoom = FALSE;
	}
	else
	{
		// Zoom in 2X
		uvs_video_format_t videoFormat;
		if (m_Dev.GetVideoProperty(videoFormat) == UVS_OK)
		{
			RECT rc = { videoFormat.videoWidth / 4, videoFormat.videoHeight / 4, videoFormat.videoWidth * 3 / 4, videoFormat.videoHeight * 3 / 4};
			m_Dev.PreviewSetRect(NULL, &rc);
			m_bDigitalZoom = TRUE;
		}
	}
}


void CUVSLib_PreviewDlg::OnBnClickedDispRect()
{
	// TODO: Add your control notification handler code here
	if (m_bDispRect)
	{
		m_Dev.PreviewSetRect(NULL, NULL);
		m_bDispRect = FALSE;
	}
	else
	{
		// Zoom out 2X
		RECT rc0;
		m_pVideoWnd->GetClientRect(&rc0);
		int nWidth = rc0.right - rc0.left;
		int nHeight = rc0.bottom - rc0.top;

		RECT rc1 = { nWidth / 4, nHeight / 4, nWidth * 3 / 4, nHeight * 3 / 4};
		m_Dev.PreviewSetRect(&rc1, NULL, RGB(240, 240, 240));

		m_pVideoWnd->RedrawWindow(); // Video Window Update
		m_bDispRect = TRUE;
	}
}


void CUVSLib_PreviewDlg::OnBnClickedDispFreeze()
{
	// TODO: Add your control notification handler code here
	BOOL bFreeze;
	m_Dev.PreviewIsFreeze(bFreeze);
	m_Dev.PreviewFreeze(!bFreeze);
}


void CUVSLib_PreviewDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (nSBCode != SB_ENDSCROLL)
	{
		int nID = pScrollBar->GetDlgCtrlID();
		int nPos = ((CSliderCtrl*)pScrollBar)->GetPos();
		if (nID == IDC_VOLUME)
		{
			m_Dev.SetAudioVolume(nPos);
		}
		else if (nID == IDC_BALANCE)
		{
			m_Dev.SetAudioBalance(nPos);
		}
		else
		{
			auto it = m_map.find(nID);
			if (it != std::end(m_map))
			{
				m_Dev.SetVideoEffect(it->second, nPos);
			}
		}
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CUVSLib_PreviewDlg::OnCbnSelchangeAudioOutput()
{
	// TODO: Add your control notification handler code here
	int nIndex = ((CComboBox*)GetDlgItem(IDC_AUDIO_OUTPUT))->GetCurSel();
	if (nIndex != CB_ERR)
	{
		if (m_nAudioRender == nIndex) return;
		DevStart();
	}
}


void CUVSLib_PreviewDlg::OnBnClickedMute()
{
	// TODO: Add your control notification handler code here
	BOOL bMute = ((CButton*)GetDlgItem(IDC_MUTE))->GetCheck() == BST_CHECKED;
	m_Dev.SetAudioMute(bMute);
}


void CUVSLib_PreviewDlg::OnClickedFlip()
{
	// TODO: Add your control notification handler code here
	BOOL bHoriz = ((CButton*)GetDlgItem(IDC_MIRROR))->GetCheck() == BST_CHECKED;
	BOOL bVert = ((CButton*)GetDlgItem(IDC_FLIP))->GetCheck() == BST_CHECKED;
	m_Dev.SetVideoMirror(bHoriz, bVert);
}


void CUVSLib_PreviewDlg::OnClickedMirror()
{
	// TODO: Add your control notification handler code here
	OnClickedFlip();
}
