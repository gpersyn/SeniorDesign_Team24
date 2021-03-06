// TestSQLDatabase.cpp : implementation file
//

#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "TestSQLDatabase.h"
#include "afxdialogex.h"
//For Database
#include "odbcinst.h"
#include "afxdb.h"

// TestSQLDatabase dialog

IMPLEMENT_DYNAMIC(TestSQLDatabase, CDialogEx)

TestSQLDatabase::TestSQLDatabase(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEST_SQL, pParent)
{

}

TestSQLDatabase::~TestSQLDatabase()
{
}

void TestSQLDatabase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_SQL_TEST, m_ListControl);
}


BEGIN_MESSAGE_MAP(TestSQLDatabase, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_DATABASE_TEST, &TestSQLDatabase::OnBnClickedButtonWriteDatabaseTest)
	ON_BN_CLICKED(IDC_BUTTON_READ_DATABASE_TEST, &TestSQLDatabase::OnBnClickedButtonReadDatabaseTest)
END_MESSAGE_MAP()


// TestSQLDatabase message handlers


void TestSQLDatabase::OnBnClickedButtonWriteDatabaseTest() //Send Test Query to Database
{
	CDatabase database;
	CString SqlString;
	CString strID, strName, strAge;
	CString sDriver = L"SQL Server";
	CString sDsn;
	CString sMc = L"GARRETT-DESKTOP";
	CString sFile = L"AppTest1";
	// You must change above path if it's different
	int iRec = 0;

	// Build ODBC connection string
	//sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sFile);
	//sDsn = L"Data Source=GARRETT-DESKTOP;Initial Catalog=AppTest1;Integrated Security=True";
	sDsn.Format(L"ODBC;Driver={%s};Server=%s;Database=%s;Trusted_Connection=yes", sDriver, sMc, sFile);

	TRY{
		// Open the database
		database.Open(NULL,false,false,sDsn);
	//if (database.Open(NULL,false,false,sDsn))
	//AfxMessageBox("database opened!");

	SqlString = "INSERT INTO Employees (ID,Name,age) VALUES (4,'John',36)";
	//SqlString = "DELETE Employees where Name='Sammy'";
	//SqlString = "TOP (1000) [ID], [Name], [Age] FROM [AppTest1].[dbo].[Employees]";
	database.ExecuteSQL(SqlString);
	// Close the database
	database.Close();
	}CATCH(CDBException, e) {
		// If a database exception occured, show error msg
		//AfxMessageBox(L"Database error: " + e→m_strError);
	}
	END_CATCH;
}


void TestSQLDatabase::OnBnClickedButtonReadDatabaseTest() //When Test Database Read Button is Pressed
{
	// TODO: Add your control notification handler code here
	CDatabase database;
	CString SqlString;
	CString strID, strName, strAge;
	CString sDriver = L"SQL Server";
	CString sDsn;
	CString sMc = L"GARRETT-DESKTOP";
	CString sFile = L"AppTest1";
	// You must change above path if it's different
	int iRec = 0;

	// Build ODBC connection string
	sDsn.Format(L"ODBC;Driver={%s};Server=%s;Database=%s;Trusted_Connection=yes", sDriver, sMc, sFile);
	TRY{
		// Open the database
		database.Open(NULL,false,false,sDsn);

	// Allocate the recordset
	CRecordset recset(&database);

	// Build the SQL statement
	SqlString = "SELECT ID, Name, Age " "FROM Employees";

	// Execute the query

	recset.Open(CRecordset::forwardOnly,SqlString,CRecordset::readOnly);
	// Reset List control if there is any data
	ResetListControl();
	// populate Grids
	ListView_SetExtendedListViewStyle(m_ListControl,LVS_EX_GRIDLINES);
	
	//m_ListControl.InsertColumn(0, L"Name", LVCFMT_LEFT, 100);
	// Column width and heading
	m_ListControl.InsertColumn(0,L"Emp ID",LVCFMT_LEFT,-1,0);
	m_ListControl.InsertColumn(1,L"Name",LVCFMT_LEFT,-1,1);
	m_ListControl.InsertColumn(2, L"Age", LVCFMT_LEFT, -1, 1);
	m_ListControl.SetColumnWidth(0, 120);
	m_ListControl.SetColumnWidth(1, 200);
	m_ListControl.SetColumnWidth(2, 200);
	
	// Loop through each record
	while (!recset.IsEOF()) {
		// Copy each column into a variable
		recset.GetFieldValue(L"ID",strID);
		recset.GetFieldValue(L"Name",strName);
		recset.GetFieldValue(L"Age", strAge);

		// Insert values into the list control
		iRec = m_ListControl.InsertItem(0,strID,0);
		m_ListControl.SetItemText(0,1,strName);
		m_ListControl.SetItemText(0, 2, strAge);

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
}

void TestSQLDatabase::ResetListControl() {
	m_ListControl.DeleteAllItems();
	int iNbrOfColumns;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_ListControl.GetDlgItem(0);
	if (pHeader) {
		//iNbrOfColumns = pHeader→GetItemCount();
		iNbrOfColumns = m_ListControl.GetItemCount();
	}
	for (int i = iNbrOfColumns; i >= 0; i--) {
		m_ListControl.DeleteColumn(i);
	}
}