// AddUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "AddUserDlg.h"
#include "afxdialogex.h"
//For Database
#include "odbcinst.h"
#include "afxdb.h"

// CAddUserDlg dialog

IMPLEMENT_DYNAMIC(CAddUserDlg, CDialogEx)

CAddUserDlg::CAddUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADD_USER, pParent)
	, m_UserName(_T(""))
	, m_FirstName(_T(""))
	, m_LastName(_T(""))
	, m_PhoneNumber(0)
	, m_Email(_T(""))
	, m_UserID(0)
	, m_UserPassword(_T(""))
	, m_ADMIN_ON(true)
{

}

CAddUserDlg::~CAddUserDlg()
{
}

void CAddUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USER_NAME, m_UserName);
	DDX_Text(pDX, IDC_FIRST_NAME, m_FirstName);
	DDX_Text(pDX, IDC_LAST_NAME, m_LastName);
	DDX_Text(pDX, IDC_PHONE_NUMBER, m_PhoneNumber);
	DDX_Text(pDX, IDC_EMAIL, m_Email);
	DDX_Text(pDX, IDC_USER_ID, m_UserID);
	DDX_Text(pDX, IDC_EDIT_USER_PASSWORD, m_UserPassword);
}


BEGIN_MESSAGE_MAP(CAddUserDlg, CDialogEx)

	ON_BN_CLICKED(IDC_RADIO_ADMIN, &CAddUserDlg::OnBnClickedRadioAdmin)
	ON_BN_CLICKED(IDC_RADIO_GENERAL, &CAddUserDlg::OnBnClickedRadioGeneral)
END_MESSAGE_MAP()


// CAddUserDlg message handlers


void CAddUserDlg::OnBnClickedRadioAdmin()
{
	m_ADMIN_ON = true;
}


void CAddUserDlg::OnBnClickedRadioGeneral()
{
	m_ADMIN_ON = false;
}
