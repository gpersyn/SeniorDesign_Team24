#pragma once
#include "afxcmn.h"
class ViewAlertsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ViewAlertsDlg)

public:
	ViewAlertsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ViewAlertsDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VIEW_ALERTS};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ViewAlerts;
	afx_msg void OnBnClickedButtonRefresh();
	void ResetListControl();
	afx_msg void OnBnClickedButtonClearAlerts();
};

