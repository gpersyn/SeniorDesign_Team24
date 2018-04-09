#pragma once

class TestSMSDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TestSMSDlg)

public:
	TestSMSDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~TestSMSDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEBUG_SMS_TEST};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
};

