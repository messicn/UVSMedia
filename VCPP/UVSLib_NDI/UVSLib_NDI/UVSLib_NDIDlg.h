
// UVSLib_NDIDlg.h : header file
//

#pragma once

// CUVSLib_NDIDlg dialog
class CUVSLib_NDIDlg : public CDialogEx
{
// Construction
public:
	CUVSLib_NDIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UVSLIB_NDI_DIALOG };

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
	BOOL m_bNDIStart;
public:
	afx_msg void OnBnClickedNdiControl();
};
