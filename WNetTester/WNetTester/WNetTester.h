
// WNetTester.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWNetTesterApp:
// See WNetTester.cpp for the implementation of this class
//

class CWNetTesterApp : public CWinApp
{
public:
	CWNetTesterApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CWNetTesterApp theApp;