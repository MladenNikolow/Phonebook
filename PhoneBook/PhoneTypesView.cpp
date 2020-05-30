#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "PhoneBookApp.h"
#endif

#include "PhoneTypesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CCitiesView

// Macros
// ----------------
IMPLEMENT_DYNCREATE(CPhoneTypesView, CListView)

BEGIN_MESSAGE_MAP(CPhoneTypesView, CListView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_ITEMACTIVATE, &CPhoneTypesView::OnLvnItemActivate)

	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_POPUP_DELETE, &CPhoneTypesView::OnContextMenuDelete)
	ON_COMMAND(ID_POPUP_VIEW, &CPhoneTypesView::OnContextMenuView)
	ON_COMMAND(ID_POPUP_EDIT, &CPhoneTypesView::OnContextMenuEdit)
	ON_COMMAND(ID_POPUP_INSERT, &CPhoneTypesView::OnContextMenuInsert)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CBaseView::OnLvnColumnclick)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------

CPhoneTypesView::CPhoneTypesView()
{
}

CPhoneTypesView::~CPhoneTypesView()
{
}

// Methods
// ----------------
void CPhoneTypesView::AddListCtrlItem(const PHONE_TYPES& oPhoneTypes, const INT_PTR& nItemData)
{
	CListCtrl& oListCtrl = GetListCtrl();
	INT_PTR nIndex = oListCtrl.InsertItem(NULL, oPhoneTypes.szPhoneType);
	oListCtrl.SetItemData(nIndex, nItemData);
}

void CPhoneTypesView::EditListCtrlRow(const PHONE_TYPES& oPhoneTypes, const INT_PTR& nListIndex)
{
	CListCtrl& oListCtrl = GetListCtrl();

	oListCtrl.SetItemText(nListIndex, NULL, oPhoneTypes.szPhoneType);
}

void CPhoneTypesView::InitializeListCtrl()
{
	CListCtrl& oListCtrl = GetListCtrl();
	oListCtrl.ModifyStyle(NULL, LVS_SINGLESEL, NULL);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	oListCtrl.InsertColumn(NULL, LSC_PHONE_TYPES_COLUMN_TYPE, LVCFMT_CENTER, LSC_PHONE_TYPES_COLUMN_WIDTH);

	CPhoneTypesDocument* pDoc = GetDocument();
	const CPhoneTypesArray& oPhoneTypesArray = pDoc->GetAllRecords();

	int nIndex = 0;
	for (INT_PTR i = 0; i < oPhoneTypesArray.GetCount(); ++i)
	{
		AddListCtrlItem((*oPhoneTypesArray.GetAt(i)), i);
	}
}
