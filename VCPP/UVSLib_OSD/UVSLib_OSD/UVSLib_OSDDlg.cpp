
// UVSLib_OSDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UVSLib_OSD.h"
#include "UVSLib_OSDDlg.h"
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


// CUVSLib_OSDDlg dialog

enum {
	TIME_OSD_INDEX = uvs_time_osd_index_preview_only,//uvs_time_osd_index_preview_enc, /* uvs_time_osd_index_preview_only, */
	BASE_OSD_INDEX = uvs_osd_index_preview_only,//uvs_osd_index_preview_enc, /* uvs_osd_index_preview_only, */
	TEXT_OSD_INDEX,
	IMAGE_OSD_INDEX,
	RECT_OSD_INDEX,
	ELLIPSE_OSD_INDEX,
	LINE_0_OSD_INDEX,
	LINE_1_OSD_INDEX,
	LINE_2_OSD_INDEX,
	LINE_3_OSD_INDEX
};

enum {
	OSD_CONTROL_NONE,
	OSD_CONTROL_BLINK,
	OSD_CONTROL_MOVE,
	OSD_CONTROL_SCROLL_0,
	OSD_CONTROL_SCROLL_1,
	OSD_CONTROL_RECT,
	OSD_CONTROL_FADE,
};


CUVSLib_OSDDlg::CUVSLib_OSDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUVSLib_OSDDlg::IDD, pParent)
	, m_Dev(0)
	, m_nVideoWidth(0)
	, m_nVideoHeight(0)
	, m_nOSDIndex(0)
	, m_nOSDControl(OSD_CONTROL_NONE)
{
	memset(&m_OSDFont, 0, sizeof(uvs_font_info_tX));
	m_OSDFont.fontPointSize = 32;
	m_OSDFont.fontStyle = uvs_font_style_cleartype;
	m_OSDFont.textColor = RGB(0, 0, 255);
	m_OSDFont.textBkColor = RGB(255, 255, 255);
	m_OSDFont.textOpacity = 255;
	m_OSDFont.textBkOpacity = 128;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUVSLib_OSDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUVSLib_OSDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TIME_OSD, &CUVSLib_OSDDlg::OnClickedTimeOsd)
	ON_CBN_SELCHANGE(IDC_TIME_MODE, &CUVSLib_OSDDlg::OnSelchangeTimeMode)
	ON_CBN_SELCHANGE(IDC_WEEK_MODE, &CUVSLib_OSDDlg::OnSelchangeWeekMode)
	ON_CBN_SELCHANGE(IDC_DATE_MODE, &CUVSLib_OSDDlg::OnSelchangeDateMode)
	ON_BN_CLICKED(IDC_OSD_FONT, &CUVSLib_OSDDlg::OnBnClickedOsdFont)
	ON_BN_CLICKED(IDC_TEXT_OSD, &CUVSLib_OSDDlg::OnClickedTextOsd)
	ON_BN_CLICKED(IDC_IMG_OSD, &CUVSLib_OSDDlg::OnClickedImgOsd)
	ON_BN_CLICKED(IDC_IMAGE_BROWSE, &CUVSLib_OSDDlg::OnBnClickedImageBrowse)
	ON_BN_CLICKED(IDC_RECT_OSD, &CUVSLib_OSDDlg::OnClickedRectOsd)
	ON_CBN_SELCHANGE(IDC_RECT_STYLE, &CUVSLib_OSDDlg::OnSelchangeRectStyle)
	ON_BN_CLICKED(IDC_ELLIPSE_OSD, &CUVSLib_OSDDlg::OnClickedEllipseOsd)
	ON_CBN_SELCHANGE(IDC_ELLIPSE_STYLE, &CUVSLib_OSDDlg::OnSelchangeEllipseStyle)
	ON_BN_CLICKED(IDC_LINE_OSD, &CUVSLib_OSDDlg::OnClickedLineOsd)
	ON_CBN_SELCHANGE(IDC_OSD_CONTROL, &CUVSLib_OSDDlg::OnSelchangeOsdControl)
	ON_CBN_SELCHANGE(IDC_VIDEO_OSD, &CUVSLib_OSDDlg::OnSelchangeVideoOsd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MULTILINE, &CUVSLib_OSDDlg::OnBnClickedMultiline)
END_MESSAGE_MAP()


// CUVSLib_OSDDlg message handlers

