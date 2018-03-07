#pragma once


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
};
