#pragma once


// TestSQLDatabase dialog

class TestSQLDatabase : public CDialogEx
{
	DECLARE_DYNAMIC(TestSQLDatabase)

public:
	TestSQLDatabase(CWnd* pParent = nullptr);   // standard constructor
	virtual ~TestSQLDatabase();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEST_SQL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonWriteDatabaseTest();
};
