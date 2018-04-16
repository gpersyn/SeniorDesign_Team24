
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SeniorDesignApp.h"

#include "MainFrm.h"

//Dialogs
#include "UserLoginDlg.h"
//Database
//For Database
#include "odbcinst.h"
#include "afxdb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame 

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	//User Login
	/*UserLoginDlg UserLogin;
	if (UserLogin.DoModal() == true) { //Check Username and Password
		//User Input
		CString UserName, UserPassword;
		UserName = UserLogin.m_UserName;
		UserPassword = UserLogin.m_Password;

		//Get info from database
		CDatabase database;
		CString SqlString;
		CString tempUserType, tempPassword;
		CString sDriver = L"SQL Server";
		CString sDsn;
		CString sMc = L"GARRETT-DESKTOP";
		CString sFile = L"AppTest1";
		int iRec = 0;

		// Build ODBC connection string
		sDsn.Format(L"ODBC;Driver={%s};Server=%s;Database=%s;Trusted_Connection=yes", sDriver, sMc, sFile);
		TRY{
			// Open the database
			database.Open(NULL,false,false,sDsn);

		// Allocate the recordset
		CRecordset recset(&database);

		//Sensor Table

		// Build the SQL statement
		SqlString.Format(L"SELECT Usertype, Passwords FROM Users Where UserName = '%s'", UserName);

		// Execute the query
		recset.Open(CRecordset::forwardOnly,SqlString,CRecordset::readOnly);

		// Loop through each record
		while (!recset.IsEOF()) {
			// Copy each column into a variable
			recset.GetFieldValue(L"Usertype", tempUserType);
			recset.GetFieldValue(L"Passwords", tempPassword);
		

			// goto next record
			recset.MoveNext();
		}

		// Close the database
		database.Close();
		}CATCH(CDBException, e) {
			// If a database exception occured, show error msg
			//AfxMessageBox("Database error: " + e→m_strError);
		}
		END_CATCH;

		//Check if user input and database match
		bool temp1 = tempPassword != UserPassword;
		bool temp2 = tempUserType != L"ADMIN";
		if (temp1 | temp2) {
			exit(0);
		}
		
	}
	else {
		exit(0);
	}*/
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

