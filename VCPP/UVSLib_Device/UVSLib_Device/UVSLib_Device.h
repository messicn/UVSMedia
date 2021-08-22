
// UVSLib_Device.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CUVSLib_DeviceApp:
// See UVSLib_Device.cpp for the implementation of this class
//

class CUVSLib_DeviceApp : public CWinApp
{
public:
	CUVSLib_DeviceApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CUVSLib_DeviceApp theApp;