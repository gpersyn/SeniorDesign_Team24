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
}


BEGIN_MESSAGE_MAP(CAddSensorDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddSensorDlg message handlers
