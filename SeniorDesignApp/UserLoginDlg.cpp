#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "UserLoginDlg.h"
#include "afxdialogex.h"


// TestSensorDlg dialog

IMPLEMENT_DYNAMIC(UserLoginDlg, CDialogEx)

UserLoginDlg::UserLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOG_IN, pParent)
	, m_UserName(_T(""))
	, m_Password(_T(""))
{

}

UserLoginDlg::~UserLoginDlg()
{
}

void UserLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_UserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_Password);
}


BEGIN_MESSAGE_MAP(UserLoginDlg, CDialogEx)
END_MESSAGE_MAP()
