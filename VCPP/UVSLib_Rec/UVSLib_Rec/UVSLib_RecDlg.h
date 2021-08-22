
// UVSLib_RecDlg.h : header file
//

#pragma once

// CUVSLib_RecDlg dialog
class CUVSLib_RecDlg : public CDialogEx
{
// Construction
public:
	CUVSLib_RecDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UVSLIB_REC_DIALOG };

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
	CDevSDK m_Dev;
	BOOL m_bRecStart;
	BOOL m_bRecResume;
	void BrowseFolder(UINT nID);
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedRecControl();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedMainDir();
	afx_msg void OnBnClickedSubDir();
	afx_msg void OnBnClickedRecPause();
};
