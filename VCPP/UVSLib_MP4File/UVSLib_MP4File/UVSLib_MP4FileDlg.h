
// UVSLib_MP4FileDlg.h : header file
//

#pragma once
#include "afxcmn.h"

// CUVSLib_MP4FileDlg dialog
class CUVSLib_MP4FileDlg : public CDialogEx
{
// Construction
public:
	CUVSLib_MP4FileDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UVSLIB_MP4FILE_DIALOG };

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
public:
	afx_msg void OnBnClickedBrowse();
	void SetFilePath(void);
	void MP4TitleAdd(const CString &filename, int beginTime, int titleTime);
	afx_msg void OnEnChangeDir();
	afx_msg void OnBnClickedRepair();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedMerge();
	afx_msg void OnBnClickedCut();
	afx_msg void OnNMClickMp4list(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedLogo();
	afx_msg void OnBnClickedFont();
	afx_msg void OnBnClickedBrowseimg();

private:
	uvs_font_info_tX m_OSDFont;
	CListCtrl m_MP4List;
	BOOL m_bRepair;
	BOOL m_bMerge;
	BOOL m_bCut;
	BOOL m_bTitle;
	CProgressCtrl m_Progress;
public:
	afx_msg void OnBnClickedSave();
};
