#pragma once
#include "afxwin.h"
#include "Structures.h"
#include "ModifyRecordUtilites.h"
#include "AlphabeticEdit.h"
#include "DlgUtilities.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDlg

///<summary> Диалог за CITIES </summary>
class CCitiesDlg : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CCitiesDlg)
	DECLARE_MESSAGE_MAP()

// Constants
// ----------------
private:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CITIES };
#endif

//Dialog Titles
#define CITIES_DIALOG_CAPTION_VIEW "City Info"
#define CITIES_DIALOG_CAPTION_INSERT "Add City"
#define CITIES_DIALOG_CAPTION_EDIT "Edit City"

// Constructor / Destructor
// ----------------
public:
	CCitiesDlg(CWnd* pParent = NULL) = delete;
	CCitiesDlg(const ModificationTypes& eModificationType, CITIES& oCities, CWnd* pParent = NULL);
	virtual ~CCitiesDlg();

// MFC Overrides
// ----------------
private:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();


// Methods
// ----------------
private:
	///<summary> Настройва всички Edit Boxes в диалога на Read Only режим </summary>
	void SetAllEdbToReadOnly();

	///<summary> Слага лимит на Edit Box-овете в диалога </summary>
	void SetAllEdbTextLimits();

	///<summary> Инициализира всички контроли в диалога спрямо типа </summary>
	void InitDialogControls(const ModificationTypes& eModificationType);

	///<summary> Инициализира диалог в режим View </summary>
	void OnViewDlg();

	///<summary> Инициализира диалог в режим Insert </summary>
	void OnInsertDlg();

	///<summary> Инициализира диалог в режим Edit </summary>
	void OnEditDlg();

	///<summary> Проверява дали данните за града са валидни </summary>
	///<return> Връща TRUE, ако са валидни и FALSE, ако не са </summary>
	BOOL IsCityValid();

// Members
// ----------------
private:
	//Control Variables
	CAlphabeticEdit m_edbCityName;
	CAlphabeticEdit m_edbCityRegion;
	CButton m_btnCityOk;
	CButton m_btnCityCancel;

	//Data Variables
	CITIES& m_oCities;
	ModificationTypes m_eModificationType;

};