BOOL CUVSLib_OSDDlg::OnInitDialog()
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
	if (m_Dev)
	{
		m_Dev.DeviceStart();
		m_Dev.PreviewStart(GetDlgItem(IDC_VIDEO)->GetSafeHwnd());

		uvs_video_format_t videoFormat;
		if (m_Dev.GetVideoProperty(videoFormat) == UVS_OK)
		{
			m_nVideoWidth = videoFormat.videoWidth;
			m_nVideoHeight = videoFormat.videoHeight;
		}
	}

	((CComboBox*)GetDlgItem(IDC_DATE_MODE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_WEEK_MODE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_TIME_MODE))->SetCurSel(1);

	SetDlgItemText(IDC_TEXT, _T("UVS Text Sample"));

	((CComboBox*)GetDlgItem(IDC_RECT_STYLE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_ELLIPSE_STYLE))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_VIDEO_OSD))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_OSD_CONTROL))->SetCurSel(0);

	SetTimer(0, 100, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUVSLib_OSDDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUVSLib_OSDDlg::OnPaint()
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
HCURSOR CUVSLib_OSDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUVSLib_OSDDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(0);
	m_Dev.DeviceClose();
}

void CUVSLib_OSDDlg::OnClickedTimeOsd()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		BOOL bEnable = ((CButton*)GetDlgItem(IDC_TIME_OSD))->GetCheck() == BST_CHECKED;
		if (!bEnable)
		{
			DisableOSD(TIME_OSD_INDEX);
			return;
		}

		/* %M month, %D month of day, %H 24 hours, %h 12 hours, %m minute, %s second, %Y year,
		 * %t AM/PM, %N month name, %n month short name, %W week name, %w week short name, %% % */
		CString str;
		int nSel = ((CComboBox*)GetDlgItem(IDC_DATE_MODE))->GetCurSel();
		switch (nSel) {
		case 0:
			str += _T("%Y-%M-%D");
			break;

		case 1:
			str += _T("%M-%D-%Y");
			break;

		case 2:
			str += _T("%D-%M-%Y");
			break;

		case 3:
			str += _T("%N %D %Y");
			break;

		case 4:
			str += _T("%n %D %Y");
			break;

		default:break;
		}

		nSel = ((CComboBox*)GetDlgItem(IDC_WEEK_MODE))->GetCurSel();
		if (nSel == 1)
		{
			str += _T(" %W");
		}
		else if (nSel == 2)
		{
			str += _T(" %w");
		}

		nSel = ((CComboBox*)GetDlgItem(IDC_TIME_MODE))->GetCurSel();
		switch (nSel) {
		case 1:
			str += _T(" %H:%m:%s");
			break;

		case 2:
			str += _T(" %h:%m:%s");
			break;

		case 3:
			str += _T(" %h:%m:%s %t");
			break;

		default:break;
		}

		m_Dev.SetTimeOSD(TIME_OSD_INDEX, 20, 20, str, m_OSDFont);
	}
}


void CUVSLib_OSDDlg::OnSelchangeTimeMode()
{
	// TODO: Add your control notification handler code here
	OnClickedTimeOsd();
}


void CUVSLib_OSDDlg::OnSelchangeWeekMode()
{
	// TODO: Add your control notification handler code here
	OnClickedTimeOsd();
}


void CUVSLib_OSDDlg::OnSelchangeDateMode()
{
	// TODO: Add your control notification handler code here
	OnClickedTimeOsd();
}


void CUVSLib_OSDDlg::OnBnClickedOsdFont()
{
	// TODO: Add your control notification handler code here
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		_tcscpy_s(m_OSDFont.szFontName, _countof(m_OSDFont.szFontName), dlg.GetFaceName());

		m_OSDFont.fontPointSize = dlg.GetSize() / 10;
		m_OSDFont.textColor = dlg.GetColor();

		int nStyle = uvs_font_style_regular;
		if (dlg.IsBold())
		{
			nStyle |= uvs_font_style_bold;
		}
		else
		{
			nStyle &= ~uvs_font_style_bold;
		}

		if (dlg.IsItalic())
		{
			nStyle |= uvs_font_style_italic;
		}
		else
		{
			nStyle &= ~uvs_font_style_italic;
		}

		if (dlg.IsUnderline())
		{
			nStyle |= uvs_font_style_underline;
		}
		else
		{
			nStyle &= ~uvs_font_style_underline;
		}

		if (dlg.IsStrikeOut())
		{
			nStyle |= uvs_font_style_strikeout;
		}
		else
		{
			nStyle &= ~uvs_font_style_strikeout;
		}

		m_OSDFont.fontStyle = static_cast< uvs_font_style_e >(nStyle);

		OnClickedTimeOsd();
		OnClickedTextOsd();
	}
}


