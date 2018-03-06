
// SeniorDesignAppView.cpp : implementation of the CSeniorDesignAppView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SeniorDesignApp.h"
#endif

#include "SeniorDesignAppDoc.h"
#include "SeniorDesignAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSeniorDesignAppView

IMPLEMENT_DYNCREATE(CSeniorDesignAppView, CView)

BEGIN_MESSAGE_MAP(CSeniorDesignAppView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSeniorDesignAppView construction/destruction

CSeniorDesignAppView::CSeniorDesignAppView()
{
	// TODO: add construction code here

}

CSeniorDesignAppView::~CSeniorDesignAppView()
{
}

BOOL CSeniorDesignAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSeniorDesignAppView drawing

void CSeniorDesignAppView::OnDraw(CDC* /*pDC*/)
{
	CSeniorDesignAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CSeniorDesignAppView printing

BOOL CSeniorDesignAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSeniorDesignAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSeniorDesignAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSeniorDesignAppView diagnostics

#ifdef _DEBUG
void CSeniorDesignAppView::AssertValid() const
{
	CView::AssertValid();
}

void CSeniorDesignAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSeniorDesignAppDoc* CSeniorDesignAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSeniorDesignAppDoc)));
	return (CSeniorDesignAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CSeniorDesignAppView message handlers
