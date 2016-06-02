
// MFC_1.h : main header file for the MFC_1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFC_1App:
// See MFC_1.cpp for the implementation of this class
//

class CMFC_1App : public CWinApp
{
public:
	CMFC_1App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFC_1App theApp;
