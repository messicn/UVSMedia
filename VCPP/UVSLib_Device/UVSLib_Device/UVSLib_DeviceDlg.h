
// UVSLib_DeviceDlg.h : header file
//

#pragma once


// CUVSLib_DeviceDlg dialog
class CUVSLib_DeviceDlg : public CDialogEx
{
// Construction
public:
	CUVSLib_DeviceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UVSLIB_DEVICE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CDevSDK m_Dev;
	COLORREF m_BkColor;

	static void CALLBACK UVSDevCallback(uvs_dev_notify_e notify, const uvs_dev_info_tX *info, uvsobj_handle obj, void *pUserData);
	void DevStart(void);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnBnClickedColor();
	afx_msg void OnBnClickedOk();
protected:
	afx_msg LRESULT OnDevchanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDevclosed(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
