
// UVSLib_RTSPDlg.h : header file
//

#pragma once

// CUVSLib_RTSPDlg dialog
class CUVSLib_RTSPDlg : public CDialogEx
{
// Construction
public:
	CUVSLib_RTSPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UVSLIB_RTSP_DIALOG };

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
	USHORT m_nPort;
	CFileRTSP* m_pFile;
	BOOL m_bLive;
	BOOL RTSPServerCreate();
	void RTSPServerDestroy();
	void FileRTSPStreamClose();
public:
	afx_msg void OnBnClickedMp4Browse();
	afx_msg void OnBnClickedRtspLive();
	afx_msg void OnBnClickedRtspFile();
};
