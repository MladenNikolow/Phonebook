#pragma once
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CNumericEdit

///<summary> Клас наследник на CEdit, който позовлява вход само от цифри </summary>
class CNumericEdit :
	public CEdit
{
// Macros
// ----------------
	DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
public:
	CNumericEdit();
	virtual ~CNumericEdit();

// Methods
// ----------------
private:
///<summary> Издава системен звук за грешка и показва Balloon Tip за грешката </summary>
void OnNotAllowedCharacter();

///<summary> Създава и показва Balloon Tip за грешка.
/// За да работи функцията, трябва да са позволени визуалните стилове </summary>
void ShowBalloonTip();

// MFC Message Handlers
// ----------------
private:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

