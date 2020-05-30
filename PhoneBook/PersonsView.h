#pragma once
#include "Contact.h"
#include "ModifyRecordUtilites.h"
#include "ViewUtilities.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsView

class CPersonsView : public CListView
{
// Macros
// ----------------
protected:
	DECLARE_DYNCREATE(CPersonsView)
	DECLARE_MESSAGE_MAP()

// Constants
// ----------------
private:
//Lsc Persons Column Info
#define LSC_PERSONS_COLUMN_WIDTH 250

#define LSC_PERSONS_COLUMN_FIRST_NAME "First Name"
#define LSC_PERSONS_COLUMN_MIDDLE_NAME "Middle Name"
#define LSC_PERSONS_COLUMN_LAST_NAME "Last Name"
#define LSC_PERSONS_COLUMN_CITY "City"
#define LSC_PERSONS_COLUMN_UCN "UCN"

// On Delete Message
#define BOX_MESSAGE_DELETE_CONTACT_CAPTION "Delete Contact"
#define BOX_MESSAGE_DELETE_CONTACT_TEXT "Are you sure you want to delete {PERSON_NAME} from your contacts?"

// Error Messages
#define ERROR_MESSAGE_MODIFY_PERSONS "An error occurred while executing the request!"
#define LOAD_PHONE_NUMBERS_ERROR "An error occurred while loading the phone numbers!"

enum LscPersonColumns
{
	LscPersonColumnFirstName = 0,
	LscPersonColumnMiddleName = 1,
	LscPersonColumnLastName = 2,
	LscPersonColumnCity = 3,
	LscPersonColumnUcn = 4
};

// Constructor / Destructor
// ----------------
protected:
	CPersonsView();
public:
	virtual ~CPersonsView();

// MFC Overrides
// ----------------
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

// Methods
// ----------------
private:
	///<summary> Добавя колните за Person към List Ctrl-a </summary>
	void SetListCtrlColumns();

	///<summary> Задава стиловете на List Ctrl-a </summary>
	void SetStylesOfListCtrl();

	///<summary> Попълва всички редове с данните на Persons </summary>
	void InitializeListCtrl();

	///<summary> Взема информацията за град по неговото ID </summary>
	BOOL GetCityInfo(const long& lCityId, CString& strCityInfo);

	///<summary> Добавя нов ред с инфо за Person и Data към него - индекс от CPersonsDocument::m_oAllPersons </summary>
	void AddListCtrlItem(const PERSONS& oPersons, const INT_PTR& nItemData);

	///<summary> Проверява дали има селектиран елемент </summary>
	///<return> Връща TRUE - ако има селектиран елемент и FALSE - ако няма </return>
	BOOL IsSelectedItem();

	///<summary> Взема данните за селектиран елемент от ListCtrl-a </summary>
	INT_PTR GetDataOfSelectedItem() const;

	///<summary> Взема PERSONS за селектирания елемент от ListCtrl-a </summary>
	PERSONS& GetSelectedItem() const;

	///<summary> Отваря диалог в режим View с данните на маркирания човек </summary>
	void OnView();

	///<summary> Отваря диалог в режим Delete и при потвърждение извиква CPersonsDocument::DeleteRecord() </summary>
	void OnDelete();

	///<summary> Отваря диалог в режим Edit и при потвърждение извиква CPersonsDocument::EditRecord() </summary>
	void OnEdit();

	///<summary> Отваря диалог в режим Insert и при потвърждение извиква CPersonsDocument::AddRecord() </summary>
	void OnInsert();

	///<summary> Търси List Ctrl елемент по Item Data </summary>
	///<return> Връща индекс на намерения елемент в List Ctrl-a или -1, ако търсенето е неуспешно </return>
	INT_PTR FindListCtrlItemWhereData(const LPARAM& lParam);

	///<summary> След изтриване на елемент в List Ctrl-a, променя данните за всички елементи 
	/// с промеменени индекси в CPersonsDocument </summary>
	void ChangeItemsDataAfterDelete(INT_PTR& nIndex);

	///<summary> Променя данните за определен елемент в List Ctrl-a </summary>
	void EditListCtrlRow(const PERSONS& oPersons, const INT_PTR& nListIndex);

	///<summary> Намира модифицирания List Ctrl елемент и го променя във View-то </summary>
	void EditListCtrlItem(const CContact& oContact);

	///<summary> Намира изтрития контакт и го премахва от List Ctrl-a </summary>
	void DeleteListCtrlItem(const CContact& oContact);

	///<summary> Добава List Ctrl елемент </summary>
	void InsertListCtrlItem(const CContact& oContact);

	///<summary> Създава CContact обект за селектирания елемент </summary>
	///<return> TRUE - ако създаването е успешно и FALSE при възникнала грешка </return>
	BOOL CreateContact(CContact& oContact);

	///<summary> Сортира List Ctrl-a по селектираната колона </summary>
	void SortByColumnAlphabetically(const LPNMLISTVIEW& pNMLV);

	///<summary> Фунцкция за сравняване на два елемента във View-то. Извиква се от CListCtrl::SortItemsEx() </summary>
	static int CALLBACK CompareListCtrlItemsAlphabetically(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

// MFC Message Handlers
// ----------------
protected:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnContextMenuView();
	afx_msg void OnContextMenuEdit();
	afx_msg void OnContextMenuDelete();
	afx_msg void OnContextMenuInsert();
	afx_msg void OnLvnItemActivate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
};