void CUVSLib_OSDDlg::OnClickedTextOsd()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		BOOL bEnable = ((CButton*)GetDlgItem(IDC_TEXT_OSD))->GetCheck() == BST_CHECKED;
		if (!bEnable)
		{
			DisableOSD(TEXT_OSD_INDEX);
			return;
		}

		CString str;
		GetDlgItemText(IDC_TEXT, str);
		if (!str.IsEmpty())
		{
			BOOL bMultiLine = ((CButton*)GetDlgItem(IDC_MULTILINE))->GetCheck() == BST_CHECKED;
			if (bMultiLine)
			{
				m_OSDFont.stringFormat = uvs_string_rect_multiple_lines;
				m_Dev.SetTextOSD(TEXT_OSD_INDEX, 20, 100, 200, 100, str, m_OSDFont);
			}
			else
			{
				m_OSDFont.stringFormat = uvs_string_format_regular;
				m_Dev.SetTextOSD(TEXT_OSD_INDEX, 20, 100, 0, 0, str, m_OSDFont);
			}
		}
	}
}


void CUVSLib_OSDDlg::OnClickedImgOsd()
{
	// TODO: Add your control notification handler code here
	if (m_Dev)
	{
		BOOL bEnable = ((CButton*)GetDlgItem(IDC_IMG_OSD))->GetCheck() == BST_CHECKED;
		if (!bEnable)
		{
			DisableOSD(IMAGE_OSD_INDEX);
			return;
		}

		CString str;
		GetDlgItemText(IDC_IMAGE, str);
		if (!str.IsEmpty())
		{
			m_Dev.SetImageOSD(IMAGE_OSD_INDEX, 20, 160, 0, 0, 192, str); /* width & height is zero, original size */
		}
	}
}


void CUVSLib_OSDDlg::OnBnClickedImageBrowse()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Jpeg Files;Png Files;Bitmap Files|*.jpg;*.png;*.bmp|All Files|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_IMAGE, dlg.GetPathName());
		OnClickedImgOsd();
	}
}


void CUVSLib_OSDDlg::DisableOSD(int nIndex)
{
	m_Dev.VideoOSDControl(nIndex, uvs_osd_delete);

	/* OSD disable, not delete */
	//int nEnable = 0; m_Dev.VideoOSDControl(nIndex, uvs_osd_enable, &nEnable);
}


void CUVSLib_OSDDlg::SetRectEllipseOSD(int nIndex, int nCheckID, int nStyleID)
{
	if (m_Dev)
	{
		BOOL bEnable = ((CButton*)GetDlgItem(nCheckID))->GetCheck() == BST_CHECKED;
		if (!bEnable)
		{
			DisableOSD(nIndex);
			return;
		}

		uvs_style_info_t info = { 4, uvs_dash_style_solid, RGB(255, 0, 0), RGB(255, 255, 255), 255, 128 };
		int nSel = ((CComboBox*)GetDlgItem(nStyleID))->GetCurSel();
		switch (nSel) {
		case 0:
			info.dashStyle = uvs_dash_style_solid;
			break;

		case 1:
			info.dashStyle = uvs_dash_style_dash;
			break;

		case 2:
			info.dashStyle = uvs_dash_style_dot;
			break;

		case 3:
			info.dashStyle = uvs_dash_style_dash_dot;
			break;

		default:break;
		}

		if (nIndex == RECT_OSD_INDEX)
		{
			m_Dev.SetRectOSD(RECT_OSD_INDEX, 20, 200, 200, 200, info);
		}
		else
		{
			m_Dev.SetEllipseOSD(ELLIPSE_OSD_INDEX, 300, 200, 200, 200, info);
		}
	}
}


void CUVSLib_OSDDlg::OnClickedRectOsd()
{
	// TODO: Add your control notification handler code here
	SetRectEllipseOSD(RECT_OSD_INDEX, IDC_RECT_OSD, IDC_RECT_STYLE);
}


