
// SeniorDesignAppView.cpp : implementation of the CSeniorDesignAppView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SeniorDesignApp.h"
#endif

#include "SeniorDesignAppDoc.h"
#include "SeniorDesignAppView.h"

//Custom Dialogs
#include "AddUserDlg.h"
#include "AddSensorDlg.h"
#include "SerialDebugDlg.h"
#include "TestSensorDlg.h"
#include "ConfigSensorDlg.h"
#include "TestSQLDatabase.h"
//Serial Port
#include<iostream>
using namespace std;
#include<string>
#include<stdlib.h>
#include"SerialPort.h"
//For Database
#include "odbcinst.h"
#include "afxdb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//Serial Port Variables
const int DataWidth = 12; //MAX_DATA_LENGTH
char output[DataWidth];
char incomingData[DataWidth];
char *port = "\\\\.\\COM4";

// CSeniorDesignAppView

IMPLEMENT_DYNCREATE(CSeniorDesignAppView, CView)

BEGIN_MESSAGE_MAP(CSeniorDesignAppView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_ADD_USER, &CSeniorDesignAppView::OnAddUser)
	ON_COMMAND(ID_ADD_SENSOR, &CSeniorDesignAppView::OnAddSensor)
	ON_COMMAND(ID_DEBUG_ADDROW, &CSeniorDesignAppView::OnDebugAddrow)
	ON_COMMAND(ID_DEBUG_REMOVEROW, &CSeniorDesignAppView::OnDebugRemoverow)
	ON_COMMAND(ID_DEBUG_SERIALDEBUG, &CSeniorDesignAppView::OnDebugSerialDebug)
	ON_COMMAND(ID_DEBUG_LEDSWITCH, &CSeniorDesignAppView::OnDebugLedswitch)
	ON_COMMAND(ID_BUTTON_TABLESIZE_INCREASE, &CSeniorDesignAppView::OnButtonTablesizeIncrease)
	ON_COMMAND(ID_BUTTON_TABLESIZE_DECREASE, &CSeniorDesignAppView::OnButtonTablesizeDecrease)
	ON_COMMAND(ID_SENSORS_CONFIGURESENSOR, &CSeniorDesignAppView::OnSensorsConfiguresensor)
	ON_COMMAND(ID_SENSORS_TESTSENSOR, &CSeniorDesignAppView::OnSensorsTestsensor)
	ON_COMMAND(ID_DEBUG_SQLDATABASE, &CSeniorDesignAppView::OnDebugSqldatabase)
END_MESSAGE_MAP()

//Serial Port Code Here
SerialPort arduino(port);


// CSeniorDesignAppView construction/destruction

CSeniorDesignAppView::CSeniorDesignAppView()
{
	// TODO: add construction code here

}

CSeniorDesignAppView::~CSeniorDesignAppView()
{
}

BOOL CSeniorDesignAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSeniorDesignAppView drawing

