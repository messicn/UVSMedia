
// UVSLib_MP4FileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UVSLib_MP4File.h"
#include "UVSLib_MP4FileDlg.h"
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


// CUVSLib_MP4FileDlg dialog




CUVSLib_MP4FileDlg::CUVSLib_MP4FileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUVSLib_MP4FileDlg::IDD, pParent)
	, m_bRepair(FALSE)
	, m_bMerge(FALSE)
	, m_bCut(FALSE)
	, m_bTitle(FALSE)
{
	memset(&m_OSDFont, 0, sizeof(uvs_font_info_tX));
	m_OSDFont.fontPointSize = 32;
	m_OSDFont.fontStyle = uvs_font_style_regular;
	m_OSDFont.stringFormat = static_cast< uvs_string_format_e >(uvs_string_rect_multiple_lines | uvs_string_align_style_center | uvs_string_line_align_style_center);
	m_OSDFont.textColor = RGB(0, 0, 255);
	m_OSDFont.textBkColor = RGB(255, 255, 255);
	m_OSDFont.textOpacity = 255;
	m_OSDFont.textBkOpacity = 128;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUVSLib_MP4FileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MP4LIST, m_MP4List);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
}

BEGIN_MESSAGE_MAP(CUVSLib_MP4FileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, &CUVSLib_MP4FileDlg::OnBnClickedBrowse)
	ON_EN_CHANGE(IDC_DIR, &CUVSLib_MP4FileDlg::OnEnChangeDir)
	ON_BN_CLICKED(IDC_REPAIR, &CUVSLib_MP4FileDlg::OnBnClickedRepair)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MERGE, &CUVSLib_MP4FileDlg::OnBnClickedMerge)
	ON_BN_CLICKED(IDC_CUT, &CUVSLib_MP4FileDlg::OnBnClickedCut)
	ON_NOTIFY(NM_CLICK, IDC_MP4LIST, &CUVSLib_MP4FileDlg::OnNMClickMp4list)
	ON_BN_CLICKED(IDC_LOGO, &CUVSLib_MP4FileDlg::OnBnClickedLogo)
	ON_BN_CLICKED(IDC_FONT, &CUVSLib_MP4FileDlg::OnBnClickedFont)
	ON_BN_CLICKED(IDC_BROWSEIMG, &CUVSLib_MP4FileDlg::OnBnClickedBrowseimg)
	ON_BN_CLICKED(IDC_SAVE, &CUVSLib_MP4FileDlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CUVSLib_MP4FileDlg message handlers

BOOL CUVSLib_MP4FileDlg::OnInitDialog()
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
	m_MP4List.InsertColumn(0, _T("MP4 File"), LVCFMT_LEFT, 350);
	m_MP4List.InsertColumn(1, _T("Status"), LVCFMT_LEFT, 300);
	m_MP4List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_Progress.SetRange(0, 100);

	GetDlgItem(IDC_REPAIR)->EnableWindow(FALSE);
	SetDlgItemInt(IDC_START, 0);
	SetDlgItemInt(IDC_END, -1);
	SetDlgItemInt(IDC_ADD, 0);
	SetDlgItemInt(IDC_DISP, 3000);
	SetDlgItemText(IDC_TEXT, _T("Title"));

	SetTimer(0, 100, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUVSLib_MP4FileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUVSLib_MP4FileDlg::OnPaint()
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
HCURSOR CUVSLib_MP4FileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUVSLib_MP4FileDlg::OnBnClickedBrowse()
{
	// TODO: Add your control notification handler code here
	LPMALLOC lpMalloc;
	if (::SHGetMalloc(&lpMalloc) != NOERROR) 
		return;

	TCHAR szDisplayName[_MAX_PATH];
	TCHAR szBuffer[_MAX_PATH];
	BROWSEINFO browseInfo;
	browseInfo.hwndOwner = GetSafeHwnd();
	browseInfo.pidlRoot = NULL;
	browseInfo.pszDisplayName = szDisplayName;
	browseInfo.lpszTitle = _T("Choose MP4 File Folder");
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
				SetDlgItemText(IDC_DIR, szBuffer);
			}
		}
	}

	if (lpItemIDList)
	{
		lpMalloc->Free(lpItemIDList);
	}

	lpMalloc->Release();
}


