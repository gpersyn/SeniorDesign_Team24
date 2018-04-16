#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "ViewAlertsDlg.h"
#include "afxdialogex.h"
//For Database
#include "odbcinst.h"
#include "afxdb.h"
CDatabase database_Alerts;

// CAddSensorDlg dialog

IMPLEMENT_DYNAMIC(ViewAlertsDlg, CDialogEx)

ViewAlertsDlg::ViewAlertsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_VIEW_ALERTS, pParent)
{
	CString sDriver = L"SQL Server";
	CString sDsn;
	CString sMc = L"GARRETT-DESKTOP";
	CString sFile = L"AppTest1";
	int iRec = 0;

	// Build ODBC connection string
	sDsn.Format(L"ODBC;Driver={%s};Server=%s;Database=%s;Trusted_Connection=yes", sDriver, sMc, sFile);

	// Open the database
	database_Alerts.Open(NULL, false, false, sDsn);

}

ViewAlertsDlg::~ViewAlertsDlg()
{
	// Close the database
	database_Alerts.Close();
}

void ViewAlertsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ALERTS, m_ViewAlerts);

	// Column width and heading
	m_ViewAlerts.InsertColumn(0, L"ErrorCode", LVCFMT_LEFT, -1, 0);
	m_ViewAlerts.InsertColumn(1, L"SensorID", LVCFMT_LEFT, -1, 1);
	m_ViewAlerts.InsertColumn(2, L"Time", LVCFMT_LEFT, -1, 1);
	m_ViewAlerts.InsertColumn(3, L"ErrorInfo", LVCFMT_LEFT, -1, 1);
	m_ViewAlerts.SetColumnWidth(0, 100);
	m_ViewAlerts.SetColumnWidth(1, 100);
	m_ViewAlerts.SetColumnWidth(2, 150);
	m_ViewAlerts.SetColumnWidth(3, 400);
	OnBnClickedButtonRefresh();
}


BEGIN_MESSAGE_MAP(ViewAlertsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &ViewAlertsDlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_ALERTS, &ViewAlertsDlg::OnBnClickedButtonClearAlerts)
END_MESSAGE_MAP()


// CAddSensorDlg message handlers




void ViewAlertsDlg::OnBnClickedButtonRefresh()
{
	CString SqlString;
	CString ErrorCode;
	CString SensorID;
	CString Time;
	CString ErrorInfo;

	// Allocate the recordset
	CRecordset recset(&database_Alerts);

	// Build the SQL statement
	SqlString = "SELECT ErrorCode, SensorID, Time, ErrorInfo " "FROM Alerts";

	// Execute the query

	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	// Reset List control if there is any data
	ResetListControl();
	// populate Grids
	ListView_SetExtendedListViewStyle(m_ViewAlerts, LVS_EX_GRIDLINES);

	// Loop through each record
	while (!recset.IsEOF()) {
		// Copy each column into a variable
		recset.GetFieldValue(L"ErrorCode", ErrorCode);
		recset.GetFieldValue(L"SensorID", SensorID);
		recset.GetFieldValue(L"Time", Time);
		recset.GetFieldValue(L"ErrorInfo", ErrorInfo);

		// Insert values into the list control
		m_ViewAlerts.InsertItem(0, ErrorCode, 0);
		m_ViewAlerts.SetItemText(0, 1, SensorID);
		m_ViewAlerts.SetItemText(0, 2, Time);
		m_ViewAlerts.SetItemText(0, 3, ErrorInfo);

		// goto next record
		recset.MoveNext();
	}

}

void ViewAlertsDlg::ResetListControl() {
	m_ViewAlerts.DeleteAllItems();
	int iNbrOfColumns;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_ViewAlerts.GetDlgItem(0);
	if (pHeader) {
		//iNbrOfColumns = pHeader→GetItemCount();
		iNbrOfColumns = m_ViewAlerts.GetItemCount();
	}
	for (int i = iNbrOfColumns-1; i >= 0; i--) {
		m_ViewAlerts.DeleteColumn(i);
	}
}

void ViewAlertsDlg::OnBnClickedButtonClearAlerts() //Clears Alerts
{
	CString SqlString;
	// Allocate the recordset

	// Build the SQL statement
	SqlString = "DELETE FROM Alerts";

	// Execute the query
	database_Alerts.ExecuteSQL(SqlString);

	OnBnClickedButtonRefresh(); //refresh table
}
