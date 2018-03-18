
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
//Serial Port
#include<iostream>
using namespace std;
#include<string>
#include<stdlib.h>
#include"SerialPort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//Serial Port Variables
const int DataWidth = 8; //MAX_DATA_LENGTH
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

	//Table code
	pDC->Rectangle(0, 0, 810, 50* num_Row);

	CRect TableBodyRect;//Color Body
	TableBodyRect.SetRect(0, 50, 810, (50 * num_Row)-1);
	pDC->FillSolidRect(TableBodyRect, RGB(249, 248, 234));

	CRect TableHeaderRect;//Color Header
	TableHeaderRect.SetRect(0, 0, 810, 50);
	pDC->FillSolidRect(TableHeaderRect, RGB(184, 231, 249));

	for (int i = 1; i < num_Row; i++) { //row lines
		pDC->MoveTo(0, 50*i); 
		pDC->LineTo(810, 50*i);
	}

	pDC->MoveTo(120,0); //First Col
	pDC->LineTo(120,50 * num_Row);
	pDC->TextOutW(10, 15, _T("SENSOR ID"));
	pDC->MoveTo(210, 0);//Second Col
	pDC->LineTo(210, 50 * num_Row);
	pDC->TextOutW(130, 15, _T("STATUS"));
	pDC->MoveTo(410, 0);//Third Col
	pDC->LineTo(410, 50 * num_Row);
	pDC->TextOutW(220, 15, _T("PROPANE VALUE")); 
	pDC->MoveTo(610, 0);//Fourth Col
	pDC->LineTo(610, 50 * num_Row);
	pDC->TextOutW(420, 15, _T("METHANE VALUE"));
	pDC->MoveTo(810, 0);//Fifth Col
	pDC->LineTo(810, 50 * num_Row);
	pDC->TextOutW(620, 15, _T("CO VALUE"));
	
	//Serial Debug Test Code
	CString TempDebugOutput = CString(output, DataWidth);
	pDC->TextOutW(400, 400, TempDebugOutput);
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

		char *charArray = "ACK";

		arduino.writeSerialPort(charArray, DataWidth);
		arduino.readSerialPort(output, DataWidth);

		Invalidate();
		UpdateWindow();
		charArray = " ";
	}
}
