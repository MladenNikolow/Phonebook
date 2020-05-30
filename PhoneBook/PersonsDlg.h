#pragma once
#include "afxwin.h"
#include "Contact.h"
#include "ModifyRecordUtilites.h"
#include "ContextMenu.h"
#include "AlphabeticEdit.h"
#include "NumericEdit.h"
#include "DlgUtilities.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDlg

///<summary> Диалог за PERSONS </summary>
class CPersonsDlg : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPersonsDlg)
	DECLARE_MESSAGE_MAP()

// Constants
// ----------------
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PERSONS };
#endif

//Dialog Titles
#define PERSONS_DIALOG_CAPTION_VIEW "Contact Info"
#define PERSONS_DIALOG_CAPTION_INSERT "Add Contact"
#define PERSONS_DIALOG_CAPTION_EDIT "Edit Contact"

// Lsc Phone Numbers
#define LSC_PHONE_NUMBERS_COLUMN 0

// Cmb Phone Types
#define CMB_PHONE_TYPES_ALL_TEXT "All"
#define CMB_PHONE_TYPES_ALL_DATA -4 // -1, -2 и -3 са използвани за други return values в CComboBox

// Message Box Texts
#define MESSAGE_BOX_DELETE_PHONE_NUMBER_TEXT "Are you sure you want to delete {PHONE_NUMBER} from your phone numbers?"
#define MESSAGE_BOX_DELETE_PHONE_NUMBER_CAPTION "Delete Phone Number"

// Constructor / Destructor
// ----------------
public:
	CPersonsDlg(CWnd* pParent = nullptr) = delete;

	CPersonsDlg(const ModificationTypes& eModificationType,
				CContact& oContact,
				const CMap<long, long&, CITIES, CITIES&>& oCitiesMap,
				const CPhoneTypesArray& oPhoneTypesArray,
				CWnd* pParent = nullptr);

	virtual ~CPersonsDlg();

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
	///<summary> Настройва всички контроли в режим Read Only или Disable Window </summary>
	void SetAllControlsToReadOnly();

	///<summary> Задава стойности на всички полета спрямо типа на диалога </summary>
	void InitializeDialog(const ModificationTypes& eModificationType);

	///<summary> Пълни m_cmbPersonsPhoneTypes с всички телефонни типове и селектира All </summary>
	void InitializePhoneTypesCmb();

	///<summary> Пълни m_cmbPersonsCities и селектира град спрямо режима на диалога <summary>
	void InitializeCityCmb();

	///<summary> Зарежда всички градове в m_cmbPersonsCities </summary>
	void LoadAllCities();

	///<summary> Настройва максималната дължина на текства във всички Edit boxes </summary>
	void SetLimitTextToAllEdb();

	///<summary> Взема селектирания тип телефони и запълва PhoneNumbersLsc с номерата </summary>
	void OnPhoneNumbersCtrlChange();

	///<summary> Инициализира List Control с всички номера от селектирания тип </summary>
	void InitializePhoneNumbersLsc(const INT_PTR& nPhoneTypesCmbIndex);

	///<summary> Взема името на града по дадено City Id </summary>
	///<return> Името на града като CString </summary>
	CString GetCityAndRegionAsString(const long& lCityId);

	///<summary> Взема имената на човека и ги събира в един стринг </summary>
	CString PrepareFullName();

	///<summary> Задава стойности на всички Edit Box-ове </summary>
	void InitializeAllEdb();

	///<summary> Инициализира контролите за прозорец, отворен в режим View </summary>
	void OnView();

	///<summary> Инициализира контролите за прозорец, отворен в режим Edit </summary>
	void OnEdit();

	///<summary> Инициализира контролите за прозорец, отворен в режим Insert </summary>
	void OnInsert();

	///<summary> Взема индекс на телефонния номер в контакта </summary>
	INT_PTR GetLscPhoneNumbersData() const;

	///<summary> Проверява дали е селектиран телефонен номер в m_lscPhoneNumbers</summary>
	///<return> Връща TRUE - ако има селектиран елемент и FALSE - ако няма </return>
	BOOL IsSelectedLscItem() const;

	///<summary> Взема селектирания елемент от m_lscPersonsPhoneNumbers </summary>
	PHONE_NUMBERS& GetSelectedPhoneNumber();

	///<summary> Търси елемент в m_lscPersonsPhoneNumbers по неговата data </summary>
	INT_PTR FindLscItemWhereData(const LPARAM& lParam);

	///<summary> Пенарежда данните за елементите в m_lscPersonsPhoneNumbers след изтриване </summary>
	void ChangeLscItemsDataAfterDelete(INT_PTR& nIndex);

	///<summary> Взема типът на даден номер </summary>
	CString GetPhoneTypeOfSelectedNumberAsString(const PHONE_NUMBERS& oPhoneNumbers);

	///<summary> Извлича информацията за човек от прозореца (вкл. копира update countera от m_oContact) </summary>
	///<return> Връща PERSON с входната информация </return>
	PERSONS ExtractPersonFromDlgControls();

	///<summary> Извлича име от стринг, след което го изтрива от стринга </summary>
	void ExtractName(CString& strName, TCHAR* pName);

	///<summary> Извлича цялото име на човека от прозореца </summary>
	void ExtractFullNameFromDlg(PERSONS& oPersons);

	///<summary> Проверява дали данните за човека са празни </summary>
	BOOL IsPersonsInfoEmpty();

	///<summary> Отваря диалог за селектирания номер в режим преглед </summary>
	void OnContextMenuView();

	///<summary> Отваря диалог за селектирания номер в режим редакция </summary>
	void OnContextMenuEdit();

	///<summary> Отваря Message Box за потвърждение на изтриването и изтрива номера </summary>
	void OnContextMenuDelete();

	///<summary> Отваря диалог за селектирания номер в режим добавяне </summary>
	void OnContextMenuInsert();


// MFC Message Handlers
// ----------------
private:
	afx_msg void OnCbnSelchangeCmbPhoneTypes();
	afx_msg void OnNMRClickLscPersonsPhoneNumbers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnItemActivateLscPersonsPhoneNumbers(NMHDR *pNMHDR, LRESULT *pResult);

// Members
// ----------------
private:
	// Control Variables
	CButton m_btnPersonsOk;
	CButton m_btnPersonsCancel;
	CAlphabeticEdit m_edbPersonsFullName;
	CNumericEdit m_edbPersonsUcn;
	CEdit m_edbPersonsAddress;
	CComboBox m_cmbPersonsCities;
	CComboBox m_cmbPersonsPhoneTypes;
	CListCtrl m_lscPersonsPhoneNumbers;

	// Data Varaibles
	const ModificationTypes m_eModificationType;
	const CMap<long, long&, CITIES, CITIES&>& m_oCitiesMap;
	const CPhoneTypesArray& m_oPhoneTypesArray;	
	CContact& m_oContact;
};
