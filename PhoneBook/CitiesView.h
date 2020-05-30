#pragma once

#include "BaseView.h"
#include "CitiesDlg.h"
#include "CitiesDocument.h"
#include "ContextMenu.h"
#include "ModifyRecordUtilites.h"



/////////////////////////////////////////////////////////////////////////////
// CCitiesView

class CCitiesView : public CBaseView <CITIES, CCitiesDocument, CCitiesDlg>
{
// Macros
// ----------------
protected:

	DECLARE_DYNCREATE(CCitiesView)
	DECLARE_MESSAGE_MAP()

// Constants
// ----------------
private:
#define LSC_CITIES_COLUMN_WIDTH 200
#define LSC_CITIES_COLUMN_NAME "Name"
#define LSC_CITIES_COLUMN_REGION "Region"

	enum LscCityColumns
	{
		LscCityColumnName = 0,
		LscCityColumnRegion = 1
	};

	// Constructor / Destructor
	// ----------------
protected:
	CCitiesView();
public:
	virtual ~CCitiesView();

// Methods
// ----------------
private:
	///<summary> Инициализира стойностите за редовете и колоните на List Ctrl-a </summary>
	virtual void InitializeListCtrl() override;

	///<summary> Добавя нов ред с инфо за City и Data към него - индекс от CCitiesDocument::m_oAllCities </summary>
	virtual void AddListCtrlItem(const CITIES& oCities, const INT_PTR& nItemData) override;

	///<summary> Променя данните за определен ред в List Ctrl-a </summary>
	virtual void EditListCtrlRow(const CITIES& oCity, const INT_PTR& nListIndex) override;

};

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCitiesDoc* CCitiesView::GetDocument() const
{
	return reinterpret_cast<CCitiesDoc*>(m_pDocument);
}
#endif
