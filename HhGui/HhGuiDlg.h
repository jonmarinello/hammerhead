// HhGuiDlg.h : header file
//

#if !defined(AFX_HHGUIDLG_H__A5F35FDB_172A_49C1_B288_62A1C823478A__INCLUDED_)
#define AFX_HHGUIDLG_H__A5F35FDB_172A_49C1_B288_62A1C823478A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <HhUnitTestFramework/UnitTest.h>
#include <HhRuntime/version.h>
#include <HhRuntime/Runtime.h>


/////////////////////////////////////////////////////////////////////////////
// CHhGuiDlg dialog

class CHhGuiDlg : public CDialog, public HH_Notifier
{
// Construction
public:
	CHhGuiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHhGuiDlg)
	enum { IDD = IDD_HHGUI_DIALOG };
	CString	m_configFile;
    CString m_inputScript;
	CString	m_result;
	CString	m_state;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHhGuiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:

    virtual void ReportProgressMessage( const std::string& message )
    {
        m_state = message.c_str();
        UpdateData( false );
    }

    virtual void ReportTestResult( bool testPassed )
    {
        m_result = testPassed ? "TEST PASSED" : "TEST FAILED";
        UpdateData( false );
    }

    virtual bool OverwriteConfigFileCheck( const std::string& configFileName )
    {
        std::stringstream messageStream;
        messageStream << "\"" << configFileName << "\"" << " already exists. Overwrite?";

        if ( ::AfxMessageBox( messageStream.str().c_str(), MB_ICONQUESTION | MB_YESNO ) == IDYES )
        {
            return true;
        }
        return false;
    }

    std::string GetIniFile();

    void UpdateFields( const HH_Runtime& runtime );

    void ChangeDir();

    bool CheckForEmptyConfigFile();

// Implementation
protected:
	HICON   m_hIcon;
    bool    m_inInitDialog;

	// Generated message map functions
	//{{AFX_MSG(CHhGuiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnRunTest();
	afx_msg void OnViewFailures();
	afx_msg void OnApproveTest();
	afx_msg void OnGenerateConfigFile();
	afx_msg void OnBrowse();
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedEditInFile();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HHGUIDLG_H__A5F35FDB_172A_49C1_B288_62A1C823478A__INCLUDED_)
