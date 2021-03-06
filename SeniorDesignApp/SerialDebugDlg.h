#pragma once
#include "afxwin.h"


// SerialDebugDlg dialog

class SerialDebugDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SerialDebugDlg)

public:
	SerialDebugDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SerialDebugDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SERIAL_DEBUG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_SerialDebug_Write;
	CString m_SerialDebug_Read;
	CButton m_SerialDebug_Send;
	afx_msg void OnBnClickedSerialdebugSend();
	bool SerialDebugSend_Clicked{ false };
};
