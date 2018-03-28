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
}


BEGIN_MESSAGE_MAP(TestSQLDatabase, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_DATABASE_TEST, &TestSQLDatabase::OnBnClickedButtonWriteDatabaseTest)
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
