#include "stdafx.h"
#include "AlphabeticEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CAlphabeticEdit

// Macros
// ----------------
BEGIN_MESSAGE_MAP(CAlphabeticEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CAlphabeticEdit::CAlphabeticEdit()
{
}

CAlphabeticEdit::~CAlphabeticEdit()
{
}

// Methods
// ----------------
void CAlphabeticEdit::OnNotAllowedCharacter(const UINT& nChar)
{
	MessageBeep(0xFFFFFFFF);
	ShowBalloonTip(nChar);
}

void CAlphabeticEdit::ShowBalloonTip(const UINT& nChar)
{
	CStringW strReasonForCancelingChar;
	EDITBALLOONTIP oEditBalloonTip;

	oEditBalloonTip.cbStruct = sizeof(EDITBALLOONTIP);
	oEditBalloonTip.pszTitle = L"Unacceptable Character";
	strReasonForCancelingChar.Format(L"The character %c is not allowed!", nChar);
	oEditBalloonTip.pszText = strReasonForCancelingChar.GetBuffer();
	oEditBalloonTip.ttiIcon = TTI_ERROR;

	SendMessage(EM_SHOWBALLOONTIP, 0, (LPARAM)&oEditBalloonTip);

	strReasonForCancelingChar.ReleaseBuffer();
}

// MFC Message Handlers
// ----------------
void CAlphabeticEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (ispunct(nChar) || isdigit(nChar))
	{
		OnNotAllowedCharacter(nChar);
		return;
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

