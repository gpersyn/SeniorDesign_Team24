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

//Database
#include "DatabaseInitialization.h"
CDatabase database;
CString sDriver;
CString sDsn;
CString sMc;
CString sFile;
// You must change above path if it's different
int iRec;

//SMS
#include <stdio.h>
#include <curl/curl.h>
#define MAX_TWILIO_MESSAGE_SIZE 10000

//for time
#include <ctime>

// CPrimeForm

IMPLEMENT_DYNCREATE(CPrimeForm, CFormView)

//Constructor
CPrimeForm::CPrimeForm()
	: CFormView(IDD_PRIMEFORM)
{
	sDriver = L"SQL Server";
	sMc = L"GARRETT-DESKTOP";
	sFile = L"AppTest1";
	iRec = 0;
	// Build ODBC connection string
	sDsn.Format(L"ODBC;Driver={%s};Server=%s;Database=%s;Trusted_Connection=yes", sDriver, sMc, sFile);
	// Open the database
	database.Open(NULL, false, false, sDsn);

	//Initialize variables
	TestSensorID = 0;
	TestCount = 0;
	updateCount = 5;

}

CPrimeForm::~CPrimeForm()
{
	database.Close();
}

void CPrimeForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VIEW_SENSORS, mViewSensors);
	//DDX_Control(pDX, IDC_LIST_VIEW_ALERTS, m_ViewAlerts);

	// Column width and heading
	mViewSensors.InsertColumn(0, L"ID", LVCFMT_LEFT, -1, 0);
	mViewSensors.InsertColumn(1, L"Status", LVCFMT_LEFT, -1, 1);
	mViewSensors.InsertColumn(2, L"Propane Value", LVCFMT_LEFT, -1, 1);
	mViewSensors.InsertColumn(3, L"Methane Value", LVCFMT_LEFT, -1, 1);
	mViewSensors.InsertColumn(4, L"CO Value", LVCFMT_LEFT, -1, 1);
	mViewSensors.InsertColumn(5, L"Building Name", LVCFMT_LEFT, -1, 1);
	mViewSensors.InsertColumn(6, L"Room Number", LVCFMT_LEFT, -1, 1);
	mViewSensors.InsertColumn(7, L"Propane Threshold", LVCFMT_LEFT, -1, 1);
	mViewSensors.InsertColumn(8, L"Methane Threshold", LVCFMT_LEFT, -1, 1);
	mViewSensors.InsertColumn(9, L"CO Threshold", LVCFMT_LEFT, -1, 1);
	mViewSensors.SetColumnWidth(0, 50);
	mViewSensors.SetColumnWidth(1, 100);
	mViewSensors.SetColumnWidth(2, 100);
	mViewSensors.SetColumnWidth(3, 100);
	mViewSensors.SetColumnWidth(4, 100);
	mViewSensors.SetColumnWidth(5, 100);
	mViewSensors.SetColumnWidth(6, 100);
	mViewSensors.SetColumnWidth(7, 110);
	mViewSensors.SetColumnWidth(8, 110);
	mViewSensors.SetColumnWidth(9, 110);
	FillSensorTable();
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
	ON_COMMAND(ID_SENSORS_UPDATESENSORS, &CPrimeForm::OnSensorsUpdatesensors)
	ON_COMMAND(ID_ALERTS_VIEWALERTS, &CPrimeForm::OnAlertsViewalerts)
	ON_WM_TIMER()
END_MESSAGE_MAP()

//Timer Stuff
void CPrimeForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//Timer Stuff
	SetTimer(1, 1000, NULL);

}

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
	//Model
	//ViewUserDlg ViewUser;
	//ViewUser.DoModal();

	//Modeless
	ViewUserDlg *dlgViewUser = new ViewUserDlg(this);
	dlgViewUser->Create(IDD_DIALOG_VIEW_USERS, GetDesktopWindow());
	dlgViewUser->ShowWindow(SW_SHOW);
}

