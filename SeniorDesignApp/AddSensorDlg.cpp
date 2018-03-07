// AddSensorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "AddSensorDlg.h"
#include "afxdialogex.h"


// CAddSensorDlg dialog

IMPLEMENT_DYNAMIC(CAddSensorDlg, CDialogEx)

CAddSensorDlg::CAddSensorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADD_SENSOR, pParent)
{

}

CAddSensorDlg::~CAddSensorDlg()
{
}

void CAddSensorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddSensorDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddSensorDlg message handlers
