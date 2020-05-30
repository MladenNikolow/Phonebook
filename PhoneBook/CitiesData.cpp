#include "stdafx.h"
#include "CitiesData.h"
#include "CitiesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData

// Constructor / Destructor
// ----------------
CCitiesData::CCitiesData()
{
}

CCitiesData::~CCitiesData()
{
}

// Methods
// ----------------
BOOL CCitiesData::LoadAllRecords(CCitiesArray& oAllCities)
{
	CCitiesTable oCitiesTable;
	return oCitiesTable.SelectAll(oAllCities);
}

BOOL CCitiesData::LoadRecordWithSpecificId(const long& lId, CITIES& oCities)
{
	CCitiesTable oCitiesTable;
	return oCitiesTable.SelectWhereId(lId, oCities);
}

BOOL CCitiesData::AddRecord(const CITIES& oCities)
{
	CCitiesTable oCitiesTable;
	return oCitiesTable.Insert(const_cast<CITIES&>(oCities));
}

BOOL CCitiesData::UpdateRecord(CITIES& oCities)
{
	CCitiesTable oCitiesTable;
	return oCitiesTable.UpdateWhereId(oCities.lId, oCities);
}

BOOL CCitiesData::DeleteRecord(const CITIES& oCities)
{
	CCitiesTable oCitiesTable;
	return oCitiesTable.DeleteWhereId(oCities.lId);
}