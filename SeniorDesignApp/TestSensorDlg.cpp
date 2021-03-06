// TestSensorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "TestSensorDlg.h"
#include "afxdialogex.h"


// TestSensorDlg dialog

IMPLEMENT_DYNAMIC(TestSensorDlg, CDialogEx)

TestSensorDlg::TestSensorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEST_SENSOR, pParent)
	, m_SensorID(0)
{

}

TestSensorDlg::~TestSensorDlg()
{
}

void TestSensorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEST_ID, m_SensorID);
	DDV_MinMaxInt(pDX, m_SensorID, 0, 999);
}


BEGIN_MESSAGE_MAP(TestSensorDlg, CDialogEx)
END_MESSAGE_MAP()


// TestSensorDlg message handlers
