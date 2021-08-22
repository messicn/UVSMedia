
// UVSLib_RTSP.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CUVSLib_RTSPApp:
// See UVSLib_RTSP.cpp for the implementation of this class
//

class CUVSLib_RTSPApp : public CWinApp
{
public:
	CUVSLib_RTSPApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CUVSLib_RTSPApp theApp;