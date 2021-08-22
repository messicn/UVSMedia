
// UVSLib_NDI.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CUVSLib_NDIApp:
// See UVSLib_NDI.cpp for the implementation of this class
//

class CUVSLib_NDIApp : public CWinApp
{
public:
	CUVSLib_NDIApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CUVSLib_NDIApp theApp;