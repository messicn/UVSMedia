
// UVSLib_Rec.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CUVSLib_RecApp:
// See UVSLib_Rec.cpp for the implementation of this class
//

class CUVSLib_RecApp : public CWinApp
{
public:
	CUVSLib_RecApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CUVSLib_RecApp theApp;