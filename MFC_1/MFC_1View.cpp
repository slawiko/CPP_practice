
// MFC_1View.cpp : implementation of the CMFC_1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_1.h"
#endif

#include "MFC_1Doc.h"
#include "MFC_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_1View

IMPLEMENT_DYNCREATE(CMFC_1View, CView)

BEGIN_MESSAGE_MAP(CMFC_1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFC_1View construction/destruction

CMFC_1View::CMFC_1View()
{
	// TODO: add construction code here

}

CMFC_1View::~CMFC_1View()
{
}

BOOL CMFC_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFC_1View drawing

void CMFC_1View::OnDraw(CDC* /*pDC*/)
{
	CMFC_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFC_1View printing

BOOL CMFC_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFC_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFC_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFC_1View diagnostics

#ifdef _DEBUG
void CMFC_1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_1Doc* CMFC_1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_1Doc)));
	return (CMFC_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_1View message handlers
