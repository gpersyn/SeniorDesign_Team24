#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "DeleteSensorDlg.h"
#include "afxdialogex.h"


// CAddSensorDlg dialog

IMPLEMENT_DYNAMIC(DeleteSensorDlg, CDialogEx)

DeleteSensorDlg::DeleteSensorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DELETE_SENSOR, pParent)
	, m_SensorID(0)
{

}

DeleteSensorDlg::~DeleteSensorDlg()
{
}

void DeleteSensorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_SENSOR_ID, m_SensorID);
}


BEGIN_MESSAGE_MAP(DeleteSensorDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddSensorDlg message handlers

