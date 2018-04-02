#pragma once
#include "afxcmn.h"


// CAddSensorDlg dialog

class ViewUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ViewUserDlg)

public:
	ViewUserDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ViewUserDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DIALOG_VIEW_USERS
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRefresh();
	void ResetListControl();
	CListCtrl m_Database_View;
};
