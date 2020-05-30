#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "PhonebookApp.h"
#include "MainFrame.h"
#include "ChildFrame.h"
#include "CitiesDocument.h"
#include "CitiesView.h"
#include "PersonsDocument.h"
#include "PersonsView.h"
#include "Structures.h"
#include "CitiesTable.h"
#include "PhoneTypesTable.h"
#include "PhoneTypesDocument.h"
#include "PhoneTypesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhonebookApp

BEGIN_MESSAGE_MAP(CPhoneBookApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPhoneBookApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


CPhoneBookApp::CPhoneBookApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	SetAppID(_T("Phonebook"));

}

// The one and only CPhoneBookApp object
CPhoneBookApp theApp;


BOOL CPhoneBookApp::InitInstance()
{	
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	CoInitialize(NULL);

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// Създава се единствената инстанция на CDataBase
	CDataBase::GetDataBase();

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_PERSONS_DOC_TYPE,
		RUNTIME_CLASS(CPersonsDocument),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CPersonsView));

	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	pDocTemplate = new CMultiDocTemplate(IDR_CITIES_DOC_TYPE,
		RUNTIME_CLASS(CCitiesDocument),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CCitiesView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_PHONE_TYPES_DOC_TYPE,
		RUNTIME_CLASS(CPhoneTypesDocument),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CPhoneTypesView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	return TRUE;	
}

int CPhoneBookApp::ExitInstance()
{
	CDataBase::GetDataBase().CloseConnection();

	//Изкарва репорт за memory leaks в output
	_CrtDumpMemoryLeaks();

	AfxOleTerm(FALSE);

	CoUninitialize();

	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg

class CAboutDlg : public CDialogEx
{
// Macros
// ----------------
	DECLARE_MESSAGE_MAP()

// Constants
// ----------------
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

// Constructor / Destructor
// ----------------
public:
	CAboutDlg();

// MFC Overrides
// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	virtual BOOL OnInitDialog();
};

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CPhoneBookApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE; 
}
