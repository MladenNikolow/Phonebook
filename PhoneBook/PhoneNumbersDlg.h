#pragma once
#include "afxwin.h"
#include "ModifyRecordUtilites.h"
#include "Structures.h"
#include "Resource.h"
#include "DlgUtilities.h"
#include "NumericEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDlg

class CPhoneNumbersDlg : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPhoneNumbersDlg)
	DECLARE_MESSAGE_MAP()

// Constants
// ----------------
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PHONE_NUMBERS };
#endif

// Constructor / Destructor
// ----------------
public:
	CPhoneNumbersDlg(const ModificationTypes& eModificationType, 
					 PHONE_NUMBERS& oPhoneNumbers, 
					 const CPhoneTypesArray& oPhoneTypesArray,
					 CWnd* pParent = NULL);
	virtual ~CPhoneNumbersDlg();

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
	///<summary> Задава информацията за телефона: номер и вида му </summary>
	void SetPhoneNumberInfo();

	///<summary> Инициaлизира информацията за вида на номера </summary>
	void SetPhoneTypeInfo();

	///<summary> Взема типът телефон в текстов формат </summary>
	CString GetPhoneTypeOfNumber();

	///<summary> Инициализира диалог в режим View </summary>
	void OnInitViewDlg();

	///<summary> Инициализира диалог в режим Edit </summary>
	void OnInitEditDlg();

	///<summary> Инициализира диалог в режим Delete </summary>
	void OnInitInsertDlg();

	///<summary> Проверява дали m_oPhoneNumbers.szPhoneNumber е празен </summary>
	///<return> TRUE - ако е празен и FALSE - ако не е </return>
	BOOL IsPhoneNumberEmpty();

	///<summary> Проверява дали има селектиран елемент ot m_cmbPhoneNumbersType </summary>
	///<return> TRUE - е селектиран елемент и FALSE - ако не е </return>
	BOOL IsPhoneTypeSelected();

// Members
// ----------------
private:
	// Control Variables
	CComboBox m_cmbPhoneNumbersType;
	CNumericEdit m_edbPhoneNumber;
	CButton m_btnPhoneNumbersOk;
	CButton m_btnPhoneNumbersCancel;

	// Data Variables
	ModificationTypes m_eModificationType;
	PHONE_NUMBERS& m_oPhoneNumbers;
	const CPhoneTypesArray& m_oPhoneTypesArray;
};
