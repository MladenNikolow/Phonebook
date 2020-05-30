#pragma once

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

class CMainFrame : public CMDIFrameWnd
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CMainFrame)
	DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
public:
	CMainFrame();
	virtual ~CMainFrame();

// MFC Overrides
// ----------------
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// MFC Message Handlers
// ----------------
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

// Members
// ----------------
protected:
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
};


