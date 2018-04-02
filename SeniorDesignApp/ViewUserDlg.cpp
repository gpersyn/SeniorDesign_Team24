// AddSensorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "ViewUserDlg.h"
#include "afxdialogex.h"
//For Database
#include "odbcinst.h"
#include "afxdb.h"


// CAddSensorDlg dialog

IMPLEMENT_DYNAMIC(ViewUserDlg, CDialogEx)

ViewUserDlg::ViewUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_VIEW_USERS, pParent)
{

}

ViewUserDlg::~ViewUserDlg()
{
}

void ViewUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VIEW_USERS, m_Database_View);
}


BEGIN_MESSAGE_MAP(ViewUserDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &ViewUserDlg::OnBnClickedButtonRefresh)
END_MESSAGE_MAP()


// CAddSensorDlg message handlers

void ViewUserDlg::OnBnClickedButtonRefresh()
{
	CDatabase database;
	CString SqlString;
	CString strID, strUserName, strUserType, strFirstName, strLastName, strPhoneNumber, strEmailAddress;
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
	SqlString = "SELECT ID, UserName, UserType, FirstName, LastName, PhoneNumber, EmailAddress " "FROM Users";

	// Execute the query

	recset.Open(CRecordset::forwardOnly,SqlString,CRecordset::readOnly);
	// Reset List control if there is any data
	ResetListControl();
	// populate Grids
	ListView_SetExtendedListViewStyle(m_Database_View,LVS_EX_GRIDLINES);

	//m_ListControl.InsertColumn(0, L"Name", LVCFMT_LEFT, 100);
	// Column width and heading
	m_Database_View.InsertColumn(0,L"ID",LVCFMT_LEFT,-1,0);
	m_Database_View.InsertColumn(1,L"User Name",LVCFMT_LEFT,-1,1);
	m_Database_View.InsertColumn(2, L"User Type", LVCFMT_LEFT, -1, 1);
	m_Database_View.InsertColumn(3, L"First Name", LVCFMT_LEFT, -1, 1);
	m_Database_View.InsertColumn(4, L"Last Name", LVCFMT_LEFT, -1, 1);
	m_Database_View.InsertColumn(5, L"Phone Number", LVCFMT_LEFT, -1, 1);
	m_Database_View.InsertColumn(6, L"Email Address", LVCFMT_LEFT, -1, 1);
	m_Database_View.SetColumnWidth(0, 50);
	m_Database_View.SetColumnWidth(1, 100);
	m_Database_View.SetColumnWidth(2, 100);
	m_Database_View.SetColumnWidth(3, 100);
	m_Database_View.SetColumnWidth(4, 100);
	m_Database_View.SetColumnWidth(5, 100);
	m_Database_View.SetColumnWidth(6, 200);

	// Loop through each record
	while (!recset.IsEOF()) {
		// Copy each column into a variable
		recset.GetFieldValue(L"ID",strID);
		recset.GetFieldValue(L"UserName", strUserName);
		recset.GetFieldValue(L"UserType", strUserType);
		recset.GetFieldValue(L"FirstName", strFirstName);
		recset.GetFieldValue(L"LastName", strLastName);
		recset.GetFieldValue(L"PhoneNumber", strPhoneNumber);
		recset.GetFieldValue(L"EmailAddress", strEmailAddress);

		// Insert values into the list control
		iRec = m_Database_View.InsertItem(0,strID,0);
		m_Database_View.SetItemText(0,1, strUserName);
		m_Database_View.SetItemText(0, 2, strUserType);
		m_Database_View.SetItemText(0, 3, strFirstName);
		m_Database_View.SetItemText(0, 4, strLastName);
		m_Database_View.SetItemText(0, 5, strPhoneNumber);
		m_Database_View.SetItemText(0, 6, strEmailAddress);

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

void ViewUserDlg::ResetListControl() {
	m_Database_View.DeleteAllItems();
	int iNbrOfColumns;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_Database_View.GetDlgItem(0);
	if (pHeader) {
		//iNbrOfColumns = pHeader→GetItemCount();
		iNbrOfColumns = m_Database_View.GetItemCount();
	}
	for (int i = iNbrOfColumns; i >= 0; i--) {
		m_Database_View.DeleteColumn(i);
	}
}