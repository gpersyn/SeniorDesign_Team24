#pragma once

// CDeleteSensor dialog

class DeleteSensorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteSensorDlg)

public:
	DeleteSensorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~DeleteSensorDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELETE_SENSOR};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	int m_SensorID;
};

