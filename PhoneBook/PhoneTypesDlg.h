#pragma once
#include "afxwin.h"
#include "Structures.h"
#include "ModifyRecordUtilites.h"
#include "AlphabeticEdit.h"
#include "DlgUtilities.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDlg

class CPhoneTypesDlg : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPhoneTypesDlg)
	DECLARE_MESSAGE_MAP()

// Constants
// ----------------
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PHONE_TYPES };
#endif

//Dialog Titles
#define PHONE_TYPES_DLG_CAPTION_VIEW "Phone Type Info"
#define PHONE_TYPES_DLG_CAPTION_INSERT "Add Phone Type"
#define PHONE_TYPES_DLG_CAPTION_UPDATE "Edit Phone Type"

// Constructor / Destructor
// ----------------
public:
	CPhoneTypesDlg(CWnd* pParent = NULL) = delete;
	CPhoneTypesDlg(const ModificationTypes& eModificationType, PHONE_TYPES& oPhoneTypes, CWnd* pParent = NULL);
	virtual ~CPhoneTypesDlg();

// MFC Overrides
// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

// Methods
// ----------------
private:
	///<summary> Инициализира всички контроли в диалога спрямо типа му </summary>
	void InitDialogControls(const ModificationTypes& eModificationType);

	///<summary> Инициализира диалог в режим View </summary>
	void OnViewDlg();

	///<summary> Инициализира диалог в режим Insert </summary>
	void OnInsertDlg();

	///<summary> Инициализира диалог в режим Edit </summary>
	void OnEditDlg();

	///<summary> Проверява дали извлечената ифнормация в oPhoneTypes е празна </summary>
	BOOL IsPhoneTypeEmpty();

// Members
// ----------------
private:
	// Control Variables
	CAlphabeticEdit m_edbPhoneTypesType;
	CButton m_btnPhoneTypesOk;
	CButton m_btnPhoneTypesCancel;
	
	// Data Variables
	PHONE_TYPES& m_oPhoneTypes;
	ModificationTypes m_eModificationType;
};
