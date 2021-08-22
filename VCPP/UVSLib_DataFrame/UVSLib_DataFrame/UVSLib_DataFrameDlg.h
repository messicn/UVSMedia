
// UVSLib_DataFrameDlg.h : header file
//

#pragma once


// CUVSLib_DataFrameDlg dialog
class CUVSLib_DataFrameDlg : public CDialogEx
{
// Construction
public:
	CUVSLib_DataFrameDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UVSLIB_DATAFRAME_DIALOG };

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
	BOOL GetVideoConvertParam(uvs_frame_convert_t &convert);

	BOOL m_bAudioCallback;
	BOOL m_bVideoCallback;
	BOOL m_bEncCallback;

public:
	afx_msg void OnBnClickedVideoSnapshot();
	afx_msg void OnBnClickedVideoRaw();
	afx_msg void OnBnClickedAudioRaw();
	afx_msg void OnBnClickedEncodeData();
	afx_msg void OnBnClickedVideoLock();
	afx_msg void OnBnClickedAudioLock();
	afx_msg void OnBnClickedVideoCopy();
	afx_msg void OnBnClickedAudioCopy();
};
