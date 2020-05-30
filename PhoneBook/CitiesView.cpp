#include "stdafx.h"
#include "CitiesTable.h"
#ifndef SHARED_HANDLERS
#include "PhoneBookapp.h"
#endif

#include "CitiesDocument.h"
#include "CitiesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CCitiesView
IMPLEMENT_DYNCREATE(CCitiesView, CListView)

BEGIN_MESSAGE_MAP(CCitiesView, CListView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_ITEMACTIVATE, &CBaseView::OnLvnItemActivate)

	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_POPUP_DELETE, &CBaseView::OnContextMenuDelete)
	ON_COMMAND(ID_POPUP_VIEW, &CBaseView::OnContextMenuView)
	ON_COMMAND(ID_POPUP_EDIT, &CBaseView::OnContextMenuEdit)
	ON_COMMAND(ID_POPUP_INSERT, &CBaseView::OnContextMenuInsert)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CBaseView::OnLvnColumnclick)
END_MESSAGE_MAP()



// Constructor / Destructor
// ----------------

CCitiesView::CCitiesView()
{
}

CCitiesView::~CCitiesView()
{
}

// Methods
// ----------------
void CCitiesView::InitializeListCtrl()
{
	CListCtrl& oListCtrl = GetListCtrl();
	oListCtrl.ModifyStyle(NULL, LVS_SINGLESEL, NULL);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	oListCtrl.InsertColumn(LscCityColumnName, LSC_CITIES_COLUMN_NAME, LVCFMT_CENTER, LSC_CITIES_COLUMN_WIDTH);
	oListCtrl.InsertColumn(LscCityColumnName, LSC_CITIES_COLUMN_REGION, LVCFMT_CENTER, LSC_CITIES_COLUMN_WIDTH);

	CCitiesDocument* pDoc = GetDocument();
	const CCitiesArray& oCitiesArray = pDoc->GetAllRecords();

	int nIndex = 0;
	for (INT_PTR i = 0; i < oCitiesArray.GetCount(); ++i)
	{
		AddListCtrlItem((*oCitiesArray.GetAt(i)), i);
	}
}
void CCitiesView::AddListCtrlItem(const CITIES& oCities, const INT_PTR& nItemData)
{
	CListCtrl& oListCtrl = GetListCtrl();
	INT_PTR nIndex = oListCtrl.InsertItem(LscCityColumnName, oCities.szName);
	oListCtrl.SetItemText(nIndex, LscCityColumnRegion, oCities.szRegion);
	oListCtrl.SetItemData(nIndex, nItemData);
}

void CCitiesView::EditListCtrlRow(const CITIES& oCity, const INT_PTR& nListIndex)
{
	CListCtrl& oListCtrl = CBaseView::GetListCtrl();

	oListCtrl.SetItemText(nListIndex, LscCityColumnName, oCity.szName);
	oListCtrl.SetItemText(nListIndex, LscCityColumnRegion, oCity.szRegion);
}






