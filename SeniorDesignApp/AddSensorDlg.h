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
};
