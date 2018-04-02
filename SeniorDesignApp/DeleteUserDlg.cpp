// DeleteUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "DeleteUserDlg.h"
#include "afxdialogex.h"


// CAddSensorDlg dialog

IMPLEMENT_DYNAMIC(DeleteUserDlg, CDialogEx)

DeleteUserDlg::DeleteUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DELETE_USERS, pParent)
	, m_UserID(0)
{

}

DeleteUserDlg::~DeleteUserDlg()
{
}

void DeleteUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_UserID);
}


BEGIN_MESSAGE_MAP(DeleteUserDlg, CDialogEx)
END_MESSAGE_MAP()


