
// MFC_1View.h : interface of the CMFC_1View class
//

#pragma once


class CMFC_1View : public CView
{
protected: // create from serialization only
	CMFC_1View();
	DECLARE_DYNCREATE(CMFC_1View)

// Attributes
public:
	CMFC_1Doc* GetDocument() const;

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
	virtual ~CMFC_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFC_1View.cpp
inline CMFC_1Doc* CMFC_1View::GetDocument() const
   { return reinterpret_cast<CMFC_1Doc*>(m_pDocument); }
#endif

