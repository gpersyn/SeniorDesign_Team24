// AddUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "AddUserDlg.h"
#include "afxdialogex.h"


// CAddUserDlg dialog

IMPLEMENT_DYNAMIC(CAddUserDlg, CDialogEx)

CAddUserDlg::CAddUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADD_USER, pParent)
{

}

CAddUserDlg::~CAddUserDlg()
{
}

void CAddUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddUserDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddUserDlg message handlers
