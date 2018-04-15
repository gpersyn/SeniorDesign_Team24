// AddSensorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "AddSensorDlg.h"
#include "afxdialogex.h"


// CAddSensorDlg dialog

IMPLEMENT_DYNAMIC(CAddSensorDlg, CDialogEx)

CAddSensorDlg::CAddSensorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADD_SENSOR, pParent)
	, m_Sensor_ID(0)
	, m_Building_Name(_T(""))
	, m_Room_Number(0)
	, m_Propane_Threshold(100)
	, m_Methane_Threshold(100)
	, m_CO_Threshold(100)
{

}

CAddSensorDlg::~CAddSensorDlg()
{
}

void CAddSensorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SENSOR_ID, m_Sensor_ID);
	DDX_Text(pDX, IDC_EDIT_BUILDING, m_Building_Name);
	DDX_Text(pDX, IDC_EDIT_ROOM, m_Room_Number);
	DDX_Text(pDX, IDC_EDIT_PRO_THRESH, m_Propane_Threshold);
	DDV_MinMaxInt(pDX, m_Propane_Threshold, 0, 999);
	DDX_Text(pDX, IDC_EDIT_METH_THRESH, m_Methane_Threshold);
	DDV_MinMaxInt(pDX, m_Methane_Threshold, 0, 999);
	DDX_Text(pDX, IDC_EDIT_CO_THRESH, m_CO_Threshold);
	DDV_MinMaxInt(pDX, m_CO_Threshold, 0, 999);
}


BEGIN_MESSAGE_MAP(CAddSensorDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddSensorDlg message handlers