void CUVSLib_OSDDlg::OnSelchangeRectStyle()
{
	// TODO: Add your control notification handler code here
	OnClickedRectOsd();
}


void CUVSLib_OSDDlg::OnClickedEllipseOsd()
{
	// TODO: Add your control notification handler code here
	SetRectEllipseOSD(ELLIPSE_OSD_INDEX, IDC_ELLIPSE_OSD, IDC_ELLIPSE_STYLE);
}


void CUVSLib_OSDDlg::OnSelchangeEllipseStyle()
{
	// TODO: Add your control notification handler code here
	OnClickedEllipseOsd();
}


void CUVSLib_OSDDlg::OnClickedLineOsd()
{
	// TODO: Add your control notification handler code here
	static const int OSD_LINE_SIZE = 4;
	static const int OSD_RECT_LEFT = 20;
	static const int OSD_RECT_TOP = 420;
	static const int OSD_RECT_WIDTH = 800;
	static const int OSD_RECT_HEIGHT = 400;

	if (m_Dev)
	{
		BOOL bEnable = ((CButton*)GetDlgItem(IDC_LINE_OSD))->GetCheck() == BST_CHECKED;
		do {
			if (bEnable)
			{
				int x, y;
				int r = m_Dev.VideoOSDControl(LINE_0_OSD_INDEX, uvs_osd_get_position, &x, &y);
				if (r != UVS_OK)
				{ // Line OSD create
					uvs_line_info_t info = { OSD_LINE_SIZE, uvs_dash_style_solid, RGB(0, 255, 255), 255 };

					// Higher performance than CDevSDK::SetRectOSD when rectangle no fill color
					int x0, y0, x1, y1;
					x0 = OSD_RECT_LEFT;
					x1 = OSD_RECT_LEFT + OSD_RECT_WIDTH;
					y0 = y1 = OSD_RECT_TOP;
					m_Dev.SetLineOSD(LINE_0_OSD_INDEX, x0, y0, x1, y1, info);

					y0 = y1 = OSD_RECT_TOP + OSD_RECT_HEIGHT - OSD_LINE_SIZE;
					m_Dev.SetLineOSD(LINE_1_OSD_INDEX, x0, y0, x1, y1, info);

					x0 = x1 = OSD_RECT_LEFT;
					y0 = OSD_RECT_TOP + OSD_LINE_SIZE;
					y1 = OSD_RECT_TOP + OSD_RECT_HEIGHT - OSD_LINE_SIZE;
					m_Dev.SetLineOSD(LINE_2_OSD_INDEX, x0, y0, x1, y1, info);

					x0 = x1 = OSD_RECT_LEFT + OSD_RECT_WIDTH - OSD_LINE_SIZE;
					m_Dev.SetLineOSD(LINE_3_OSD_INDEX, x0, y0, x1, y1, info);
					break;
				}
			}

			// Line OSD enable/disable
			int nEnable = bEnable ? 1 : 0;
			m_Dev.VideoOSDControl(LINE_0_OSD_INDEX, uvs_osd_enable, &nEnable);
			m_Dev.VideoOSDControl(LINE_1_OSD_INDEX, uvs_osd_enable, &nEnable);
			m_Dev.VideoOSDControl(LINE_2_OSD_INDEX, uvs_osd_enable, &nEnable);
			m_Dev.VideoOSDControl(LINE_3_OSD_INDEX, uvs_osd_enable, &nEnable);
		} while (0);
	}
}


