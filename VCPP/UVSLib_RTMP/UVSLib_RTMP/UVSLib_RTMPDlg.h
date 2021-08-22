
// UVSLib_RTMPDlg.h : header file
//

#pragma once

// CUVSLib_RTMPDlg dialog
class CUVSLib_RTMPDlg : public CDialogEx
{
// Construction
public:
	CUVSLib_RTMPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UVSLIB_RTMP_DIALOG };

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
	afx_msg void OnDestroy();
private:
	CDevSDK m_Dev;
	CFileRTMP* m_pFile;
	BOOL m_bLive;
	void FileRTMPStop();
public:
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnBnClickedRtmpLive();
	afx_msg void OnBnClickedRtmpFile();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
