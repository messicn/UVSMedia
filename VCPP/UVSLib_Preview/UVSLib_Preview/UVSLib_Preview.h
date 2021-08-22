
// UVSLib_Preview.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CUVSLib_PreviewApp:
// See UVSLib_Preview.cpp for the implementation of this class
//

class CUVSLib_PreviewApp : public CWinApp
{
public:
	CUVSLib_PreviewApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CUVSLib_PreviewApp theApp;