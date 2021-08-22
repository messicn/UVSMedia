
// UVSLib_PreviewDlg.h : header file
//

#pragma once

#include <unordered_map>

// CUVSLib_PreviewDlg dialog
class CUVSLib_PreviewDlg : public CDialogEx
{
// Construction
public:
	CUVSLib_PreviewDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UVSLIB_PREVIEW_DIALOG };

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
	std::unordered_map<int, uvs_video_effect_e> m_map;
	int m_nAudioIndex;
	int m_nVideoIndex;
	int m_nAudioRender;

	BOOL m_bFullScreen;
	BOOL m_bDigitalZoom;
	BOOL m_bDispRect;

	CWnd *m_pVideoWnd;
	CWnd *m_pParentWnd;
	RECT m_VideoRect;
	CDevSDK m_Dev;

	void DevStart(void);

public:
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeAudioInput();
	afx_msg void OnSelchangeVideoInput();
	afx_msg void OnClickedDisp();
	afx_msg void OnBnClickedFullScreen();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedDigitalZoom();
	afx_msg void OnBnClickedDispRect();
	afx_msg void OnBnClickedDispFreeze();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCbnSelchangeAudioOutput();
	afx_msg void OnBnClickedMute();
	afx_msg void OnClickedFlip();
	afx_msg void OnClickedMirror();
};
