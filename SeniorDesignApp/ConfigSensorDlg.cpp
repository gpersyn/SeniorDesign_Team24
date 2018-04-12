// ConfigSensorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "ConfigSensorDlg.h"
#include "afxdialogex.h"


// ConfigSensorDlg dialog

IMPLEMENT_DYNAMIC(ConfigSensorDlg, CDialogEx)

ConfigSensorDlg::ConfigSensorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONFIG_SENSOR, pParent)
	, m_SensorID(0)
{

}

ConfigSensorDlg::~ConfigSensorDlg()
{
}

void ConfigSensorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_SensorID);
}


BEGIN_MESSAGE_MAP(ConfigSensorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &ConfigSensorDlg::OnBnClickedRadio1)
END_MESSAGE_MAP()


// ConfigSensorDlg message handlers


void ConfigSensorDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
}
