
// UVSLib_MP4File.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CUVSLib_MP4FileApp:
// See UVSLib_MP4File.cpp for the implementation of this class
//

class CUVSLib_MP4FileApp : public CWinApp
{
public:
	CUVSLib_MP4FileApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CUVSLib_MP4FileApp theApp;