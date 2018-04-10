#pragma once
class UserLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UserLoginDlg)

public:
	UserLoginDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~UserLoginDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOG_IN};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_UserName;
	CString m_Password;
};

