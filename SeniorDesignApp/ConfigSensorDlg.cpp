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
	, m_CO_Thresh(0)
	, m_Meth_Thresh(0)
	, m_ProThresh(0)
	, Sensor_State(true)
{

}

ConfigSensorDlg::~ConfigSensorDlg()
{
}

void ConfigSensorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_SensorID);
	DDX_Text(pDX, IDC_CONFIG_CO_THRESHOLD, m_CO_Thresh);
	DDV_MinMaxInt(pDX, m_CO_Thresh, 0, 999);
	DDX_Text(pDX, IDC_CONFIG_METHANE_THRESHOLD, m_Meth_Thresh);
	DDV_MinMaxInt(pDX, m_Meth_Thresh, 0, 999);
	DDX_Text(pDX, IDC_CONFIG_PROPANE_THRESHOLD, m_ProThresh);
	DDV_MinMaxInt(pDX, m_ProThresh, 0, 999);
}


BEGIN_MESSAGE_MAP(ConfigSensorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &ConfigSensorDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO_CONFIG_SENSOR_STATE_ON, &ConfigSensorDlg::OnBnClickedRadioConfigSensorStateOn)
	ON_BN_CLICKED(IDC_RADIO_CONFIG_SENSOR_STATE_OFF, &ConfigSensorDlg::OnBnClickedRadioConfigSensorStateOff)
END_MESSAGE_MAP()


// ConfigSensorDlg message handlers


void ConfigSensorDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
}


void ConfigSensorDlg::OnBnClickedRadioConfigSensorStateOn()
{
	Sensor_State = true; //Sensor on
}


void ConfigSensorDlg::OnBnClickedRadioConfigSensorStateOff()
{
	Sensor_State = false; //Sensor off
}
