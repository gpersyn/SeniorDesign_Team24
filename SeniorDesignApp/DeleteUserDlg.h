#pragma once


// CAddSensorDlg dialog

class DeleteUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteUserDlg)

public:
	DeleteUserDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~DeleteUserDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELETE_USERS
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_UserID;
};
