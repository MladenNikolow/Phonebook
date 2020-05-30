#include "stdafx.h"
#include "PhoneTypesTable.h"

// Constructor / Destructor
// ----------------
CPhoneTypesTable::CPhoneTypesTable() : CBaseTable(PhoneTypesTableName)
{
}

CPhoneTypesTable::CPhoneTypesTable(CSession& oSession) : CBaseTable(PhoneTypesTableName, oSession)
{
}

CPhoneTypesTable::~CPhoneTypesTable()
{
}

// Overrides
// ----------------
void CPhoneTypesTable::GetInfoFromRow(PHONE_TYPES& oRow) const
{
	oRow.lId = m_ID;
	oRow.lUpdateCounter = m_UPDATE_COUNTER;
	_tcscpy_s(oRow.szPhoneType, sizeof(oRow.szPhoneType), m_PHONE_TYPE);
}

void CPhoneTypesTable::SetInfoForRow(const PHONE_TYPES& oRow)
{
	m_ID = oRow.lId;
	m_UPDATE_COUNTER = oRow.lUpdateCounter;
	_tcscpy_s(m_PHONE_TYPE, sizeof(m_PHONE_TYPE), oRow.szPhoneType);
}

void CPhoneTypesTable::InitFieldsLengthAndStatus()
{
	m_dwIDLength = sizeof(long);
	m_dwUPDATE_COUNTERLength = sizeof(long);
	m_dwPHONE_TYPELength = PHONE_TYPE_LENGTH;

	m_dwIDStatus = DBSTATUS_S_OK;
	m_dwUPDATE_COUNTERStatus = DBSTATUS_S_OK;
	m_dwPHONE_TYPEStatus = DBSTATUS_S_OK;
}

long& CPhoneTypesTable::GetUpdateCounterValue(const PHONE_TYPES& oRow)
{
	return (long&)*((char*)&oRow + offsetof(PHONE_TYPES, lUpdateCounter));
}