void CUVSLib_MP4FileDlg::SetFilePath(void)
{
	m_MP4List.DeleteAllItems();

	CString str;
	GetDlgItemText(IDC_DIR, str);
	if (!str.IsEmpty())
	{
		PathAppend(str.GetBuffer(MAX_PATH), _T("*.mp4"));
		str.ReleaseBuffer();

		int r, index;
		uvs_mp4_file_status_t fileStatus;

		CFileFind fileFind;
		BOOL bSuccess = fileFind.FindFile(str);
		while (bSuccess)
		{
			bSuccess = fileFind.FindNextFile();
			str = fileFind.GetFilePath();
			index = m_MP4List.InsertItem(m_MP4List.GetItemCount(), str);
			r = uvs_mp4_file_get_status(CStringA(str), &fileStatus);
			if (r == UVS_OK)
			{
				CString s;
				switch (fileStatus.audioCodec) {
				case uvs_audio_codec_MP3:
					s = _T("MP3/");
					break;
				case uvs_audio_codec_AAC:
					s = _T("AAC/");
					break;
				case uvs_audio_codec_none:
					s = _T("NONE/");
					break;
				}

				switch (fileStatus.videoCodec) {
				case uvs_video_codec_hw_h264:
				case uvs_video_codec_intel_h264:
				case uvs_video_codec_nvidia_h264:
				case uvs_video_codec_sw_h264:
				case uvs_video_codec_sw_x264:
					s += _T("H.264(AVC)");
					break;

				case uvs_video_codec_hw_h265:
				case uvs_video_codec_intel_h265:
				case uvs_video_codec_nvidia_h265:
					s += _T("H.265(HEVC)");
					break;
				}

				str.Format(_T("%s %d x %d %dms %.2ffps"),
						s, fileStatus.videoWidth, fileStatus.videoHeight, fileStatus.videoDuration, fileStatus.videoFrameRate);
			}
			else
			{
				str.Format(_T("Get status failed %d"), r);
			}

			m_MP4List.SetItemText(index, 1, str);
			m_MP4List.SetItemData(index, r);
		}
	}
}


void CUVSLib_MP4FileDlg::OnEnChangeDir()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	SetFilePath();
}


void CUVSLib_MP4FileDlg::OnBnClickedRepair()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_MP4List.GetFirstSelectedItemPosition();
	if (pos)
	{
		CFileDialog dlg(FALSE, _T(".mp4"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("MP4 Files|*.mp4||"));
		if (dlg.DoModal() == IDOK)
		{
			CString inputFile(m_MP4List.GetItemText(m_MP4List.GetNextSelectedItem(pos), 0));
			if (CDevSDK::MP4FileRepair(inputFile, dlg.GetPathName()) == 0)
			{
				EnableWindow(FALSE);
				m_Progress.SetPos(0);
				m_bRepair = TRUE;
			}
		}
	}
}


void CUVSLib_MP4FileDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(0);
}