void CPrimeForm::OnAddUser()
{
	CAddUserDlg dlgAddUser; //Call Add User Dialog Box
	if (dlgAddUser.DoModal() == true) {
		int temp_UserID = dlgAddUser.m_UserID;
		CString temp_UserName = dlgAddUser.m_UserName;
		CString temp_UserType;
		if (dlgAddUser.m_ADMIN_ON == true) {
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
		CString SqlString;
		CString strID, strName, strAge;

		//Database Code
		sDsn.Format(L"ODBC;Driver={%s};Server=%s;Database=%s;Trusted_Connection=yes", sDriver, sMc, sFile);
		SqlString.Format(L"INSERT INTO Users (ID,UserName,UserType,FirstName,LastName,PhoneNumber,EmailAddress,Passwords) VALUES (%d,'%s','%s','%s','%s',%u,'%s','%s')", temp_UserID, temp_UserName, temp_UserType, temp_FirstName, temp_LastName, temp_PhoneNumber, temp_Email_Address, temp_User_Password);
		database.ExecuteSQL(SqlString);
	}
}


void CPrimeForm::OnUsersDeleteuser()
{
	DeleteUserDlg DeleteUser;
	if (DeleteUser.DoModal() == true) {
		int Temp_UserID = DeleteUser.m_UserID;
		CString SqlString;
		CString strID, strName, strAge;

		//Database stuff
		sDsn.Format(L"ODBC;Driver={%s};Server=%s;Database=%s;Trusted_Connection=yes", sDriver, sMc, sFile);
		SqlString.Format(L"DELETE Users where ID=%d",Temp_UserID);
		database.ExecuteSQL(SqlString);
	}
}

//SENSOR DIALOGS---------------------------------------------------------------------------------------------
void CPrimeForm::OnAddSensor()
{
	int SensorID;
	CString BuildingName;
	int RoomNumber, PropaneThreshold, MethaneThreshold, COThreshold;
	CAddSensorDlg dlgAddSensor; //Call Add Sensor Dialog Box
	if (dlgAddSensor.DoModal() == true) { //Only If the clicked the ok box
		SensorID = dlgAddSensor.m_Sensor_ID;
		BuildingName = dlgAddSensor.m_Building_Name;
		RoomNumber = dlgAddSensor.m_Room_Number;
		PropaneThreshold = dlgAddSensor.m_Propane_Threshold;
		MethaneThreshold = dlgAddSensor.m_Methane_Threshold;
		COThreshold = dlgAddSensor.m_CO_Threshold;
		CString SqlString;
		CString strID, strName, strAge;
		SqlString.Format(L"INSERT INTO Sensors (ID ,Status, PropaneValue, MethaneValue, COValue, BuildingName, RoomNumber, PropaneThreshold, MethaneThreshold, COThreshold) VALUES (%d,'WORKING','0','0','0','%s',%d,%d,%d,%d)", SensorID, BuildingName, RoomNumber, PropaneThreshold, MethaneThreshold, COThreshold);

		database.ExecuteSQL(SqlString); //send query
		FillSensorTable(); //Refresh sensor table in primeview
	}
}


void CPrimeForm::OnSensorsDeleteuser() //This is acctually to delete Sensor not User
{
	DeleteSensorDlg DeleteSensor;
	if (DeleteSensor.DoModal() == true) {
		int Temp_SensorID = DeleteSensor.m_SensorID;

		//Delete User from database
		CString SqlString;
		CString strID, strName, strAge;

		SqlString.Format(L"DELETE Sensors where ID=%d", Temp_SensorID);
		database.ExecuteSQL(SqlString);
		OnButtonRefresh();
	}
}


void CPrimeForm::OnSensorsConfiguresensor()
{
	int SensorID, PropaneThreshold, MethaneThreshold, COThreshold;
	bool SensorState;
	CString strSensorState;
	int intSensorState;
	ConfigSensorDlg ConfigureSensorDialog; //Call Config Sensor Dialog Box
	if (ConfigureSensorDialog.DoModal() == true) {

		//Database Stuff
		SensorID = ConfigureSensorDialog.m_SensorID;
		PropaneThreshold = ConfigureSensorDialog.m_ProThresh;
		MethaneThreshold = ConfigureSensorDialog.m_Meth_Thresh;
		COThreshold = ConfigureSensorDialog.m_CO_Thresh;
		SensorState = ConfigureSensorDialog.Sensor_State;
		if (SensorState == true) {
			strSensorState = L"WORKING";
			intSensorState = 1; //Sensor on
		}
		else {
			strSensorState = L"OFF";
			intSensorState = 0; //Sensor off
		}
		//Update Sensor
		CString SqlString;
		//update threshold
		SqlString.Format(L"UPDATE Sensors SET PropaneThreshold = %d Where ID = %d", PropaneThreshold, SensorID); //update Propane
		database.ExecuteSQL(SqlString);
		SqlString.Format(L"UPDATE Sensors SET MethaneThreshold = %d Where ID = %d", MethaneThreshold, SensorID);//update Methane
		database.ExecuteSQL(SqlString);
		SqlString.Format(L"UPDATE Sensors SET COThreshold = %d Where ID = %d", COThreshold, SensorID);//update CO
		database.ExecuteSQL(SqlString);
		//update sensor status
		SqlString.Format(L"UPDATE Sensors SET Status = '%s' Where ID = %d", strSensorState, SensorID); //update Propane
		database.ExecuteSQL(SqlString);

		//Serial Stuff
		std:string tempInput = "C"; //This is the control bits (C=config)

		std::string tempState = std::to_string(intSensorState);
		tempInput += tempState;

		int tempID = ConfigureSensorDialog.m_SensorID;
		std::string temp = std::to_string(tempID);
		if (tempID < 10) { //add extra zeros to id if id is only a single digit
			tempInput += "00";
		}
		else if (tempID < 99) { //if id has double digits
			tempInput += "0";
		}
		tempInput += temp; //add sensor id to control bits
		const char *InputArray = tempInput.c_str(); 
		arduino.writeSerialPort(InputArray, DataWidth);
	}
}


void CPrimeForm::OnSensorsTestsensor()
{
	TestSensorDlg TestSensorDialog; //Call Test Sensor Dialog Box
	if (TestSensorDialog.DoModal() == true) {
		if (TestSensorID == 0) { //if your not already testing a sensor
		std:string tempInput = "T"; //This is the control bits (T=Test)
		//CONTOL BITS: '00' = read, '01' = config, '10' = test
			int tempID = TestSensorDialog.m_SensorID;
			std::string temp = std::to_string(tempID);
			if (tempID < 10) { //add extra zeros to id if id is only a single digit
				tempInput += "00";
			}
			else if (tempID < 99) { //if id has double digits
				tempInput += "0";
			}
			tempInput += temp; //add sensor id to control bits
			const char *InputArray = tempInput.c_str();
			arduino.writeSerialPort(InputArray, DataWidth);

			TestSensorID = tempID;
			TestCount = 10; //wait 30 seconds for response before ending test
			CString SqlString;
			SqlString.Format(L"UPDATE Sensors SET Status = 'TESTING' Where ID = %d", TestSensorID); //update Sensor Status
			database.ExecuteSQL(SqlString);
		}
	}
}

void CPrimeForm::OnSensorsUpdatesensors()
{
	//Character arrays to store incoming messages
	char ControlBits[2]{ 1, 1};
	char SensorIDBits[3]{ 0, 0, 0 };
	char PropaneBits[3]{ 0, 0, 0 };
	char MethaneBits[3]{ 0, 0, 0 };
	char COBits[3]{ 0, 0, 0 };
	char inData[DataWidth];
	//Converted data
	CString sensorStatus; //Sensors old status
	int Control;
	int SensorID;
	int Propane;
	int Methane;
	int CO;
	//Tresholds
	CString strPropaneThreshold, strMethaneThreshold, strCOThreshold, Building;
	int PropaneThreshold, MethaneThreshold, COThreshold;
	bool overThresh = false; //tells if any sensor is overthreshold.
	//Message
	std::string MessageTemp = "WARNING: Dangerous gas leak in building ";
	std::string MessageTemp2 = ". Please Evacuate immediately!";
	std::time_t result = std::time(nullptr);
	std::string strCurrentTime = std::ctime(&result);
	CString CurrentTime(strCurrentTime.c_str());

	for (int i = 0; i < 5; i++) {
		arduino.readSerialPort(inData, DataWidth);
		//find start of message
		if (inData[0] == 'S') {
			//Read serial input
			for (int j = 0; j <= 1; j++) {
				ControlBits[j] = inData[1 + j];
			}
			for (int j = 0; j <= 2; j++) {
				SensorIDBits[j] = inData[3 + j];
				PropaneBits[j] = inData[6 + j];
				MethaneBits[j] = inData[9 + j];
				COBits[j] = inData[12 + j];
			}

			//convert to ints
			Control = atoi(ControlBits);
			SensorID = atoi(SensorIDBits);
			Propane = atoi(PropaneBits);
			Methane = atoi(MethaneBits);
			CO = atoi(COBits);

			//check if right string length


			//Check if sensor id exists
			int maxInt = MaxSensorID();
			if (SensorID > maxInt) {
				return;
			}

			//check if gas readings are right
			if ((Propane < 5) || (Propane > 150)) {
				return;
			}
			else if ((Methane < 5) || (Methane > 150)) {
				return;
			}
			else if ((CO < 5) || (CO > 150)) {
				return;
			}

			//Update Sensor
			CString SqlString;

			SqlString.Format(L"UPDATE Sensors SET PropaneValue = %d Where ID = %d", Propane, SensorID); //update Propane
			database.ExecuteSQL(SqlString);
			SqlString.Format(L"UPDATE Sensors SET MethaneValue = %d Where ID = %d", Methane, SensorID);//update Methane
			database.ExecuteSQL(SqlString);
			SqlString.Format(L"UPDATE Sensors SET COValue = %d Where ID = %d", CO, SensorID);//update CO
			database.ExecuteSQL(SqlString);

			//read thresholds from database

			// Allocate the recordset
			CRecordset recset(&database);
			// Build the SQL statement
			SqlString.Format(L"SELECT Status, BuildingName, PropaneThreshold, MethaneThreshold, COThreshold" " FROM Sensors" " Where ID = %d", SensorID);
			// Execute the query
			recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
			recset.GetFieldValue(L"Status", sensorStatus);
			recset.GetFieldValue(L"BuildingName", Building);
			recset.GetFieldValue(L"PropaneThreshold", strPropaneThreshold);
			recset.GetFieldValue(L"MethaneThreshold", strMethaneThreshold);
			recset.GetFieldValue(L"COThreshold", strCOThreshold);

			//convert from CStrings to need type
			PropaneThreshold = _ttoi(strPropaneThreshold);
			MethaneThreshold = _ttoi(strMethaneThreshold);
			COThreshold = _ttoi(strCOThreshold);
			CT2CA pszConvertedAnsiString(Building);
		std:string BuildingName(pszConvertedAnsiString);

			//Compare Threshold to actual value
			if (Propane > PropaneThreshold) {
				SqlString.Format(L"UPDATE Sensors SET Status = 'ERROR' Where ID = %d", SensorID); //update Sensor Status
				database.ExecuteSQL(SqlString);
				if (sensorStatus != "ERROR") { //This makes sure it only sends one alert message per incident
					SqlString.Format(L"INSERT INTO Alerts (ErrorCode ,SensorID, Time, ErrorInfo ) VALUES (1001, %d, '%s', 'Propane value of %d is to high')", SensorID, CurrentTime, Propane); //update Alert Status
					database.ExecuteSQL(SqlString);
				}

				overThresh = true;
			}
			if (Methane > MethaneThreshold) {
				SqlString.Format(L"UPDATE Sensors SET Status = 'ERROR' Where ID = %d", SensorID); //update Sensor Status
				database.ExecuteSQL(SqlString);

				if (sensorStatus != "ERROR") {
					SqlString.Format(L"INSERT INTO Alerts (ErrorCode ,SensorID, Time, ErrorInfo ) VALUES (1002, %d, '%s', 'Methane value of %d is to high')", SensorID, CurrentTime, Methane); //update Alert Status
					database.ExecuteSQL(SqlString);
				}

				overThresh = true;
			}
			if (CO > COThreshold) {
				SqlString.Format(L"UPDATE Sensors SET Status = 'ERROR' Where ID = %d", SensorID); //update Sensor Status
				database.ExecuteSQL(SqlString);

				if (sensorStatus != "ERROR") {
					SqlString.Format(L"INSERT INTO Alerts (ErrorCode ,SensorID, Time, ErrorInfo ) VALUES (1003, %d, '%s', 'CO value of %d is to high')", SensorID, CurrentTime, CO); //update Alert Status
					database.ExecuteSQL(SqlString);
				}

				overThresh = true;
			}

			if (overThresh == true) { //A gas is over the threshold
				if (sensorStatus == "WORKING") { //Send SMS Alert
					MessageTemp += BuildingName;//Construct Message
					MessageTemp += MessageTemp2;
					char const* message3 = MessageTemp.c_str();
					int y = sendSMS(message3); //send message
				}
			}
			else { //Gas isn't over the threshold
				if (sensorStatus == "ERROR") { //reset status
					SqlString.Format(L"UPDATE Sensors SET Status = 'WORKING' Where ID = %d", SensorID); //update Sensor Status
					database.ExecuteSQL(SqlString);
				}
			}

			//Test Sensor Code
			if (TestSensorID != 0) { //we are testing a sensor
				if (TestCount < 1) { //Sensor we are testing never responded
					SqlString.Format(L"UPDATE Sensors SET Status = 'ERROR' Where ID = %d", TestSensorID); //update Sensor Status
					database.ExecuteSQL(SqlString);
					SqlString.Format(L"INSERT INTO Alerts (ErrorCode ,SensorID, Time, ErrorInfo ) VALUES (1004, %d, '%s', 'Sensor not responding to test')", TestSensorID, CurrentTime); //update Alert Status
					database.ExecuteSQL(SqlString);
					TestSensorID = 0; //end test
				}
				else { //Still Waiting for response
					TestCount = TestCount - 1;
				}
			}




			//refresh sensor table
			OnButtonRefresh();
		}
		else if (inData[0] == 'P') { //if sensor is pinging us back after receiving our test ping
			CString SqlString;
			SqlString.Format(L"UPDATE Sensors SET Status = 'WORKING' Where ID = %d", TestSensorID); //update Sensor Status
			database.ExecuteSQL(SqlString);
			TestSensorID = 0; //end test
		}
	}
}


//ToolBar Dialog-------------------------------------------------------------------------------------------------

void CPrimeForm::OnButtonAlerts() //When alert button (on toolbar) is pressed
{
	OnAlertsViewalerts();
}

void CPrimeForm::OnButtonUsers()
{
	OnUsersViewusers();
}


//Alerts-------------------------------------------------------------------------------------------------------

void CPrimeForm::OnAlertsViewalerts()
{
	//Model
	//ViewAlertsDlg AlertsDialog;
	//AlertsDialog.DoModal();

	//Modeless
	ViewAlertsDlg *AlertsDialog = new ViewAlertsDlg(this);
	AlertsDialog->Create(IDD_DIALOG_VIEW_ALERTS, GetDesktopWindow());
	AlertsDialog->ShowWindow(SW_SHOW);
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

		const char *InputArray = "ACK";

		arduino.writeSerialPort(InputArray, DataWidth);
		//arduino.readSerialPort(incomingData, DataWidth);
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
	for (int i = iNbrOfColumns-1; i >= 0; i--) { //the -1 prevents it from deleteing an extra column
		mViewSensors.DeleteColumn(i);
	}
}

void CPrimeForm::FillSensorTable() {
	CString SqlString;
	CString strID, strStatus, strPropaneValue, strMethaneValue, strCOValue, strBuildingName, strRoomNumber, strPropaneThreshold, strMethaneThreshold, strCOThreshold;
	
	// Allocate the recordset
	CRecordset recset(&database);

	//Sensor Table

	// Build the SQL statement
	SqlString = "SELECT ID, Status, PropaneValue, MethaneValue, COValue, BuildingName, RoomNumber, PropaneThreshold, MethaneThreshold, COThreshold" " FROM Sensors";

	// Execute the query
	recset.Open(CRecordset::forwardOnly,SqlString,CRecordset::readOnly);
	// Reset List control if there is any data
	ResetListControl();
	// populate Grids
	ListView_SetExtendedListViewStyle(mViewSensors,LVS_EX_GRIDLINES);

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
		recset.GetFieldValue(L"PropaneThreshold", strPropaneThreshold);
		recset.GetFieldValue(L"MethaneThreshold", strMethaneThreshold);
		recset.GetFieldValue(L"COThreshold", strCOThreshold);

		// Insert values into the list control
		iRec = mViewSensors.InsertItem(0,strID,0);
		mViewSensors.SetItemText(0,1, strStatus);
		mViewSensors.SetItemText(0, 2, strPropaneValue);
		mViewSensors.SetItemText(0, 3, strMethaneValue);
		mViewSensors.SetItemText(0, 4, strCOValue);
		mViewSensors.SetItemText(0, 5, strBuildingName);
		mViewSensors.SetItemText(0, 6, strRoomNumber);
		mViewSensors.SetItemText(0, 7, strPropaneThreshold);
		mViewSensors.SetItemText(0, 8, strMethaneThreshold);
		mViewSensors.SetItemText(0, 9, strCOThreshold);

		// goto next record
		recset.MoveNext();
	}
}


