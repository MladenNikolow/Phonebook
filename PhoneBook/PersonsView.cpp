#include "stdafx.h"
#include "PersonsDocument.h"
#include "PhoneBookApp.h"
#include "PersonsView.h"
#include "ContextMenu.h"
#include "PersonsDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsView

// Macros
// ----------------
IMPLEMENT_DYNCREATE(CPersonsView, CListView)

BEGIN_MESSAGE_MAP(CPersonsView, CListView)

	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_POPUP_DELETE, &CPersonsView::OnContextMenuDelete)
	ON_COMMAND(ID_POPUP_VIEW, &CPersonsView::OnContextMenuView)
	ON_COMMAND(ID_POPUP_EDIT, &CPersonsView::OnContextMenuEdit)
	ON_COMMAND(ID_POPUP_INSERT, &CPersonsView::OnContextMenuInsert)
	ON_NOTIFY_REFLECT(LVN_ITEMACTIVATE, &CPersonsView::OnLvnItemActivate)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CPersonsView::OnLvnColumnclick)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPersonsView::CPersonsView()
{
}

CPersonsView::~CPersonsView()
{
}

// MFC Overrides
// ----------------
BOOL CPersonsView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}

void CPersonsView::OnInitialUpdate()
{
	SetStylesOfListCtrl();
	SetListCtrlColumns();
	InitializeListCtrl();

	CListView::OnInitialUpdate();
}

void CPersonsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (!pHint)
	{
		return;
	}

	CContact& oContact = (CContact&)*pHint;

	switch (lHint)
	{
	case ModificationTypeEdit:
		EditListCtrlItem(oContact);
		break;

	case ModificationTypeDelete:
		DeleteListCtrlItem(oContact);
		break;

	case ModificationTypeInsert:
		InsertListCtrlItem(oContact);
		break;

	default:
		break;
	}

}

#ifdef _DEBUG
void CPersonsView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonsView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// Methods
// ----------------
void CPersonsView::SetListCtrlColumns()
{
	CListCtrl& oListCtrl = GetListCtrl();

	oListCtrl.InsertColumn(LscPersonColumnFirstName, LSC_PERSONS_COLUMN_FIRST_NAME, LVCFMT_CENTER, LSC_PERSONS_COLUMN_WIDTH);
	oListCtrl.InsertColumn(LscPersonColumnMiddleName, LSC_PERSONS_COLUMN_MIDDLE_NAME, LVCFMT_CENTER, LSC_PERSONS_COLUMN_WIDTH);
	oListCtrl.InsertColumn(LscPersonColumnLastName, LSC_PERSONS_COLUMN_LAST_NAME, LVCFMT_CENTER, LSC_PERSONS_COLUMN_WIDTH);
	oListCtrl.InsertColumn(LscPersonColumnCity, LSC_PERSONS_COLUMN_CITY, LVCFMT_CENTER, LSC_PERSONS_COLUMN_WIDTH);
	oListCtrl.InsertColumn(LscPersonColumnUcn, LSC_PERSONS_COLUMN_UCN, LVCFMT_CENTER, LSC_PERSONS_COLUMN_WIDTH);
}

