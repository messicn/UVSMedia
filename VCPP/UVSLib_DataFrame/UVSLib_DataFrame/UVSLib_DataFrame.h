
// UVSLib_DataFrame.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CUVSLib_DataFrameApp:
// See UVSLib_DataFrame.cpp for the implementation of this class
//

class CUVSLib_DataFrameApp : public CWinApp
{
public:
	CUVSLib_DataFrameApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CUVSLib_DataFrameApp theApp;