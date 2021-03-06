// HhGui.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include <HhGui/HhGui.h>
#include <HhGui/HhGuiDlg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHhGuiApp

BEGIN_MESSAGE_MAP(CHhGuiApp, CWinApp)
	//{{AFX_MSG_MAP(CHhGuiApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHhGuiApp construction

CHhGuiApp::CHhGuiApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHhGuiApp object

CHhGuiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHhGuiApp initialization

BOOL CHhGuiApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER == 1200            // VC++ 6.0
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	CHhGuiDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
