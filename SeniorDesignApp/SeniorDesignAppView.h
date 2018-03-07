
// SeniorDesignAppView.h : interface of the CSeniorDesignAppView class
//

#pragma once


class CSeniorDesignAppView : public CView
{
protected: // create from serialization only
	CSeniorDesignAppView();
	DECLARE_DYNCREATE(CSeniorDesignAppView)

// Attributes
public:
	CSeniorDesignAppDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSeniorDesignAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddUser();
};

#ifndef _DEBUG  // debug version in SeniorDesignAppView.cpp
inline CSeniorDesignAppDoc* CSeniorDesignAppView::GetDocument() const
   { return reinterpret_cast<CSeniorDesignAppDoc*>(m_pDocument); }
#endif

