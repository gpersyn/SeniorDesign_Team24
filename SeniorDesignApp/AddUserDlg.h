#pragma once
#include "afxcmn.h"


// CAddUserDlg dialog

class CAddUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddUserDlg)

public:
	CAddUserDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddUserDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_USER}; 
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_UserName;
	CString m_FirstName;
	CString m_LastName;
	long m_PhoneNumber;
	CString m_Email;
	int m_UserID;
	CString m_UserPassword;
	bool m_ADMIN_ON;
};
