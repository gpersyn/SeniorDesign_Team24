// PrimeForm.cpp : implementation file
//

#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "PrimeForm.h"

//Custom Dialogs
#include "AddUserDlg.h"
#include "AddSensorDlg.h"
#include "SerialDebugDlg.h"
#include "TestSensorDlg.h"
#include "ConfigSensorDlg.h"
#include "TestSQLDatabase.h"
#include "DeleteUserDlg.h"
#include "ViewUserDlg.h"
#include "DeleteSensorDlg.h"
#include "ViewAlertsDlg.h"
#include "TestSMSDlg.h"

//For Serial Stuff
#include "SerialHeader.h" 
SerialPort arduino(port);

//For Database
#include "odbcinst.h"
#include "afxdb.h"

//SMS
#include <stdio.h>
#include <curl/curl.h>
#define MAX_TWILIO_MESSAGE_SIZE 10000

// CPrimeForm

IMPLEMENT_DYNCREATE(CPrimeForm, CFormView)

CPrimeForm::CPrimeForm()
	: CFormView(IDD_PRIMEFORM)
{

}

CPrimeForm::~CPrimeForm()
{
}

void CPrimeForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VIEW_SENSORS, mViewSensors);
	//DDX_Control(pDX, IDC_LIST_VIEW_ALERTS, m_ViewAlerts);
}

BEGIN_MESSAGE_MAP(CPrimeForm, CFormView)
	ON_COMMAND(ID_USERS_VIEWUSERS, &CPrimeForm::OnUsersViewusers)
	ON_COMMAND(ID_ADD_USER, &CPrimeForm::OnAddUser)
	ON_COMMAND(ID_USERS_DELETEUSER, &CPrimeForm::OnUsersDeleteuser)
	ON_COMMAND(ID_BUTTON_REFRESH, &CPrimeForm::OnButtonRefresh)
	ON_COMMAND(ID_ADD_SENSOR, &CPrimeForm::OnAddSensor)
	ON_COMMAND(ID_SENSORS_DELETEUSER, &CPrimeForm::OnSensorsDeleteuser)
	ON_COMMAND(ID_SENSORS_CONFIGURESENSOR, &CPrimeForm::OnSensorsConfiguresensor)
	ON_COMMAND(ID_SENSORS_TESTSENSOR, &CPrimeForm::OnSensorsTestsensor)
	ON_COMMAND(ID_BUTTON_ALERTS, &CPrimeForm::OnButtonAlerts)
	ON_COMMAND(ID_BUTTON_USERS, &CPrimeForm::OnButtonUsers)
	ON_COMMAND(ID_DEBUG_SMSTEST, &CPrimeForm::OnDebugSmstest)
	ON_COMMAND(ID_DEBUG_LEDSWITCH, &CPrimeForm::OnDebugLedswitch)
END_MESSAGE_MAP()


// CPrimeForm diagnostics

#ifdef _DEBUG
void CPrimeForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPrimeForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPrimeForm message handlers

//USER DIALOGS---------------------------------------------------------------------------------------------------------------
void CPrimeForm::OnUsersViewusers()
{
	ViewUserDlg ViewUser;
	ViewUser.DoModal();
}

