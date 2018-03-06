// PrimeForm.cpp : implementation file
//

#include "stdafx.h"
#include "SeniorDesignApp.h"
#include "PrimeForm.h"


// CPrimeForm

IMPLEMENT_DYNCREATE(CPrimeForm, CFormView)

CPrimeForm::CPrimeForm()
	: CFormView(IDD_PRIMEFORM)
{

}

CPrimeForm::~CPrimeForm()
{
}

void CPrimeForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPrimeForm, CFormView)
END_MESSAGE_MAP()


// CPrimeForm diagnostics

#ifdef _DEBUG
void CPrimeForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPrimeForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPrimeForm message handlers
