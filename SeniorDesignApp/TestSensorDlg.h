#pragma once


// TestSensorDlg dialog

class TestSensorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TestSensorDlg)

public:
	TestSensorDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~TestSensorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEST_SENSOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_SensorID;
};
