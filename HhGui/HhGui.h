// HhGui.h : main header file for the HHGUI application
//

#if !defined(AFX_HHGUI_H__53DAD506_92D7_4682_A6AF_9C4791ADC655__INCLUDED_)
#define AFX_HHGUI_H__53DAD506_92D7_4682_A6AF_9C4791ADC655__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHhGuiApp:
// See HhGui.cpp for the implementation of this class
//

class CHhGuiApp : public CWinApp
{
public:
	CHhGuiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHhGuiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHhGuiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HHGUI_H__53DAD506_92D7_4682_A6AF_9C4791ADC655__INCLUDED_)