void CPersonsView::SetStylesOfListCtrl()
{
	CListCtrl& oListCtrl = GetListCtrl();
	oListCtrl.ModifyStyle(NULL, LVS_SINGLESEL, NULL);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

void CPersonsView::InitializeListCtrl()
{
	CPersonsDocument* pDocument = (CPersonsDocument*)GetDocument();
	const CPersonsArray& oPersonsArray = pDocument->GetAllRecords();
	
	for (INT_PTR i = 0; i < oPersonsArray.GetCount(); ++i)
	{
		AddListCtrlItem((*oPersonsArray.GetAt(i)), i);
	}
}

BOOL CPersonsView::GetCityInfo(const long& lCityId, CString& strCityInfo)
{
	CPersonsDocument* pDocument = (CPersonsDocument*)GetDocument();
	const CITIES* pCity = pDocument->GetPersonCity(lCityId);

	if (!pCity)
		return FALSE;

	strCityInfo.Format(pCity->szName);
	strCityInfo.Append(", ");
	strCityInfo.Append(pCity->szRegion);

	return TRUE;
}

void CPersonsView::AddListCtrlItem(const PERSONS& oPersons, const INT_PTR& nItemData)
{
	CListCtrl& oListCtrl = GetListCtrl();
	INT_PTR nIndex = oListCtrl.InsertItem(LscPersonColumnFirstName, oPersons.szFirstName);

	oListCtrl.SetItemText(nIndex, LscPersonColumnMiddleName, oPersons.szMiddleName);
	oListCtrl.SetItemText(nIndex, LscPersonColumnLastName, oPersons.szLastName);

	//Добавяне на града
	CString strCityInfo;
	GetCityInfo(oPersons.lCityId, strCityInfo);
	oListCtrl.SetItemText(nIndex, LscPersonColumnCity, strCityInfo);

	oListCtrl.SetItemText(nIndex, LscPersonColumnUcn, oPersons.szUcn);
	oListCtrl.SetItemData(nIndex, nItemData);
}

BOOL CPersonsView::IsSelectedItem()
{
	CListCtrl& oListCtrl = GetListCtrl();

	if (!oListCtrl.GetFirstSelectedItemPosition())
	{
		return FALSE;
	}

	return TRUE;
}

INT_PTR CPersonsView::GetDataOfSelectedItem() const
{
	CListCtrl& oListCtrl = GetListCtrl();

	POSITION oSelectedItemPosition = oListCtrl.GetFirstSelectedItemPosition();

	return oListCtrl.GetItemData(oListCtrl.GetNextSelectedItem(oSelectedItemPosition));
}

PERSONS& CPersonsView::GetSelectedItem() const
{
	INT_PTR nArrayIndexOfSelectedPerson = GetDataOfSelectedItem();
	CPersonsDocument* pDocument = (CPersonsDocument*)GetDocument();
	PERSONS* pSelectedPerson = pDocument->GetAllRecords().GetAt(nArrayIndexOfSelectedPerson);

	return (*pSelectedPerson);
}

BOOL CPersonsView::CreateContact(CContact& oContact)
{
	CPersonsDocument* pDocument = (CPersonsDocument*)GetDocument();

	PERSONS oPersons = GetSelectedItem();
	INT_PTR nPersonsIndex = GetDataOfSelectedItem();

	CPhoneNumbersArray oPhoneNumbersArray;
	if (!pDocument->GetAllPhoneNumbersOfPerson(oPersons.lId, oPhoneNumbersArray))
	{
		AfxMessageBox(LOAD_PHONE_NUMBERS_ERROR);
		return FALSE;
	}

	CContact oNewContact(oPersons, oPhoneNumbersArray, nPersonsIndex);
	oContact.Copy(oNewContact);
}

void CPersonsView::OnView()
{
	CContact oContact;
	if (!CreateContact(oContact))
		return;

	CPersonsDocument* pDocument = (CPersonsDocument*)GetDocument();
	CPersonsDlg oPersonsDlg(ModificationTypeNone, oContact , pDocument->GetAllCities() , pDocument->GetAllPhoneTypes());

	oPersonsDlg.DoModal();
}

void CPersonsView::OnDelete()
{
	PERSONS oPersons = GetSelectedItem();

	CString strDeleteMessage = BOX_MESSAGE_DELETE_CONTACT_TEXT;
	strDeleteMessage.Replace("{PERSON_NAME}", oPersons.szFirstName);
	int nMessageBoxRespone = MessageBox(strDeleteMessage, BOX_MESSAGE_DELETE_CONTACT_CAPTION, MB_OKCANCEL);

	if (nMessageBoxRespone == IDCANCEL)
		return;

	CContact oContact;
	if (!CreateContact(oContact))
		return;

	CPersonsDocument* pDocument = (CPersonsDocument*)GetDocument();
	if (!pDocument->DeleteRecord(oContact))
	{
		AfxMessageBox(ERROR_MESSAGE_MODIFY_PERSONS);
	}
}

void CPersonsView::OnEdit()
{
	CContact oContact;
	if (!CreateContact(oContact))
		return;

	CPersonsDocument* pDocument = (CPersonsDocument*)GetDocument();
	
	CPersonsDlg oPersonsDlg(ModificationTypeEdit, oContact, pDocument->GetAllCities(), pDocument->GetAllPhoneTypes());

	INT_PTR nDlgResult = oPersonsDlg.DoModal();

	if (nDlgResult == IDCANCEL)
		return;

	if(!pDocument->UpdateRecord(oContact))
	{
		AfxMessageBox(ERROR_MESSAGE_MODIFY_PERSONS);
	}
}

void CPersonsView::OnInsert()
{
	PERSONS oPersons;
	CPhoneNumbersArray oPhoneNumbersArray;
	CContact oContact;

	CPersonsDocument* pDocument = (CPersonsDocument*)GetDocument();

	CPersonsDlg oPersonsDlg(ModificationTypeInsert, oContact, pDocument->GetAllCities(), pDocument->GetAllPhoneTypes());
	INT_PTR nDlgResponse = oPersonsDlg.DoModal();

	if (nDlgResponse == IDCANCEL)
		return;

	if (!pDocument->InsertRecord(oContact))
	{
		AfxMessageBox(ERROR_MESSAGE_MODIFY_PERSONS);
	}

}

INT_PTR CPersonsView::FindListCtrlItemWhereData(const LPARAM& lParam)
{
	CListCtrl& oListCtrl = GetListCtrl();

	LVFINDINFOA oSearchedItem;
	oSearchedItem.flags = LVFI_PARAM;
	oSearchedItem.lParam = lParam;

	return oListCtrl.FindItem(&oSearchedItem);
}

void CPersonsView::ChangeItemsDataAfterDelete(INT_PTR& nIndex)
{
	CListCtrl& oListCtrl = GetListCtrl();

	int nItemData = 0;
	for (int i = --nIndex; i >= 0; --i)
	{
		nItemData = oListCtrl.GetItemData(i);
		oListCtrl.SetItemData(i, (--nItemData));
	}
}

void CPersonsView::EditListCtrlRow(const PERSONS& oPersons, const INT_PTR& nListIndex)
{
	CListCtrl& oListCtrl = GetListCtrl();

	oListCtrl.SetItemText(nListIndex, LscPersonColumnFirstName, oPersons.szFirstName);
	oListCtrl.SetItemText(nListIndex, LscPersonColumnMiddleName, oPersons.szMiddleName);
	oListCtrl.SetItemText(nListIndex, LscPersonColumnLastName, oPersons.szLastName);

	CString strCityInfo;
	GetCityInfo(oPersons.lCityId, strCityInfo);
	oListCtrl.SetItemText(nListIndex, LscPersonColumnCity, strCityInfo);

	oListCtrl.SetItemText(nListIndex, LscPersonColumnUcn, oPersons.szUcn);
}

void CPersonsView::DeleteListCtrlItem(const CContact& oContact)
{
	CListCtrl& oListCtrl = GetListCtrl();

	INT_PTR nListIndex = FindListCtrlItemWhereData(oContact.nPersonsArrayIndex);
	oListCtrl.DeleteItem(nListIndex);

	ChangeItemsDataAfterDelete(nListIndex);
}

void CPersonsView::EditListCtrlItem(const CContact& oContact)
{
	CListCtrl& oListCtrl = GetListCtrl();
	CPersonsDocument* pDocument = (CPersonsDocument*)GetDocument();

	INT_PTR nPersonsArrayIndex = oContact.nPersonsArrayIndex;
	const CPersonsArray& oPersonsArray = pDocument->GetAllRecords();
	PERSONS* pPersons = oPersonsArray.GetAt(nPersonsArrayIndex);

	INT_PTR nListCtrlIndex = FindListCtrlItemWhereData(nPersonsArrayIndex);

	EditListCtrlRow(*pPersons, nListCtrlIndex);
}

void CPersonsView::InsertListCtrlItem(const CContact& oContact)
{
	CListCtrl& oListCtrl = GetListCtrl();
	CPersonsDocument* pDocument = (CPersonsDocument*)GetDocument();

	const CPersonsArray& oAllPersons = pDocument->GetAllRecords();
	PERSONS* pPersons = oAllPersons.GetAt(oContact.nPersonsArrayIndex);

	AddListCtrlItem(*pPersons, oContact.nPersonsArrayIndex);
}

// MFC Message Handlers
// ----------------
void CPersonsView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CContextMenu oContextMenu;

	if (IsSelectedItem())
	{
		oContextMenu.InitializeMenu(ContextMenuModify);

	}
	else
	{
		oContextMenu.InitializeMenu(ContextMenuAdd);
	}

	oContextMenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}

