#pragma once

#include <stdlib.h>
#include <crtdbg.h>
#include "DataBase.h"
#include "resource.h" 

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#define _CRTDBG_MAP_ALLOC
  

/////////////////////////////////////////////////////////////////////////////
// CPhonebookApp

class CPhoneBookApp : public CWinApp
{
// Macros
// ----------------
	DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
public:
	CPhoneBookApp();

// MFC Overrides
// ----------------
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// MFC Message Handlers
// ----------------
	afx_msg void OnAppAbout();

};

extern CPhoneBookApp theApp;
