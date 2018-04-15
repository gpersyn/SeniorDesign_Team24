#pragma once


// CAddSensorDlg dialog

class CAddSensorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddSensorDlg)

public:
	CAddSensorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddSensorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_SENSOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_Sensor_ID;
	CString m_Building_Name;
	int m_Room_Number;
	int m_Propane_Threshold;
	int m_Methane_Threshold;
	int m_CO_Threshold;
};
