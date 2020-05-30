#pragma once
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CAlphabeticEdit

///<summary> Клас наследник на CEdit, който позовлява вход само от букви и спейсове </summary>
class CAlphabeticEdit :
	public CEdit
{
// Macros
// ----------------
	DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
public:
	CAlphabeticEdit();
	virtual ~CAlphabeticEdit();

// Methods
// ----------------
private:
	///<summary> Издава системен звук за грешка и показва Balloon Tip за грешката </summary>
	void OnNotAllowedCharacter(const UINT& nChar);

	///<summary> Създава и показва Balloon Tip за грешка.
	/// За да работи функцията, трябва да са позволени визуалните стилове </summary>
	void ShowBalloonTip(const UINT& nChar);

// MFC Message Handlers
// ----------------
private:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

