#include "stdafx.h"
#include "PhoneNumbersTable.h"

// Constructor / Destructor
// ----------------
CPhoneNumbersTable::CPhoneNumbersTable() : CBaseTable(PhoneNumbersTableName)
{
	InitFieldsLengthAndStatus();
}

CPhoneNumbersTable::CPhoneNumbersTable(CSession& oSession) : CBaseTable(PhoneNumbersTableName, oSession)
{
}

CPhoneNumbersTable::~CPhoneNumbersTable()
{
}

// Overrides
// ----------------
BOOL CPhoneNumbersTable::SelectAllPhoneNumbersOfPersons(const long& lId, CPhoneNumbersArray& oPhoneNumbersArray)
{
	if (!SelectAllWhereForeignKey(PERSON_ID, lId, oPhoneNumbersArray))
		return FALSE;

	return TRUE;
}

BOOL CPhoneNumbersTable::DeleteAllPhoneNumbersOfPersons(const long& lId)
{
	if (!DeleteAllWhereForeignKey(PERSON_ID, lId))
		return FALSE;

	return TRUE;
}

void CPhoneNumbersTable::GetInfoFromRow(PHONE_NUMBERS& oRow) const
{
	oRow.lId = m_ID;
	oRow.lUpdateCounter = m_UPDATE_COUNTER;
	oRow.lPersonId = m_PERSON_ID;
	oRow.lPhoneTypeId = m_PHONE_TYPE_ID;
	_tcscpy_s(oRow.szPhoneNumber, sizeof(oRow.szPhoneNumber), m_PHONE_NUMBER);
}

void CPhoneNumbersTable::SetInfoForRow(const PHONE_NUMBERS& oRow)
{
	m_ID = oRow.lId;
	m_UPDATE_COUNTER = oRow.lUpdateCounter;
	m_PERSON_ID = oRow.lPersonId;
	m_PHONE_TYPE_ID = oRow.lPhoneTypeId;
	_tcscpy_s(m_PHONE_NUMBER, sizeof(m_PHONE_NUMBER), oRow.szPhoneNumber);
}

void CPhoneNumbersTable::InitFieldsLengthAndStatus()
{
	m_dwIDLength = sizeof(long);
	m_dwUPDATE_COUNTERLength = sizeof(long);
	m_dwPERSON_IDLength = sizeof(long);
	m_dwPHONE_TYPE_IDLength = sizeof(long);
	m_dwPHONE_NUMBERLength = PHONE_NUMBER_LENGTH;

	m_dwIDStatus = DBSTATUS_S_OK;
	m_dwUPDATE_COUNTERStatus = DBSTATUS_S_OK;
	m_dwPERSON_IDStatus = DBSTATUS_S_OK;
	m_dwPHONE_TYPE_IDStatus = DBSTATUS_S_OK;
	m_dwPHONE_NUMBERStatus = DBSTATUS_S_OK;
}

long& CPhoneNumbersTable::GetUpdateCounterValue(const PHONE_NUMBERS& oRow)
{
	return (long&)*((char*)&oRow + offsetof(PHONE_NUMBERS, lUpdateCounter));
}