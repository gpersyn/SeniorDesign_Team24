// SerialDebugDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "SerialDebugDlg.h"
#include "afxdialogex.h"


// SerialDebugDlg dialog

IMPLEMENT_DYNAMIC(SerialDebugDlg, CDialogEx)

SerialDebugDlg::SerialDebugDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SERIAL_DEBUG, pParent)
{

}

SerialDebugDlg::~SerialDebugDlg()
{
}

void SerialDebugDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SerialDebugDlg, CDialogEx)
END_MESSAGE_MAP()


// SerialDebugDlg message handlers
