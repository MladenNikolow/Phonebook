#include "stdafx.h"
#include "CitiesTable.h"
#include "DataBase.h"
#include <sstream>

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

// Constructor / Destructor
// ----------------
CCitiesTable::CCitiesTable() : CBaseTable(CitiesTableName)
{
	InitFieldsLengthAndStatus();
}

CCitiesTable::CCitiesTable(CSession& oSession) : CBaseTable(CitiesTableName, oSession)
{
}

CCitiesTable::~CCitiesTable()
{
}

// Overrides
// ----------------
void CCitiesTable::GetInfoFromRow(CITIES& oCities) const
{
	oCities.lId = m_ID;
	oCities.lUpdateCounter = m_UPDATE_COUNTER;
	_tcscpy_s(oCities.szName, m_NAME);
	_tcscpy_s(oCities.szRegion, m_REGION);
}

void CCitiesTable::SetInfoForRow(const CITIES& oCities)
{
	m_ID = oCities.lId;
	m_UPDATE_COUNTER = oCities.lUpdateCounter;
	_tcscpy_s(m_NAME, sizeof(m_NAME), oCities.szName);
	_tcscpy_s(m_REGION, sizeof(m_REGION), oCities.szRegion);
}

void CCitiesTable::InitFieldsLengthAndStatus()
{
	m_dwIDLength = sizeof(long);
	m_dwNAMELength = CITY_NAME_LENGTH;
	m_dwREGIONLength = REGION_NAME_LENGTH;
	m_dwUPDATE_COUNTERLength = sizeof(long);

	m_dwIDStatus = DBSTATUS_S_OK;
	m_dwNAMEStatus = DBSTATUS_S_OK;
	m_dwREGIONStatus = DBSTATUS_S_OK;
	m_dwUPDATE_COUNTERStatus = DBSTATUS_S_OK;
}

long& CCitiesTable::GetUpdateCounterValue(const CITIES& oRow)
{
	return (long&)*((char*)&oRow + offsetof(CITIES, lUpdateCounter));
}