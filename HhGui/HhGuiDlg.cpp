// HhGuiDlg.cpp : implementation file
//

#include "stdafx.h"

#include <HhGui/HhGui.h>
#include <HhGui/HhGuiDlg.h>
#include <HhGui/FolderBrowser.h>
#include "hhguidlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char* section = "HHGUI";
const char* iniFile = "hhGui.ini";
const char* iniFileConfigFileTagName = "configFile";
const char* iniFileLeftTagName = "left";
const char* iniFileTopTagName = "top";

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
    DDX_Text(pDX, IDC_VERSION, CString(HH_VERSION_AS_STRING));
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define REPORT_SUCCESS                          \
        m_state = "Operation succeeded";        \
        UpdateData( false );

#define REPORT_ERROR                            \
        m_state = "Operation failed";           \
        UpdateData( false );

#define REPORT_ABORT                            \
        m_state = "Operation aborted by user";  \
        UpdateData( false );

/////////////////////////////////////////////////////////////////////////////
// CHhGuiDlg dialog

CHhGuiDlg::CHhGuiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHhGuiDlg::IDD, pParent),
      m_inInitDialog( true )
{
	//{{AFX_DATA_INIT(CHhGuiDlg)
	m_configFile = _T("");
	m_inputScript = _T("");
	m_result = _T("");
	m_state = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHhGuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHhGuiDlg)
	DDX_Text(pDX, IDC_CONFIG_FILE, m_configFile);
	DDV_MaxChars(pDX, m_configFile, _MAX_PATH);
	DDX_Text(pDX, IDC_INPUT_SCRIPT, m_inputScript);
	DDX_Text(pDX, IDC_RESULT, m_result);
	DDX_Text(pDX, IDC_STATE, m_state);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHhGuiDlg, CDialog)
	//{{AFX_MSG_MAP(CHhGuiDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RUN_TEST, OnRunTest)
	ON_BN_CLICKED(IDC_VIEW_FAILURES, OnViewFailures)
	ON_BN_CLICKED(IDC_APPROVE_TEST, OnApproveTest)
	ON_BN_CLICKED(IDC_GENERATE_CONFIG_FILE, OnGenerateConfigFile)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_EDIT_IN_FILE, OnBnClickedEditInFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHhGuiDlg message handlers

BOOL CHhGuiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
    UpdateData( false );

    char leftAsString[ 64 ] = {0};
    ::GetPrivateProfileString(
        section,
        iniFileLeftTagName,
        "0",
        leftAsString,
        sizeof leftAsString,
        iniFile );
    
    char topAsString[ 64 ] = {0};
    ::GetPrivateProfileString(
        section,
        iniFileTopTagName,
        "0",
        topAsString,
        sizeof topAsString,
        iniFile );

    RECT rect;
    GetWindowRect( &rect );
    rect.left = atoi( leftAsString );
    rect.top = atoi( topAsString );
    rect.bottom += rect.top;
    rect.right += rect.left;
    MoveWindow( &rect );

    char configFile[ _MAX_PATH ];
    ::GetPrivateProfileString(
        section,
        iniFileConfigFileTagName,
        "",
        configFile,
        sizeof configFile,
        iniFile );
    m_configFile = configFile;

    try
    {
        ChangeDir();
        HH_Runtime  runtime( GetIniFile(), ( const char* )m_configFile, *this );
        m_inputScript = strrchr( runtime.GetInputFileName().c_str(), '\\' ) + 1;
    }
    catch( HH_Exception& ex )
    {
        AfxMessageBox( ex.AsString().c_str() );
    }

    m_state = "";
    m_result = "";
    UpdateData( false );

    m_inInitDialog = false;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CHhGuiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


void CHhGuiDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHhGuiDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHhGuiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CHhGuiDlg::OnOK() 
{
	CDialog::OnOK();
}


std::string CHhGuiDlg::GetIniFile()
{
    char modulePath[ _MAX_PATH ];

    if ( !::GetModuleFileName( ::GetModuleHandle( NULL ), modulePath, sizeof modulePath ) )
    {
        throw HH_Win32Error( "::GetModuleFileName() failed", ::GetLastError() );
    }
    *( strrchr( modulePath, '\\' ) + 1 ) = '\0';

    return std::string( modulePath ) + "hh.ini";
}


void CHhGuiDlg::OnRunTest() 
{
    try
    {
        if ( CheckForEmptyConfigFile() )
        {
            ChangeDir();
            HH_Runtime  runtime( GetIniFile(), ( const char* )m_configFile, *this );
            UpdateData( false );
            runtime.ExecuteUnitTest( "" );
            REPORT_SUCCESS;
        }
    }
    catch ( HH_Exception& ex )
    {
        REPORT_ERROR;
        ::AfxMessageBox( ex.AsString().c_str() );
    }
}


void CHhGuiDlg::OnViewFailures() 
{
    try
    {
        if ( CheckForEmptyConfigFile() )
        {
            ChangeDir();
            HH_Runtime  runtime( GetIniFile(), ( const char* )m_configFile, *this );
            UpdateData( false );
            runtime.ViewUnitTestFailures();
            REPORT_SUCCESS;
        }
    }
    catch ( HH_Exception& ex )
    {
        REPORT_ERROR;
        ::AfxMessageBox( ex.AsString().c_str() );
    }
}