void CPrimeForm::OnAddUser()
{
	CAddUserDlg dlgAddUser; //Call Add User Dialog Box
	if (dlgAddUser.DoModal() == true) {
		int temp_UserID = dlgAddUser.m_UserID;
		CString temp_UserName = dlgAddUser.m_UserName;
		CString temp_UserType;
		if (dlgAddUser.m_ADMIN_ON) {
			temp_UserType = L"ADMIN";
		}
		else {
			temp_UserType = L"GENERAL";
		}
		CString temp_FirstName = dlgAddUser.m_FirstName;
		CString temp_LastName = dlgAddUser.m_LastName;
		long temp_PhoneNumber = dlgAddUser.m_PhoneNumber;
		CString temp_Email_Address = dlgAddUser.m_Email;
		CString temp_User_Password = dlgAddUser.m_UserPassword;

		//Add User to database
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
		//SqlString = "INSERT INTO Users (ID,UserName,UserType,FirstName,LastName,PhoneNumber,EmailAddress) VALUES (1,'Cowboysfan82','ADMIN','John','Packer',210456789,'Cowboysfan82@yahoo.com')";
		SqlString.Format(L"INSERT INTO Users (ID,UserName,UserType,FirstName,LastName,PhoneNumber,EmailAddress,Passwords) VALUES (%d,'%s','%s','%s','%s',%u,'%s','%s')", temp_UserID, temp_UserName, temp_UserType, temp_FirstName, temp_LastName, temp_PhoneNumber, temp_Email_Address, temp_User_Password);
		//SqlString.Format(L"DELETE Users where ID=%d",Temp_UserID);
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
}


void CPrimeForm::OnUsersDeleteuser()
{
	DeleteUserDlg DeleteUser;
	if (DeleteUser.DoModal() == true) {
		int Temp_UserID = DeleteUser.m_UserID;

		//Delete User from database
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
		//SqlString = "INSERT INTO Users (ID,UserName,UserType,FirstName,LastName,PhoneNumber,EmailAddress) VALUES (1,'Cowboysfan82','ADMIN','John','Packer',210456789,'Cowboysfan82@yahoo.com')";
		//SqlString.Format(L"INSERT INTO Users (ID,UserName,UserType,FirstName,LastName,PhoneNumber,EmailAddress) VALUES (%d,'%s','ADMIN','John','Packer',210456789,'Cowboysfan82@yahoo.com')", m_UserID,L"Johny");
		SqlString.Format(L"DELETE Users where ID=%d",Temp_UserID);
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
}

//SENSOR DIALOGS---------------------------------------------------------------------------------------------
void CPrimeForm::OnAddSensor()
{
	int SensorID;
	CString BuildingName;
	int RoomNumber;
	CAddSensorDlg dlgAddSensor; //Call Add Sensor Dialog Box
	if (dlgAddSensor.DoModal() == true) { //Only If the clicked the ok box
		SensorID = dlgAddSensor.m_Sensor_ID;
		BuildingName = dlgAddSensor.m_Building_Name;
		RoomNumber = dlgAddSensor.m_Room_Number;

		//Add Sensor to database
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
		//SqlString = "INSERT INTO Users (ID,UserName,UserType,FirstName,LastName,PhoneNumber,EmailAddress) VALUES (1,'Cowboysfan82','ADMIN','John','Packer',210456789,'Cowboysfan82@yahoo.com')";
		SqlString.Format(L"INSERT INTO Sensors (ID ,Status, PropaneValue, MethaneValue, COValue, BuildingName, RoomNumber) VALUES (%d,'WORKING','0','0','0','%s',%d)", SensorID, BuildingName, RoomNumber);
		//SqlString.Format(L"DELETE Users where ID=%d",Temp_UserID);
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
}


void CPrimeForm::OnSensorsDeleteuser() //This is acctually to delete Sensor not User
{
	DeleteSensorDlg DeleteSensor;
	if (DeleteSensor.DoModal() == true) {
		int Temp_SensorID = DeleteSensor.m_SensorID;

		//Delete User from database
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
			SqlString.Format(L"DELETE Sensors where ID=%d", Temp_SensorID);
			database.ExecuteSQL(SqlString);
			// Close the database
			database.Close();
		}CATCH(CDBException, e) {
			// If a database exception occured, show error msg
			//AfxMessageBox(L"Database error: " + e→m_strError);
		}
		END_CATCH;
		OnButtonRefresh();
	}
}


void CPrimeForm::OnSensorsConfiguresensor()
{
	ConfigSensorDlg ConfigureSensorDialog; //Call Config Sensor Dialog Box
	if (ConfigureSensorDialog.DoModal() == true) {

		/*//Use Return Values
		CString test3 = ConfigureSensorDialog.m_Config_SensorID;
		int test2 = ConfigureSensorDialog.Methane_Threshold_Value;

		CStringA test1 = "Hi";
		char *OutputSerial;
		OutputSerial = test1.GetBuffer(test1.GetLength()); //convert to char array

		arduino.writeSerialPort(OutputSerial, DataWidth);*/
	}
}


void CPrimeForm::OnSensorsTestsensor()
{
	TestSensorDlg TestSensorDialog; //Call Test Sensor Dialog Box
	TestSensorDialog.DoModal();
}

//ToolBar Dialog-------------------------------------------------------------------------------------------------

void CPrimeForm::OnButtonAlerts() //When alert button (on toolbar) is pressed
{
	ViewAlertsDlg AlertsDialog;
	AlertsDialog.DoModal();
}

void CPrimeForm::OnButtonUsers()
{
	ViewUserDlg ViewUser;
	ViewUser.DoModal();
}


//Debug Dialog-------------------------------------------------------------------------------------------------
void CPrimeForm::OnDebugSmstest()
{
	TestSMSDlg TestSMS;
	if (TestSMS.DoModal() == true){ //Send SMS
		char const* message = "This is a SMS test!";
		int r = sendSMS(message);
	}
}

void CPrimeForm::OnDebugLedswitch()
{
	if (arduino.isConnected()) {
		/*CString data = _T("ACK");
		char *charArray = new char[data.GetLength() + 1];
		copy(data.Mid(0,0), data.Mid(data.GetLength() - 1, data.GetLength() - 1), charArray);
		charArray[data.GetLength()] = '\n';*/

		char *InputArray = "ACK";

		arduino.writeSerialPort(InputArray, DataWidth);
		arduino.readSerialPort(incomingData, DataWidth);
	}
}

//MainView Stuff-----------------------------------------------------------------------------------------------
void CPrimeForm::OnButtonRefresh()
{
	FillSensorTable();

}

void CPrimeForm::ResetListControl() {
	mViewSensors.DeleteAllItems();
	int iNbrOfColumns;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)mViewSensors.GetDlgItem(0);
	if (pHeader) {
		//iNbrOfColumns = pHeader→GetItemCount();
		iNbrOfColumns = mViewSensors.GetItemCount();
	}
	for (int i = iNbrOfColumns; i >= 0; i--) {
		mViewSensors.DeleteColumn(i);
	}
}

void CPrimeForm::FillSensorTable() {
	CDatabase database;
	CString SqlString;
	CString strID, strStatus, strPropaneValue, strMethaneValue, strCOValue, strBuildingName, strRoomNumber;
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

	//Sensor Table

	// Build the SQL statement
	SqlString = "SELECT ID, Status, PropaneValue, MethaneValue, COValue, BuildingName, RoomNumber " "FROM Sensors";

	// Execute the query
	recset.Open(CRecordset::forwardOnly,SqlString,CRecordset::readOnly);
	// Reset List control if there is any data
	ResetListControl();
	// populate Grids
	ListView_SetExtendedListViewStyle(mViewSensors,LVS_EX_GRIDLINES);

	//m_ListControl.InsertColumn(0, L"Name", LVCFMT_LEFT, 100);
	// Column width and heading
	mViewSensors.InsertColumn(0,L"ID",LVCFMT_LEFT,-1,0);
	mViewSensors.InsertColumn(1,L"Status",LVCFMT_LEFT,-1,1);
	mViewSensors.InsertColumn(2, L"Propane Value", LVCFMT_LEFT, -1, 1);
	mViewSensors.InsertColumn(3, L"Methane Value", LVCFMT_LEFT, -1, 1);
	mViewSensors.InsertColumn(4, L"CO Value", LVCFMT_LEFT, -1, 1);
	mViewSensors.InsertColumn(5, L"Building Name", LVCFMT_LEFT, -1, 1);
	mViewSensors.InsertColumn(6, L"Room Number", LVCFMT_LEFT, -1, 1);
	mViewSensors.SetColumnWidth(0, 50);
	mViewSensors.SetColumnWidth(1, 100);
	mViewSensors.SetColumnWidth(2, 100);
	mViewSensors.SetColumnWidth(3, 100);
	mViewSensors.SetColumnWidth(4, 100);
	mViewSensors.SetColumnWidth(5, 100);
	mViewSensors.SetColumnWidth(6, 100);

	// Loop through each record
	while (!recset.IsEOF()) {
		// Copy each column into a variable
		recset.GetFieldValue(L"ID",strID);
		recset.GetFieldValue(L"Status", strStatus);
		recset.GetFieldValue(L"PropaneValue", strPropaneValue);
		recset.GetFieldValue(L"MethaneValue", strMethaneValue);
		recset.GetFieldValue(L"COValue", strCOValue);
		recset.GetFieldValue(L"BuildingName", strBuildingName);
		recset.GetFieldValue(L"RoomNumber", strRoomNumber);

		// Insert values into the list control
		iRec = mViewSensors.InsertItem(0,strID,0);
		mViewSensors.SetItemText(0,1, strStatus);
		mViewSensors.SetItemText(0, 2, strPropaneValue);
		mViewSensors.SetItemText(0, 3, strMethaneValue);
		mViewSensors.SetItemText(0, 4, strCOValue);
		mViewSensors.SetItemText(0, 5, strBuildingName);
		mViewSensors.SetItemText(0, 6, strRoomNumber);

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


//SMS Functions-------------------------------------------------------------------------------
size_t _twilio_null_write(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	return size * nmemb;
}

int CPrimeForm::sendSMS(char const* message) {



	// See: https://www.twilio.com/docs/api/rest/sending-messages for
	// information on Twilio body size limits.
	if (strlen(message) > 1600) {
		fprintf(stderr, "SMS send failed.\n"
			"Message body must be less than 1601 characters.\n"
			"The message had %zu characters.\n", strlen(message));
		return -1;
	}

	CURL *curl;
	//CURLcode res;
	CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	char url[MAX_TWILIO_MESSAGE_SIZE];
	snprintf(url,
		sizeof(url),
		"%s%s%s",
		"https://api.twilio.com/2010-04-01/Accounts/",
		account_sid,
		"/Messages");

	char parameters[MAX_TWILIO_MESSAGE_SIZE];

	snprintf(parameters,
		sizeof(parameters),
		"%s%s%s%s%s%s",
		"To=",
		to_number,
		"&From=",
		from_number,
		"&Body=",
		message);


	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters);
	curl_easy_setopt(curl, CURLOPT_USERNAME, account_sid);
	curl_easy_setopt(curl, CURLOPT_PASSWORD, auth_token);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

	if (!verbose) {
		curl_easy_setopt(curl,
			CURLOPT_WRITEFUNCTION,
			_twilio_null_write);
	}

	res = curl_easy_perform(curl);


	long http_code = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

	if (res != CURLE_OK) {
		if (verbose) {
			fprintf(stderr,
				"SMS send failed: %s.\n",
				curl_easy_strerror(res));
		}
		return -1;
	}
	else if (http_code != 200 && http_code != 201) {
		if (verbose) {
			fprintf(stderr,
				"SMS send failed, HTTP Status Code: %ld.\n",
				http_code);
		}
		return -1;
	}
	else {
		if (verbose) {
			fprintf(stderr,
				"SMS sent successfully!\n");
		}
		return 0;
	}

	curl_easy_cleanup(curl);
}


