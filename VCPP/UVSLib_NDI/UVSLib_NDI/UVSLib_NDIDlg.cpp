
// UVSLib_NDIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UVSLib_NDI.h"
#include "UVSLib_NDIDlg.h"
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


// CUVSLib_NDIDlg dialog




CUVSLib_NDIDlg::CUVSLib_NDIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUVSLib_NDIDlg::IDD, pParent)
	, m_bNDIStart(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUVSLib_NDIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUVSLib_NDIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_NDI_CONTROL, &CUVSLib_NDIDlg::OnBnClickedNdiControl)
END_MESSAGE_MAP()


// CUVSLib_NDIDlg message handlers

BOOL CUVSLib_NDIDlg::OnInitDialog()
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

	GetDlgItem(IDC_NDI_AUDIO)->EnableWindow(count > 0);
	SetDlgItemText(IDC_SOURCE_NAME, _T("UVS Stream"));
	((CComboBox*)GetDlgItem(IDC_VIDEO_ROTATE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_VIDEO_SCALE))->SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUVSLib_NDIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUVSLib_NDIDlg::OnPaint()
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
HCURSOR CUVSLib_NDIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUVSLib_NDIDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	m_Dev.DeviceClose();
}


void CUVSLib_NDIDlg::OnBnClickedNdiControl()
{
	// TODO: Add your control notification handler code here
	static uvs_rotate_mode_e rotatemode[] = { uvs_rotate_none, uvs_rotate_90, uvs_rotate_180, uvs_rotate_270 };

	if (m_Dev)
	{
		do {
			if (m_bNDIStart)
			{
				m_Dev.NDIStop();
				m_Dev.NDIDestroy();
				m_bNDIStart = FALSE;
				break;
			}

			CString strSource;
			GetDlgItemText(IDC_SOURCE_NAME, strSource);
			if (strSource.IsEmpty()) break;

			CString strGroup;
			GetDlgItemText(IDC_GROUP_NAME, strGroup);

			// video rotate
			uvs_frame_convert_t convert = { uvs_frame_NONE };
			int nSel = ((CComboBox*)GetDlgItem(IDC_VIDEO_ROTATE))->GetCurSel();
			if (nSel == CB_ERR || nSel >= _countof(rotatemode)) break;
			convert.rotateMode = rotatemode[nSel];

			// video scale
			nSel = ((CComboBox*)GetDlgItem(IDC_VIDEO_SCALE))->GetCurSel();
			if (nSel == CB_ERR) break;
			if (nSel > 0)
			{
				convert.scaleWidth = 640;
				convert.scaleHeight = 480;
			}

			// video mirror
			convert.bFlip = ((CButton*)GetDlgItem(IDC_VIDEO_FLIP))->GetCheck() == BST_CHECKED;
			convert.bMirror = ((CButton*)GetDlgItem(IDC_VIDEO_MIRROR))->GetCheck() == BST_CHECKED;

			int r = m_Dev.NDICreate(strSource, strGroup);
			if (r != UVS_OK) break;

			if (convert.bFlip || convert.bMirror ||
				convert.rotateMode != uvs_rotate_none ||
				(convert.cropWidth > 0 && convert.cropHeight > 0) ||
				(convert.scaleWidth > 0 && convert.scaleHeight > 0))
			{
				r = m_Dev.NDIConfig(&convert);
				if (r != UVS_OK) break;
			}

			BOOL bAudio = ((CButton*)GetDlgItem(IDC_NDI_AUDIO))->GetCheck() == BST_CHECKED;
			r = m_Dev.NDIStart(bAudio);
			if (r != UVS_OK) break;

			m_bNDIStart = TRUE;
		} while (0);

		SetDlgItemText(IDC_NDI_CONTROL, m_bNDIStart ? _T("NDI Stream Stop") : _T("NDI Stream Start"));
	}
}
