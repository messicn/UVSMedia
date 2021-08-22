
// UVSLib_OSDDlg.h : header file
//

#pragma once


// CUVSLib_OSDDlg dialog
class CUVSLib_OSDDlg : public CDialogEx
{
// Construction
public:
	CUVSLib_OSDDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UVSLIB_OSD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	void DisableOSD(int nIndex);
	void SetRectEllipseOSD(int nIndex, int nCheckID, int nStyleID);
	void VideoOSDControl(void);
	uvs_font_info_tX m_OSDFont;
	CDevSDK m_Dev;

	int m_nVideoWidth;
	int m_nVideoHeight;
	int m_nOSDIndex;
	int m_nOSDControl;
public:
	afx_msg void OnDestroy();
	afx_msg void OnClickedTimeOsd();
	afx_msg void OnSelchangeTimeMode();
	afx_msg void OnSelchangeWeekMode();
	afx_msg void OnSelchangeDateMode();
	afx_msg void OnBnClickedOsdFont();
	afx_msg void OnClickedTextOsd();
	afx_msg void OnClickedImgOsd();
	afx_msg void OnBnClickedImageBrowse();
	afx_msg void OnClickedRectOsd();
	afx_msg void OnSelchangeRectStyle();
	afx_msg void OnClickedEllipseOsd();
	afx_msg void OnSelchangeEllipseStyle();
	afx_msg void OnClickedLineOsd();
	afx_msg void OnSelchangeOsdControl();
	afx_msg void OnSelchangeVideoOsd();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedMultiline();
};
