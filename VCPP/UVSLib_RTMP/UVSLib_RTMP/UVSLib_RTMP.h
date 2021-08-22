
// UVSLib_RTMP.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CUVSLib_RTMPApp:
// See UVSLib_RTMP.cpp for the implementation of this class
//

class CUVSLib_RTMPApp : public CWinApp
{
public:
	CUVSLib_RTMPApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CUVSLib_RTMPApp theApp;