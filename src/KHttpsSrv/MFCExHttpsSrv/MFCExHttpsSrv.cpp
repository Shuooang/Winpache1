// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MFCExHttpsSrv.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MFCExHttpsSrv.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "SrvDoc.h"
#include "SrvView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCExHttpsSrvApp

BEGIN_MESSAGE_MAP(CMFCExHttpsSrvApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMFCExHttpsSrvApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CMFCExHttpsSrvApp construction

CMFCExHttpsSrvApp::CMFCExHttpsSrvApp() noexcept
{
	m_bHiColorIcons = TRUE;


	m_nAppLook = 0;
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	//SetAppID(_T("WinpachePro.AppID.NoVersion"));
	SetAppID(_T("Keepspeed.Winpache.WinpachePro.Ver1.0.1"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CMFCExHttpsSrvApp object

CMFCExHttpsSrvApp theApp;


// CMFCExHttpsSrvApp initialization

BOOL CMFCExHttpsSrvApp::InitInstance()
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

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("WinpachePro"));//?zzz// Local AppWizard - Generated Applications"));
	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)

	CMainPool::Pool(8);//?zzz

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_WinpacheTYPE,
		RUNTIME_CLASS(SrvDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSrvView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);





	_doc.LoadData();






	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CMFCExHttpsSrvApp::ExitInstance()
{
	_doc.SaveData();
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMFCExHttpsSrvApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CMFCExHttpsSrvApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMFCExHttpsSrvApp customization load/save methods

void CMFCExHttpsSrvApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CMFCExHttpsSrvApp::LoadCustomState()
{
}

void CMFCExHttpsSrvApp::SaveCustomState()
{
}

// CMFCExHttpsSrvApp message handlers


/// //////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(KAppDoc, CDocument)

// BEGIN_MESSAGE_MAP(KAppDoc, CDocument)
// END_MESSAGE_MAP()


// KAppDoc construction/destruction

KAppDoc::KAppDoc() noexcept
{
}

KAppDoc::~KAppDoc()
{
}

BOOL KAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}
void KAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		//CJsonPbj js;
		JObj js;

		if (_GUID.IsEmpty())
			_GUID = KwGetFormattedGuid();
		KJSPUT(_GUID);
		KJSPUT(_fname);
		KJSPUT(_DSN);
		KJSPUT(_UID);
		KJSPUT(_database);
		KJSPUT(_statDB);
		CFile* fr = ar.GetFile();

		CStringA sUtf8 = js.ToJsonStringUtf8();
		fr->Write((PAS)sUtf8, sUtf8.GetLength());
	}
	else
	{
		CFile* fr = ar.GetFile();
		int len = (int)fr->GetLength();
		CStringA sa;
		char* buf = sa.GetBufferSetLength(len);
		fr->Read(buf, len);
		CString sWstr;
		KwUTF8ToWchar(buf, sWstr);

		auto jdoc = ShJVal(Json::Parse((PWS)sWstr));
		if (jdoc.get() == nullptr)
		{
			AfxMessageBox(L"파일 포맷 오류.");
			return;
		}
		auto& js = *jdoc->AsObject().get();

		KJSGETS(_GUID);
		if (_GUID.IsEmpty())
			_GUID = KwGetFormattedGuid();
		KJSGETS(_fname);
		KJSGETS(_DSN);
		KJSGETS(_UID);
		//KJSGETS(_PWD);
		KJSGETS(_database);
		KJSGETS(_statDB);
		//KJSGETI(_UID);// 숫자인 경우
	}
}

void KAppDoc::LoadData()
{
	CString full = GetFilePath();
	if (KwIfFileExist(full))
	{
		if (!OnOpenDocument(full))
		{
			TRACE("Error! File Winpache.json loading.");
			return;
		}
		SetPathName(full, FALSE);
		//OnDocumentEvent(CDocument::onAfterOpenDocument);
	}
}

CString KAppDoc::GetFilePath()
{
	TCHAR curDir[1002];
	GetCurrentDirectory(1000, curDir);//C:\Users\dwkang\AppData\Roaming\Outbin\KHttpsSrv\x64\Debug
	//L"Winpache.json";
	WCHAR appdata[MAX_PATH];//CSIDL_PERSONAL
	HRESULT result = SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, appdata);

	CString fl; fl.Format(L"%s\\Winpache\\", appdata);
	CString full = fl + _fname;
	//CString fl; fl.Format(L"..\\..\\%s", fname);
	return full;
}
//C:\Program Files(x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30037
// \atlmfc\src\mfc\afximpl.h
//#include <afximpl.h>
void KAppDoc::SaveData()
{
#ifdef _DEBUG
	PWS fname = L"..\\..\\..\\log\\t_reqlog.log";
	PWS fname1 = L"..\\..\\..\\log\\t_reqlogx.log";//wrong file
	PWS fname2 = L"..\\..\\..\\logx\\t_reqlog.log";//wrong dir
	PWS fname3 = L"..\\..\\..\\logx\\t_reqlogx.log";//both wrong
// 	TCHAR lpszPathOut[512];
// 	BOOL b1 = AfxFullPath(lpszPathOut, fname);
	CString path;
	PWS pFile{ 0 };//result is always OK
	DWORD dw0 = KwGetFullPathName(fname, path, &pFile);//57
	DWORD dw1 = KwGetFullPathName(fname1, path, &pFile);//58
	DWORD dw2 = KwGetFullPathName(fname2, path, &pFile);//58
	DWORD dw3 = KwGetFullPathName(fname3, path, &pFile);//59
#endif // _DEBUG

	const CString& full0 = GetPathName();
	if (full0.GetLength() > 0)
		VERIFY(DoFileSave());
	else
	{
		//auto app = AfxGetApp();
		CString full = GetFilePath();
		VERIFY(DoSave(full, 0));
	}
}