void CPersonsView::OnContextMenuView()
{
	OnView();
}

void CPersonsView::OnContextMenuDelete()
{
	OnDelete();
}

void CPersonsView::OnContextMenuEdit()
{
	OnEdit();
}

void CPersonsView::OnContextMenuInsert()
{
	OnInsert();
}

void CPersonsView::OnLvnItemActivate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnView();
	*pResult = 0;
}

int CALLBACK CPersonsView::CompareListCtrlItemsAlphabetically(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	LVITEM& oFirstItem = (LVITEM&)lParam1;
	LVITEM& oSecondItem = (LVITEM&)lParam2;

	SortViewInfo* pSortViewInfo = (SortViewInfo*)lParamSort;

	const CListCtrl& oListCtrl = pSortViewInfo->oListCtrl;
	INT_PTR nColumnIndex = pSortViewInfo->nColumnIndex;

	CString strFirstItemText = oListCtrl.GetItemText(lParam1, nColumnIndex);
	CString strSecondItemText = oListCtrl.GetItemText(lParam2, nColumnIndex);

	int nResult = strcmp(strFirstItemText, strSecondItemText);
	return nResult;
}

void CPersonsView::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	SortByColumnAlphabetically(pNMLV);
	
	*pResult = 0;
}

void CPersonsView::SortByColumnAlphabetically(const LPNMLISTVIEW& pNMLV)
{
	CListCtrl& oListCtrl = GetListCtrl();
	SortViewInfo oSortViewInfo(oListCtrl, pNMLV->iSubItem);

	if (!oListCtrl.SortItemsEx(&CompareListCtrlItemsAlphabetically, (DWORD_PTR)&oSortViewInfo))
		AfxMessageBox("An error occurred while sorting the data!");
}