void CSeniorDesignAppView::OnDraw(CDC* pDC)
{
	CSeniorDesignAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//Custom Font
	CFont font;
	VERIFY(font.CreateFont(
		(20 * table_size),							//nHeight
		0,							//nWidth
		0,							//nEscapement
		0,							//nOrientation
		FW_NORMAL,					//nWeight
		FALSE,						//bItalic
		FALSE,						//bUnderline
		0,							//cStrikeOut
		ANSI_CHARSET,				//nCharSet
		OUT_DEFAULT_PRECIS,			//nOutPrecision
		CLIP_DEFAULT_PRECIS,		//nClipPrecision
		DEFAULT_QUALITY,			//nQuality
		DEFAULT_PITCH | FF_SWISS,	//nPitchAndFamily
		L"Arial"));					//lpszFacename

	CFont* def_font = pDC->SelectObject(&font); //Saves Old Font


	//Table code
	pDC->Rectangle(0, 0, 810* table_size, 50 * table_size * num_Row);

	CRect TableBodyRect;//Color Body
	TableBodyRect.SetRect(0, 50, 810 * table_size, ((50 * num_Row)-1) * table_size);
	pDC->FillSolidRect(TableBodyRect, RGB(249, 248, 234));


	for (int i = 1; i < num_Row; i++) { //row lines
		pDC->MoveTo(0, 50*i*table_size);
		pDC->LineTo(810 * table_size, 50*i*table_size);
		//Write Sensor Values
		DecodeSerialInput();
		if (i == 1) {
			pDC->TextOutW(10 * table_size, (50 * i * table_size) + (15 * table_size), Sensor_ID); //Sensor ID
			pDC->TextOutW(130 * table_size, (50 * i * table_size) + (15 * table_size), Sensor_Status); //Status
			pDC->TextOutW(220 * table_size, (50 * i * table_size) + (15 * table_size), CO_Value); //CO
			pDC->TextOutW(420 * table_size, (50 * i * table_size) + (15 * table_size), Methane_Value); //Methane
			pDC->TextOutW(620 * table_size, (50 * i * table_size) + (15 * table_size), Propane_Value); //Propane
		}
	}

	CRect TableHeaderRect;//Color Header
	TableHeaderRect.SetRect(0, 0, 810 * table_size, 50 * table_size);
	pDC->FillSolidRect(TableHeaderRect, RGB(184, 231, 249));

	pDC->MoveTo(120 * table_size,0); //First Col
	pDC->LineTo(120 * table_size,50 * num_Row * table_size);
	pDC->TextOutW(10 * table_size, 15 * table_size, _T("SENSOR ID"));
	pDC->MoveTo(210 * table_size, 0);//Second Col
	pDC->LineTo(210 * table_size, 50 * num_Row * table_size);
	pDC->TextOutW(130 * table_size, 15 * table_size, _T("STATUS"));
	pDC->MoveTo(410 * table_size, 0);//Third Col
	pDC->LineTo(410 * table_size, 50 * num_Row * table_size);
	pDC->TextOutW(220 * table_size, 15 * table_size, _T("CO VALUE"));
	pDC->MoveTo(610 * table_size, 0);//Fourth Col
	pDC->LineTo(610 * table_size, 50 * num_Row * table_size);
	pDC->TextOutW(420 * table_size, 15 * table_size, _T("METHANE VALUE"));
	pDC->MoveTo(810 * table_size, 0);//Fifth Col
	pDC->LineTo(810 * table_size, 50 * num_Row * table_size);
	pDC->TextOutW(620 * table_size, 15 * table_size, _T("PROPANE VALUE"));
	
	//Reset Text Background Color
	pDC->SetBkMode(TRANSPARENT);

	//Serial Debug Test Code
	CString TempDebugOutput = CString(incomingData, DataWidth);
	pDC->TextOutW(400, 400, TempDebugOutput);

	//DrawText Test
	pDC->SelectObject(def_font); //Sets Font back to old Font
}


// CSeniorDesignAppView printing

BOOL CSeniorDesignAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSeniorDesignAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSeniorDesignAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSeniorDesignAppView diagnostics

#ifdef _DEBUG
void CSeniorDesignAppView::AssertValid() const
{
	CView::AssertValid();
}

void CSeniorDesignAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSeniorDesignAppDoc* CSeniorDesignAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSeniorDesignAppDoc)));
	return (CSeniorDesignAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CSeniorDesignAppView message handlers


void CSeniorDesignAppView::OnAddUser() //Add user button is pressed
{
	CAddUserDlg dlgAddUser; //Call Add User Dialog Box
	dlgAddUser.DoModal();
}


void CSeniorDesignAppView::OnAddSensor()
{
	CAddSensorDlg dlgAddSensor; //Call Add Sensor Dialog Box
	dlgAddSensor.DoModal();
}


void CSeniorDesignAppView::OnDebugAddrow()
{
	num_Row++;
	Invalidate();
	UpdateWindow();
}


void CSeniorDesignAppView::OnDebugRemoverow()
{
	if(num_Row > 2) {
		num_Row--;
		Invalidate();
		UpdateWindow();
	}
	
}


void CSeniorDesignAppView::OnDebugSerialDebug()
{
	//Open Modeless Dialog Box
	SerialDebugDlg *dlgSerialDebug = new SerialDebugDlg(this);
	dlgSerialDebug->Create(IDD_DIALOG_SERIAL_DEBUG,GetDesktopWindow());
	dlgSerialDebug->ShowWindow(SW_SHOW);

	dlgSerialDebug->m_SerialDebug_Read = _T("Sent!");
	//Pass info from open Dialog box 
	if (dlgSerialDebug->m_SerialDebug_Send.GetCheck() == BST_CHECKED) {
		dlgSerialDebug->m_SerialDebug_Read = _T("Sent!");
		m_SerialDebug_Write_View = dlgSerialDebug->m_SerialDebug_Write;
	}


	//m_SerialDebug_Send_View = dlgSerialDebug.m_SerialDebug_Send;
	//IDOK
	/*if (dlgSerialDebug.DoModal() == IDOK) {
		m_SerialDebug_Write_View = dlgSerialDebug.m_SerialDebug_Write;
		m_SerialDebug_Read_View = dlgSerialDebug.m_SerialDebug_Read;
		Invalidate();
		UpdateWindow();
	}*/
	//dlgSerialDebug->Create(CModeless:IDD);

}

void CSeniorDesignAppView::OnDebugLedswitch()
{
	if (arduino.isConnected()) {
		/*CString data = _T("ACK");
		char *charArray = new char[data.GetLength() + 1];
		copy(data.Mid(0,0), data.Mid(data.GetLength() - 1, data.GetLength() - 1), charArray);
		charArray[data.GetLength()] = '\n';*/

		charInputArray = "ACK";

		arduino.writeSerialPort(charInputArray, DataWidth);
		arduino.readSerialPort(incomingData, DataWidth);

		Invalidate();
		UpdateWindow();
	}
}


void CSeniorDesignAppView::OnButtonTablesizeIncrease()
{
	if (table_size < 2.5) {
		table_size = table_size + 0.25;
		Invalidate();
		UpdateWindow();
	}
}


void CSeniorDesignAppView::OnButtonTablesizeDecrease()
{
	if (table_size > 1) {
		table_size = table_size - 0.25;
		Invalidate();
		UpdateWindow();
	}
}

void CSeniorDesignAppView::DecodeSerialInput() {
	//Initialize Temp C Array Variables
	char Sensor_ID_Temp[3]{ 0,0,0 };
	char CO_Value_Temp[3]{ 0, 0, 0 };
	char Methane_Value_Temp[3]{ 0, 0, 0 };
	char Propane_Value_Temp[3]{ 0, 0, 0 };

	//Get Sensor ID from Serial Input
	int i;
	int j = 0;
	for (i = 0; i < 3; i++) {
		Sensor_ID_Temp[j] = incomingData[i];
		j++;
	}
	j = 0;
	//Get CO Values
	for (i = 3; i < 6; i++) {
		CO_Value_Temp[j] = incomingData[i];
		j++;
	}
	j = 0;
	//Get Methane Values
	for (i = 6; i < 9; i++) {
		Methane_Value_Temp[j] = incomingData[i];
		j++;
	}
	j = 0;
	//Get Propane Values
	for (i = 9; i < 12; i++) {
		Propane_Value_Temp[j] = incomingData[i];
		j++;
	}

	//Convert Sensor Values to CSTRING
	Sensor_ID = CString(Sensor_ID_Temp, 3);
	CO_Value = CString(CO_Value_Temp, 3);
	Methane_Value = CString(Methane_Value_Temp, 3);
	Propane_Value = CString(Propane_Value_Temp, 3);

	//Check if sensor is working (NOT ADDED YET)
	Sensor_Status = "Yes"; //Temp
}

void CSeniorDesignAppView::OnSensorsConfiguresensor()
{
	ConfigSensorDlg ConfigureSensorDialog; //Call Config Sensor Dialog Box
	ConfigureSensorDialog.DoModal();

	//Use Return Values
	CString test3 = ConfigureSensorDialog.m_Config_SensorID;
	int test2 = ConfigureSensorDialog.Methane_Threshold_Value;

	CStringA test1 = "Hi";
	char *OutputSerial;
	OutputSerial = test1.GetBuffer(test1.GetLength()); //convert to char array

	arduino.writeSerialPort(OutputSerial, DataWidth);
}


void CSeniorDesignAppView::OnSensorsTestsensor()
{
	TestSensorDlg TestSensorDialog; //Call Test Sensor Dialog Box
	TestSensorDialog.DoModal();
}


void CSeniorDesignAppView::OnDebugSqldatabase() //When test SQL button pressed in menu call dialog box
{
	TestSQLDatabase TestDatabase;
	TestDatabase.DoModal();
}