void CUVSLib_MP4FileDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	int progress = 0;
	CString str;
	if (m_bRepair)
	{
		CDevSDK::MP4FileGetRepairProgress(progress);
	}
	else if (m_bMerge)
	{
		CDevSDK::MP4FileGetMergeProgress(progress);
	}
	else if (m_bCut)
	{
		CDevSDK::MP4FileGetCutProgress(progress);
	}
	else if (m_bTitle)
	{
		CDevSDK::MP4FileGetTitleProgress(progress);
	}

	if (m_bRepair || m_bMerge || m_bCut || m_bTitle)
	{
		if (progress >= 0)
		{
			m_Progress.SetPos(progress);
		}

		if (progress == -1 || progress == 100)
		{
			if (m_bRepair) m_bRepair = FALSE;
			if (m_bMerge) m_bMerge = FALSE;
			if (m_bCut) m_bCut = FALSE;
			if (m_bTitle) m_bTitle = FALSE;

			EnableWindow(TRUE);
			MessageBox(progress == 100 ? _T("Operator Succeed!") : _T("Operator Failed!"));
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CUVSLib_MP4FileDlg::OnBnClickedMerge()
{
#define MAX_FILE_NUM 64
	// TODO: Add your control notification handler code here
	POSITION pos = m_MP4List.GetFirstSelectedItemPosition();
	CStringArray fileArray;
	while (pos)
	{	
		fileArray.Add(m_MP4List.GetItemText(m_MP4List.GetNextSelectedItem(pos), 0));
	}

	if (fileArray.GetCount() > 1)
	{
		CFileDialog dlg(FALSE, _T(".mp4"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("MP4 Files|*.mp4||"));
		if (dlg.DoModal() == IDOK)
		{
			LPCTSTR inputFile[MAX_FILE_NUM];
			for (int i=0; i<fileArray.GetCount(); i++)
			{
				inputFile[i] = fileArray[i];
			}

			if (CDevSDK::MP4FileMerge(inputFile, fileArray.GetCount(), dlg.GetPathName()) == UVS_OK)
			{
				EnableWindow(FALSE);
				m_Progress.SetPos(0);
				m_bMerge = TRUE;
			}
		}
	}
}


void CUVSLib_MP4FileDlg::OnBnClickedCut()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_MP4List.GetFirstSelectedItemPosition();
	if (pos)
	{
		BOOL bResult;
		int nBegin = GetDlgItemInt(IDC_START, &bResult);
		if (bResult)
		{
			int nEnd = GetDlgItemInt(IDC_END, &bResult);
			if (bResult)
			{
				CFileDialog dlg(FALSE, _T(".mp4"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("MP4 Files|*.mp4||"));
				if (dlg.DoModal() == IDOK)
				{
					CString inputFile(m_MP4List.GetItemText(m_MP4List.GetNextSelectedItem(pos), 0));
					if (CDevSDK::MP4FileCut(inputFile, nBegin, nEnd, dlg.GetPathName()) == 0)
					{
						EnableWindow(FALSE);
						m_Progress.SetPos(0);
						m_bCut = TRUE;
					}
				}
			}
		}
	}
}


void CUVSLib_MP4FileDlg::OnNMClickMp4list(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (pNMItemActivate->iItem >= 0)
	{
		CString str(m_MP4List.GetItemText(pNMItemActivate->iItem, 0));
		PathRenameExtension(str.GetBuffer(MAX_PATH), _T(".m4i"));
		str.ReleaseBuffer();
		GetDlgItem(IDC_REPAIR)->EnableWindow(PathFileExists(str));
	}
	*pResult = 0;
}

void CUVSLib_MP4FileDlg::MP4TitleAdd(const CString &filename, int beginTime, int titleTime)
{
	POSITION pos = m_MP4List.GetFirstSelectedItemPosition();
	if (pos)
	{
		CString inputFile(m_MP4List.GetItemText(m_MP4List.GetNextSelectedItem(pos), 0));

		uvs_mp4_file_status_t status;
		int r = CDevSDK::MP4FileGetStatus(inputFile, status);
		if (r == UVS_OK)
		{
			uvs_mp4_file_title_tX title = {0};

			CString text;
			GetDlgItemText(IDC_TEXT, text);
			if (!text.IsEmpty())
			{
				title.szTitleText = text;
			}

			CString image;
			GetDlgItemText(IDC_IMAGE, image);
			if (!image.IsEmpty())
			{
				title.szTitleImageFile = image;
				title.imageOpacity = 128;
			}

			title.x = 0;
			title.y = 0;
			title.width = status.videoWidth;
			title.height = status.videoHeight;
			title.textFont = m_OSDFont;
			if (CDevSDK::MP4FileAddTitle(inputFile, beginTime, &title, 1, titleTime, filename) == 0)
			{
				EnableWindow(FALSE);
				m_Progress.SetPos(0);
				m_bTitle = TRUE;
			}
		}
	}
}


void CUVSLib_MP4FileDlg::OnBnClickedLogo()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_MP4List.GetFirstSelectedItemPosition();
	if (pos)
	{
		BOOL bResult;
		int nBegin = GetDlgItemInt(IDC_ADD, &bResult);
		if (bResult)
		{
			int nDisp = GetDlgItemInt(IDC_DISP, &bResult);
			if (bResult)
			{
				CFileDialog dlg(FALSE, _T(".mp4"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("MP4 Files|*.mp4||"));
				if (dlg.DoModal() == IDOK)
				{
					MP4TitleAdd(dlg.GetPathName(), nBegin, nDisp);
				}
			}
		}
	}
}


void CUVSLib_MP4FileDlg::OnBnClickedFont()
{
	// TODO: Add your control notification handler code here
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		_tcscpy_s(m_OSDFont.szFontName, _countof(m_OSDFont.szFontName), dlg.GetFaceName());

		m_OSDFont.fontPointSize = dlg.GetSize() / 10;
		m_OSDFont.textColor = dlg.GetColor();

		int nStyle = m_OSDFont.fontStyle;
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
	}
}


void CUVSLib_MP4FileDlg::OnBnClickedBrowseimg()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Jpeg Files;Png Files;Bitmap Files|*.jpg;*.png;*.bmp|All Files|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_IMAGE, dlg.GetPathName());
	}
}


void CUVSLib_MP4FileDlg::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(FALSE, _T(".jpg"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Jpeg Files;Png Files;Bitmap Files|*.jpg;*.png;*.bmp|All Files|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		MP4TitleAdd(dlg.GetPathName(), 0, 1);
	}
}
