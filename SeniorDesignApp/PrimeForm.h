#pragma once



// CPrimeForm form view

class CPrimeForm : public CFormView
{
	DECLARE_DYNCREATE(CPrimeForm)

protected:
	CPrimeForm();           // protected constructor used by dynamic creation
	virtual ~CPrimeForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRIMEFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};


