
// SeniorDesignApp.h : main header file for the SeniorDesignApp application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSeniorDesignAppApp:
// See SeniorDesignApp.cpp for the implementation of this class
//

class CSeniorDesignAppApp : public CWinApp
{
public:
	CSeniorDesignAppApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSeniorDesignAppApp theApp;