void CHhGuiDlg::OnApproveTest() 
{
    try
    {
        if ( CheckForEmptyConfigFile() )
        {
            ChangeDir();
            HH_Runtime  runtime( GetIniFile(), ( const char* )m_configFile, *this );
            UpdateData( false );
            runtime.ApproveUnitTest();
            REPORT_SUCCESS;
        }
    }
    catch ( HH_Exception& ex )
    {
        REPORT_ERROR;
        ::AfxMessageBox( ex.AsString().c_str() );
    }
}


void CHhGuiDlg::OnGenerateConfigFile() 
{
    try
    {
        HH_FolderBrowser    folderBrowser;

        if ( folderBrowser.DoModal(
            this->GetSafeHwnd(),
            "Choose the folder where you want to generate a default config file." ) == IDOK )
        {
            m_configFile = folderBrowser.GetFolderPath().c_str();
            
            if ( m_configFile[ m_configFile.GetLength() - 1 ] != '\\' )
            {
                m_configFile += '\\';
            }
            
            m_configFile += CString( "hh.cfg" );
            ChangeDir();
            HH_Runtime::GenerateConfigFile( *this );
            REPORT_SUCCESS;
        }
        else
        {
            REPORT_ABORT;
        }
    }
    catch ( HH_Exception& ex )
    {
        REPORT_ERROR;
        ::AfxMessageBox( ex.AsString().c_str() );
    }
}


void CHhGuiDlg::OnBrowse() 
{
    CFileDialog fileDialog(
        TRUE,                                                   // open dialog
        ".cfg",                                                 // default extension
        "*.cfg",                                                // default file name
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        "Hammerhead Config Files (*.cfg)|*.cfg|All Files (*.*)|*.*||\0",
        this );

    if ( fileDialog.DoModal() == IDOK )
    {
        m_configFile = fileDialog.GetPathName();
        ChangeDir();
        HH_Runtime  runtime( GetIniFile(), ( const char* )m_configFile, *this );
        m_inputScript = strrchr( runtime.GetInputFileName().c_str(), '\\' ) + 1;
        m_state = "";
        m_result = "";
        UpdateData( false );
    }
}


void CHhGuiDlg::ChangeDir()
{
    char drive[_MAX_DRIVE];
    char path[_MAX_DIR];

    ::ZeroMemory( drive, sizeof drive );
    ::ZeroMemory( path, sizeof path );

    ::_splitpath_s( ( const char* )m_configFile, drive, sizeof drive, path, sizeof path, NULL, 0, NULL, 0 );

    if( *drive != '\0' && _chdrive( toupper( *drive ) - 'A' + 1 ) != 0 )
    {
        std::string message = "Can't change drives to '";
        message += drive;
        message += "' with ::_chdrive()";
        throw HH_ErrnoError( message, errno );
    }

    std::string completePath = std::string( drive ) + std::string( path );
    if ( _chdir( completePath.c_str() ) != 0 )
    {
        std::string message = "Can't change directories to '";
        message += completePath;
        message += "' with ::_chdir()";
        throw HH_ErrnoError( message, errno );
    }

    ::WritePrivateProfileString(
        section,
        iniFileConfigFileTagName,
        m_configFile,
        iniFile );
}


bool CHhGuiDlg::CheckForEmptyConfigFile()
{
    UpdateData();
    if ( strlen( m_configFile ) == 0 )
    {
        ::AfxMessageBox( "You must specify a config file to complete this operation. Please provide a path to an existing config file.", MB_ICONWARNING );
        CWnd* pConfigFileTextBox = GetDlgItem( IDC_CONFIG_FILE );
        ASSERT( pConfigFileTextBox != NULL );
        pConfigFileTextBox->SetFocus();
        return false;
    }
    return true;
}


void CHhGuiDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
    RECT rect;
    GetWindowRect( &rect );
    if ( !m_inInitDialog )
    {
        char leftAsString[ 64 ] = {0};
        _itoa_s( rect.left, leftAsString, 10 );
        ::WritePrivateProfileString(
            section,
            iniFileLeftTagName,
            leftAsString,
            iniFile );

        char topAsString[ 64 ] = {0};
        _itoa_s( rect.top, topAsString, 10 );
        ::WritePrivateProfileString(
            section,
            iniFileTopTagName,
            topAsString,
            iniFile );
    }
}

void CHhGuiDlg::OnBnClickedEditInFile()
{
    try
    {
        if ( CheckForEmptyConfigFile() )
        {
            ChangeDir();
            HH_Runtime  runtime( GetIniFile(), ( const char* )m_configFile, *this );
            UpdateData( false );
            runtime.EditDotInFile();
            REPORT_SUCCESS;
        }
    }
    catch ( HH_Exception& ex )
    {
        REPORT_ERROR;
        ::AfxMessageBox( ex.AsString().c_str() );
    }
}
