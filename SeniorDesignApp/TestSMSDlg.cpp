#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "TestSMSDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(TestSMSDlg, CDialogEx)

TestSMSDlg::TestSMSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEBUG_SMS_TEST, pParent)
{

}

TestSMSDlg::~TestSMSDlg()
{
}

void TestSMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TestSMSDlg, CDialogEx)
END_MESSAGE_MAP()


// TestSensorDlg message handlers

