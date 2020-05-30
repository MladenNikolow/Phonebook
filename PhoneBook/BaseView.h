#pragma once
#include "ModifyRecordUtilites.h"
#include "ContextMenu.h"
#include "CitiesDlg.h"
#include "ViewUtilities.h"

/////////////////////////////////////////////////////////////////////////////
// CBaseView

template <class BASE_TYPE, class BASE_DOCUMENT, class BASE_DIALOG>
class CBaseView : public CListView
{
// Macros
// ----------------

// Constants
// ----------------
private:
// On Delete
#define BOX_MESSAGE_DELETE_VIEW_RECORD_CAPTION "Delete Record"
#define BOX_MESSAGE_DELETE_VIEW_RECORD_TEXT "Are you sure you want to delete the selected item?"

// Error Messages
#define ERROR_MESSAGE_MODIFY_DATA "An error occurred while executing the request"

// Constructor / Destructor
// ----------------
public:
	CBaseView() {};
	virtual ~CBaseView() {}

// MFC Overrides
// ----------------
public:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override
	{
		ModifiedRecordInfo* pModifiedRecordInfo = (ModifiedRecordInfo*)lHint;
		if (!pModifiedRecordInfo)
		{
			return;
		}

		OnChange(*pModifiedRecordInfo);
	}

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override
	{
		cs.style |= LVS_REPORT;
		return CListView::PreCreateWindow(cs);
	}

	virtual void OnInitialUpdate() override
	{
		InitializeListCtrl();

		CListView::OnInitialUpdate();
	}

// Methods
// ----------------
	// Pure Virtual Methods
	virtual void InitializeListCtrl() = 0;

	virtual void AddListCtrlItem(const BASE_TYPE& oRecord, const INT_PTR& nItemData) = 0;

	virtual void EditListCtrlRow(const BASE_TYPE& oCity, const INT_PTR& nListIndex) = 0;
	
	// Base Methods
	BASE_DOCUMENT* GetDocument() const
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(BASE_DOCUMENT)));
		return (BASE_DOCUMENT*)m_pDocument;
	}

	BOOL IsSelectedItem()
	{
		CListCtrl& oListCtrl = GetListCtrl();

		if (!oListCtrl.GetFirstSelectedItemPosition())
		{
			return FALSE;
		}

		return TRUE;
	}

	INT_PTR GetDataOfSelectedItem()
	{
		CListCtrl& oListCtrl = GetListCtrl();

		POSITION oSelectedItemPosition = oListCtrl.GetFirstSelectedItemPosition();

		return oListCtrl.GetItemData(oListCtrl.GetNextSelectedItem(oSelectedItemPosition));
	}

	BASE_TYPE GetSelectedItem()
	{
		INT_PTR nArrayIndexOfSelectedItem = GetDataOfSelectedItem();

		BASE_TYPE* pSelectedRecord = GetDocument()->GetAllRecords().GetAt(nArrayIndexOfSelectedItem);

		return (*pSelectedRecord);
	}

	INT_PTR FindListCtrlItemWhereData(const LPARAM& lParam)
	{
		CListCtrl& oListCtrl = GetListCtrl();

		LVFINDINFOA oSearchedItem;
		oSearchedItem.flags = LVFI_PARAM;
		oSearchedItem.lParam = lParam;

		return oListCtrl.FindItem(&oSearchedItem);
	}

	void ChangeItemsDataAfterDelete(INT_PTR& nIndex)
	{
		CListCtrl& oListCtrl = GetListCtrl();

		int nItemData = 0;
		for (int i = --nIndex; i >= 0; --i)
		{
			nItemData = oListCtrl.GetItemData(i);
			oListCtrl.SetItemData(i, (--nItemData));
		}
	}


	void OnChange(const ModifiedRecordInfo& oModifiedRecordInfo)
	{
		switch (oModifiedRecordInfo.eModificationType)
		{
		case ModificationTypeInsert:
			InsertListCtrlItem(oModifiedRecordInfo);
			break;

		case ModificationTypeEdit:
			EditListCtrlItem(oModifiedRecordInfo);
			break;

		case ModificationTypeDelete:
			DeleteListCtrlItem(oModifiedRecordInfo);
			break;

		default:
			break;
		}
	}

	void EditListCtrlItem(const ModifiedRecordInfo& oModifiedRecordInfo)
	{
		CListCtrl& oListCtrl = GetListCtrl();

		const CTypedAutoPtrArray<BASE_TYPE>& oBaseTypeArray = GetDocument()->GetAllRecords();
		BASE_TYPE* pRecord = oBaseTypeArray.GetAt(oModifiedRecordInfo.nArrayIndex);

		INT_PTR nListIndex = FindListCtrlItemWhereData(oModifiedRecordInfo.nArrayIndex);

		EditListCtrlRow(*pRecord, nListIndex);
	}

	void InsertListCtrlItem(const ModifiedRecordInfo& oModifiedRecordInfo)
	{
		CListCtrl& oListCtrl = GetListCtrl();

		const CTypedAutoPtrArray<BASE_TYPE>& oBaseTypeArray = GetDocument()->GetAllRecords();
		BASE_TYPE* pRecord = oBaseTypeArray.GetAt(oModifiedRecordInfo.nArrayIndex);

		AddListCtrlItem(*pRecord, oModifiedRecordInfo.nArrayIndex);
	}

	void DeleteListCtrlItem(const ModifiedRecordInfo& oModifiedRecordInfo)
	{
		CListCtrl& oListCtrl = GetListCtrl();

		INT_PTR nListIndex = FindListCtrlItemWhereData(oModifiedRecordInfo.nArrayIndex);
		oListCtrl.DeleteItem(nListIndex);

		ChangeItemsDataAfterDelete(nListIndex);
	}

	template <class BASE_DIALOG>
	void OnView()
	{
		BASE_TYPE oBaseType = GetSelectedItem();

		BASE_DIALOG oCitiesDlg(ModificationTypeNone, oBaseType);

		INT_PTR nCitiesDlgResponse = oCitiesDlg.DoModal();
	}

	template <class BASE_DIALOG>
	void OnEdit()
	{
		BASE_TYPE oBaseType = GetSelectedItem();
		INT_PTR nArrayIndexOfSelectedItem = GetDataOfSelectedItem();

		//Зареждам отново данните за маркирания елемент от базата данни, 
		//за да се намали шанса за провал на Update операцията
		BASE_DOCUMENT* pDocument = (BASE_DOCUMENT*)GetDocument();
		if (!pDocument->GetRecord(oBaseType.lId, oBaseType))
			return;

		BASE_DIALOG oCitiesDlg(ModificationTypeEdit, oBaseType);

		INT_PTR nCitiesDlgResponse = oCitiesDlg.DoModal();

		if (nCitiesDlgResponse != IDOK)
			return;

		if(!pDocument->UpdateRecord(oBaseType, nArrayIndexOfSelectedItem))
			AfxMessageBox(ERROR_MESSAGE_MODIFY_DATA);
	}

	template <class BASE_DIALOG>
	void OnInsert()
	{
		BASE_TYPE oBaseType;

		BASE_DIALOG oCitiesDlg(ModificationTypeInsert, oBaseType);

		INT_PTR nCitiesDlgResponse = oCitiesDlg.DoModal();

		if (nCitiesDlgResponse != IDOK)
		{
			return;
		}

		BASE_DOCUMENT* pDocument = (BASE_DOCUMENT*)GetDocument();

		if (!pDocument->AddRecord(oBaseType))
			AfxMessageBox(ERROR_MESSAGE_MODIFY_DATA);
	}

	void OnDelete()
	{
		int nMessageBoxRespone = MessageBox(BOX_MESSAGE_DELETE_VIEW_RECORD_TEXT, BOX_MESSAGE_DELETE_VIEW_RECORD_CAPTION, MB_OKCANCEL);

		if (nMessageBoxRespone != IDOK)
			return;

		INT_PTR nArrayIndexOfSelectedItem = GetDataOfSelectedItem();
		BASE_DOCUMENT* pDocument = (BASE_DOCUMENT*)GetDocument();

		if (!pDocument->DeleteRecord(nArrayIndexOfSelectedItem))
			AfxMessageBox(ERROR_MESSAGE_MODIFY_DATA);
	}

