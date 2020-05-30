#pragma once

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

class CChildFrame : public CMDIChildWnd
{
// Macros
// ----------------
protected:
	DECLARE_DYNCREATE(CChildFrame)
	DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
public:
	CChildFrame();
	virtual ~CChildFrame();

// MFC Overrides
// ----------------
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
