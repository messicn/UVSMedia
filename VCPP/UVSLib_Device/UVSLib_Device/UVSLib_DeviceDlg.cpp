
// UVSLib_DeviceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UVSLib_Device.h"
#include "UVSLib_DeviceDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_DEVCLOSED (WM_USER + 2020)
#define WM_DEVCHANGED (WM_USER + 2021)


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


// CUVSLib_DeviceDlg dialog




CUVSLib_DeviceDlg::CUVSLib_DeviceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUVSLib_DeviceDlg::IDD, pParent)
	, m_Dev(0)
	, m_BkColor(RGB(0, 0, 0))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUVSLib_DeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CALLBACK CUVSLib_DeviceDlg::UVSDevCallback(uvs_dev_notify_e notify, const uvs_dev_info_tX *info, uvsobj_handle obj, void *pUserData)
{
	CUVSLib_DeviceDlg *pDlg = static_cast< CUVSLib_DeviceDlg* >(pUserData);
	if (pDlg)
	{
		uvs_dev_info_tX *param = new uvs_dev_info_tX;
		memcpy(param, info, sizeof(uvs_dev_info_tX));
		pDlg->PostMessage(notify == uvs_dev_changed ? WM_DEVCHANGED : WM_DEVCLOSED, (WPARAM)param, (LPARAM)(obj));
	}
}

void CUVSLib_DeviceDlg::DevStart(void)
{
	if (m_Dev)
	{
		m_Dev.DeviceStart();
		m_Dev.PreviewStart(GetDlgItem(IDC_VIDEO)->GetSafeHwnd());
	}
}

BEGIN_MESSAGE_MAP(CUVSLib_DeviceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, &CUVSLib_DeviceDlg::OnBnClickedBrowse)
	ON_BN_CLICKED(IDC_COLOR, &CUVSLib_DeviceDlg::OnBnClickedColor)
	ON_BN_CLICKED(IDOK, &CUVSLib_DeviceDlg::OnBnClickedOk)
	ON_MESSAGE(WM_DEVCHANGED, &CUVSLib_DeviceDlg::OnDevchanged)
	ON_MESSAGE(WM_DEVCLOSED, &CUVSLib_DeviceDlg::OnDevclosed)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CUVSLib_DeviceDlg message handlers

BOOL CUVSLib_DeviceDlg::OnInitDialog()
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
	((CComboBox*)GetDlgItem(IDC_MODE))->SetCurSel(0);

	CDevSDK::SetDeviceCallback(UVSDevCallback, this);

	DevStart();
	SetTimer(0, 200, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUVSLib_DeviceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUVSLib_DeviceDlg::OnPaint()
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
HCURSOR CUVSLib_DeviceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUVSLib_DeviceDlg::OnBnClickedBrowse()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Jpeg Files;Png Files;Bitmap Files|*.jpg;*.png;*.bmp|All Files|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_IMAGE, dlg.GetPathName());
	}
}


void CUVSLib_DeviceDlg::OnBnClickedColor()
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg(m_BkColor, CC_FULLOPEN, this);
	if (dlg.DoModal() == IDOK)
	{
		m_BkColor = dlg.GetColor();
	}
}


void CUVSLib_DeviceDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_IMAGE, str);

	/* Valid dev reopen */
	if (str.IsEmpty())
	{
		CDevSDK::SetNosignalImage(NULL); /* No signal image disabled */
	}
	else
	{
		uvs_draw_mode_e mode = ((CComboBox*)GetDlgItem(IDC_MODE))->GetCurSel() == 0 ? uvs_draw_stretch : uvs_draw_center;
		CDevSDK::SetNosignalImage(str, mode, m_BkColor);
	}
}


afx_msg LRESULT CUVSLib_DeviceDlg::OnDevchanged(WPARAM wParam, LPARAM lParam)
{
	uvs_dev_info_tX *info = reinterpret_cast< uvs_dev_info_tX* >(wParam);
	if (info)
	{
		if (!m_Dev)
		{
			m_Dev.DeviceOpen(*info);
			DevStart();
		}
		delete info;
	}

	return 0;
}


afx_msg LRESULT CUVSLib_DeviceDlg::OnDevclosed(WPARAM wParam, LPARAM lParam)
{
	uvs_dev_info_tX *info = reinterpret_cast< uvs_dev_info_tX* >(wParam);

	if (m_Dev)
	{
		if (m_Dev.m_DevObj == (uvsobj_handle)lParam)
		{
			m_Dev.DeviceClose();
			GetDlgItem(IDC_VIDEO)->InvalidateRect(NULL);
		}
	}

	if (info) delete info;

	return 0;
}


void CUVSLib_DeviceDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	if (m_Dev)
	{
		BOOL bSignal, bMode;
		int r = m_Dev.GetVideoStatus(bSignal, bMode);
		if (r == UVS_OK)
		{
			str.Format(_T("%s(%s)"), bSignal ? _T("Signal") : _T("No Signal"), bMode ? _T("USB3") : _T("USB2"));
		}
	}

	SetDlgItemText(IDC_STATUS, str);

	CDialogEx::OnTimer(nIDEvent);
}


void CUVSLib_DeviceDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(0);

	/* Event disabled */
	CDevSDK::SetDeviceCallback(NULL, NULL);

	m_Dev.DeviceClose();
}