//SMS Functions-------------------------------------------------------------------------------
size_t _twilio_null_write(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	return size * nmemb;
}

int CPrimeForm::sendSMS(char const* message) {
	char const* account_sid = "AC2224c0258a7de9a1f4084e9d0ab90646";
	char const* auth_token = "65abbaaec703b46920f5b58c45650ca8";
	//char const* message = "Test4";
	char const* from_number = "8302667136";
	char const* to_number = "2109121818";
	//char const* picture_url = "";
	bool verbose = true;

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








void CPrimeForm::OnTimer(UINT_PTR nIDEvent)
{
	//for (int i = 0; i < 5; i++) {
		OnSensorsUpdatesensors();
		
	//}


	CFormView::OnTimer(nIDEvent);
}

int CPrimeForm::MaxSensorID() { //Finds max sensor value to prevent querying a sensor that doesn't exist
	CString SqlString;
	CString strID;
	int intID;
	int maxID = 0;
	// Allocate the recordset
	CRecordset recset(&database);

	//Sensor Table

	// Build the SQL statement
	SqlString = "SELECT ID" " FROM Sensors";

	// Execute the query
	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

	// Loop through each record
	while (!recset.IsEOF()) {
		// Copy each column into a variable
		recset.GetFieldValue(L"ID", strID);
		intID = _wtoi(strID);

		if (intID > maxID) {
			maxID = intID;
		}

		// goto next record
		recset.MoveNext();
	}

	return maxID;
}
