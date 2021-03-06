// SerialDebugDlg.cpp : implementation fileIDD_DIALOG_SERIAL_DEBUG
//

#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "SerialDebugDlg.h"
#include "afxdialogex.h"


// SerialDebugDlg dialog

IMPLEMENT_DYNAMIC(SerialDebugDlg, CDialogEx)

SerialDebugDlg::SerialDebugDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SERIAL_DEBUG, pParent)
	, m_SerialDebug_Write(_T(""))
	, m_SerialDebug_Read(_T("Test"))
{

}

SerialDebugDlg::~SerialDebugDlg()
{
}

void SerialDebugDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXTBOX_SERIAL_WRITE, m_SerialDebug_Write);
	DDX_Text(pDX, IDC_TEXTBOX_SERIAL_READ, m_SerialDebug_Read);
	DDX_Control(pDX, IDC_SerialDebug_Send, m_SerialDebug_Send);
}



BEGIN_MESSAGE_MAP(SerialDebugDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SerialDebug_Send, &SerialDebugDlg::OnBnClickedSerialdebugSend)
END_MESSAGE_MAP()


// SerialDebugDlg message handlers


void SerialDebugDlg::OnBnClickedSerialdebugSend()
{
	SerialDebugSend_Clicked = true;
	m_SerialDebug_Read = _T("Another Test");
	Invalidate();
	UpdateWindow();
}