void CUVSLib_OSDDlg::VideoOSDControl(void)
{
	if (m_nOSDControl == OSD_CONTROL_BLINK)
	{
		// clear show / hide period
		int nMS = 0;
		m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_set_blink, &nMS, &nMS);
	}
	else if (m_nOSDControl == OSD_CONTROL_SCROLL_0 || m_nOSDControl == OSD_CONTROL_SCROLL_1 || m_nOSDControl == OSD_CONTROL_RECT)
	{
		// restore clip
		int nSize = 0;
		m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_set_clip_size, &nSize, &nSize);
		if (m_nOSDControl == OSD_CONTROL_SCROLL_1)
		{
			DisableOSD(BASE_OSD_INDEX);
		}
	}

	int nIndex[] = { TIME_OSD_INDEX, TEXT_OSD_INDEX, IMAGE_OSD_INDEX, RECT_OSD_INDEX, ELLIPSE_OSD_INDEX };
	int nSel = ((CComboBox*)GetDlgItem(IDC_VIDEO_OSD))->GetCurSel();
	if (nSel >= 0 && nSel < _countof(nIndex))
	{
		m_nOSDIndex = nIndex[nSel];
	}
	
	m_nOSDControl = ((CComboBox*)GetDlgItem(IDC_OSD_CONTROL))->GetCurSel();
	if (m_nOSDControl == OSD_CONTROL_BLINK)
	{ // Blink
		int nShowMS = 800;
		int nHideMS = 600;
		m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_set_blink, &nShowMS, &nHideMS);
	}
	else if (m_nOSDControl == OSD_CONTROL_SCROLL_0 || m_nOSDControl == OSD_CONTROL_SCROLL_1 || m_nOSDControl == OSD_CONTROL_RECT)
	{
		int w, h;
		int r = m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_get_size, &w, &h);
		if (r == UVS_OK)
		{
			int x = m_nVideoWidth > w ? (m_nVideoWidth - w) / 2 : 0;
			// X & Width must be even
			x &= ~1;
			w = (w + 1) & ~1;
			m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_set_position, &x);
			m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_set_clip_position, &x);
			m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_set_clip_size, &w, &h);

			if (m_nOSDControl == OSD_CONTROL_SCROLL_1)
			{
				int y;
				r = m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_get_clip_position, NULL, &y);
				if (r == UVS_OK)
				{
					// create background
					uvs_style_info_t info = { 0, uvs_dash_style_solid, RGB(0, 0, 0), RGB(0, 255, 0), 128, 128 };
					m_Dev.SetRectOSD(BASE_OSD_INDEX, x, y, w, h, info);
				}

				int nOpacity = 0;
				m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_set_opacity, NULL, &nOpacity);
			}
		}
	}
}


void CUVSLib_OSDDlg::OnSelchangeOsdControl()
{
	// TODO: Add your control notification handler code here
	VideoOSDControl();
}


void CUVSLib_OSDDlg::OnSelchangeVideoOsd()
{
	// TODO: Add your control notification handler code here
	VideoOSDControl();
}


void CUVSLib_OSDDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (m_nOSDControl == OSD_CONTROL_MOVE || m_nOSDControl == OSD_CONTROL_SCROLL_0 || m_nOSDControl == OSD_CONTROL_SCROLL_1)
	{
		int x, w;
		int r = m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_get_position, &x);
		if (r == UVS_OK)
		{
			r = m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_get_size, &w);
			if (r == UVS_OK)
			{
				int m = 0;
				if (m_nOSDControl == OSD_CONTROL_SCROLL_0 || m_nOSDControl == OSD_CONTROL_SCROLL_1)
				{
					m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_get_clip_position, &m);
				}
				
				if (x > m - w)
				{
					// move left
					x -= 8;
				}
				else
				{
					// right side beginning
					x = m_nOSDControl == OSD_CONTROL_MOVE ? m_nVideoWidth : m + w;
				}

				// move to new position
				m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_set_position, &x);
			}
		}
	}
	else if (m_nOSDControl == OSD_CONTROL_RECT)
	{
		int w, h;
		int r = m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_get_clip_size, &w, &h);
		if (r == UVS_OK)
		{
			if (w > 0 && h > 0)
			{
				// reduce clip size
				w = w * 95 / 100;
				h = h * 95 / 100;
			}
			else
			{
				m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_get_size, &w, &h);
			}

			w = (w + 1) & ~1; // Width even
			m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_set_clip_size, &w, &h);
		}
	}
	else if (m_nOSDControl == OSD_CONTROL_FADE)
	{
		int frontOpacity, bkOpacity;
		int r = m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_get_opacity, &frontOpacity, &bkOpacity);
		if (frontOpacity > 25)
		{
			frontOpacity = frontOpacity * 250 / 255;
			bkOpacity = bkOpacity * 250 / 255;
		}
		else
		{
			frontOpacity = 255;
			bkOpacity = 128;
		}

		m_Dev.VideoOSDControl(m_nOSDIndex, uvs_osd_set_opacity, &frontOpacity, &bkOpacity);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CUVSLib_OSDDlg::OnBnClickedMultiline()
{
	// TODO: Add your control notification handler code here
	OnClickedTextOsd();
}
