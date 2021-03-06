#pragma once


// ConfigSensorDlg dialog

class ConfigSensorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConfigSensorDlg)

public:
	ConfigSensorDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ConfigSensorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONFIG_SENSOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	int CO_Threshold_Value;
	int Methane_Threshold_Value;
	int Propane_Threshold_Value;
	bool Sensor_State;

	int m_SensorID;
	int m_CO_Thresh;
	int m_Meth_Thresh;
	int m_ProThresh;
	afx_msg void OnBnClickedRadioConfigSensorStateOn();
	afx_msg void OnBnClickedRadioConfigSensorStateOff();
};
