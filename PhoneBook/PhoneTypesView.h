#pragma once

#include "BaseView.h"
#include "PhoneTypesDlg.h"
#include "PhoneTypesDocument.h"
#include "ContextMenu.h"
#include "ModifyRecordUtilites.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesView

class CPhoneTypesView : public CBaseView <PHONE_TYPES, CPhoneTypesDocument, CPhoneTypesDlg>
{
// Macros
// ----------------
protected:
	DECLARE_DYNCREATE(CPhoneTypesView)
	DECLARE_MESSAGE_MAP()

// Constants
// ----------------
private:
#define LSC_PHONE_TYPES_COLUMN_WIDTH 200
#define LSC_PHONE_TYPES_COLUMN_TYPE "Phone Type"

// Constructor / Destructor
// ----------------
protected:
	CPhoneTypesView();
	virtual ~CPhoneTypesView();

// Methods
// ----------------
private:
	///<summary> Инициализира стойностите за редовете и колоните на List Ctrl-a </summary>
	void InitializeListCtrl();

	///<summary> Добавя нов ред с инфо за Phone Type и Data към него - индекс от CCitiesDocument::m_oAllPhoneTypes </summary>
	void AddListCtrlItem(const PHONE_TYPES& oPhoneTypes, const INT_PTR& nItemData);

	///<summary> Променя текста за определен ред в List Ctrl-a </summary>
	void EditListCtrlRow(const PHONE_TYPES& oPhoneTypes, const INT_PTR& nListIndex);

};


