#include "stdafx.h"
#include "NumericEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CNumericEdit

// Macros
// ----------------
BEGIN_MESSAGE_MAP(CNumericEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CNumericEdit::CNumericEdit()
{
}

CNumericEdit::~CNumericEdit()
{
}

// Methods
// ----------------
void CNumericEdit::OnNotAllowedCharacter()
{
	MessageBeep(0xFFFFFFFF);
	ShowBalloonTip();
}

void CNumericEdit::ShowBalloonTip()
{
	CStringW strReasonForCancelingChar;
	EDITBALLOONTIP oEditBalloonTip;

	oEditBalloonTip.cbStruct = sizeof(EDITBALLOONTIP);
	oEditBalloonTip.pszTitle = L"Unacceptable Character";
	strReasonForCancelingChar.Format(L"Only number are allowed!");
	oEditBalloonTip.pszText = strReasonForCancelingChar.GetBuffer();
	oEditBalloonTip.ttiIcon = TTI_ERROR;

	SendMessage(EM_SHOWBALLOONTIP, 0, (LPARAM)&oEditBalloonTip);

	strReasonForCancelingChar.ReleaseBuffer();
}

// MFC Message Handlers
// ----------------
void CNumericEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!isdigit(nChar) && !iscntrl(nChar))
	{
		OnNotAllowedCharacter();
		return;
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