// MFC Message Handlers
// ----------------
	void OnLvnItemActivate(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

		OnView<BASE_DIALOG>();

		*pResult = 0;
	}

	void OnContextMenu(CWnd* pWnd, CPoint point)
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

	void OnContextMenuView()
	{
		OnView<BASE_DIALOG>();
	}

	void OnContextMenuDelete()
	{
		OnDelete();
	}

	void OnContextMenuEdit()
	{
		OnEdit<BASE_DIALOG>();
	}

	void OnContextMenuInsert()
	{
		OnInsert<BASE_DIALOG>();
	}

	static int CALLBACK CompareListCtrlItemsAlphabetically(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
	{
		SortViewInfo* pSortViewInfo = (SortViewInfo*)lParamSort;

		const CListCtrl& oListCtrl = pSortViewInfo->oListCtrl;
		INT_PTR nColumnIndex = pSortViewInfo->nColumnIndex;

		CString strFirstItemText = oListCtrl.GetItemText(lParam1, nColumnIndex);
		CString strSecondItemText = oListCtrl.GetItemText(lParam2, nColumnIndex);

		return strcmp(strFirstItemText, strSecondItemText);
	}

	void SortByColumnAlphabetically(const LPNMLISTVIEW& pNMLV)
	{
		CListCtrl& oListCtrl = GetListCtrl();
		SortViewInfo oSortViewInfo(oListCtrl, pNMLV->iSubItem);

		if (!oListCtrl.SortItemsEx(&CompareListCtrlItemsAlphabetically, (DWORD_PTR)&oSortViewInfo))
			AfxMessageBox("An error occurred while sorting the data!");
	}

	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

		SortByColumnAlphabetically(pNMLV);

		*pResult = 0;
	}

#ifdef _DEBUG
	virtual void AssertValid() const override
	{
		CListView::AssertValid();
	}

	virtual void Dump(CDumpContext& dc) const override
	{
		CListView::Dump(dc);
	}

#endif //_DEBUG
};
