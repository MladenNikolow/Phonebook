#include "stdafx.h"
#include "PersonsTable.h"

// Constructor / Destructor
// ----------------
CPersonsTable::CPersonsTable() : CBaseTable(PersonsTableName)
{
	InitFieldsLengthAndStatus();
}

CPersonsTable::CPersonsTable(CSession& oSession) : CBaseTable(PersonsTableName, oSession)
{
}

CPersonsTable::~CPersonsTable()
{
}

// Overrides
// ----------------
void CPersonsTable::GetInfoFromRow(PERSONS& oRow) const
{
	oRow.lId = m_ID;
	oRow.lUpdateCounter = m_UPDATE_COUNTER;
	_tcscpy_s(oRow.szFirstName, m_FIRST_NAME);
	_tcscpy_s(oRow.szMiddleName, m_MIDDLE_NAME);
	_tcscpy_s(oRow.szLastName, m_LAST_NAME);
	_tcscpy_s(oRow.szUcn, m_UCN);
	oRow.lCityId = m_CITY_ID;
	_tcscpy_s(oRow.szStreetAddress, m_STREET_ADDRESS);
}

void CPersonsTable::SetInfoForRow(const PERSONS& oRow)
{
	m_ID = oRow.lId;
	m_UPDATE_COUNTER = oRow.lUpdateCounter;
	_tcscpy_s(m_FIRST_NAME, sizeof(m_FIRST_NAME), oRow.szFirstName);
	_tcscpy_s(m_MIDDLE_NAME, sizeof(m_MIDDLE_NAME), oRow.szMiddleName);
	_tcscpy_s(m_LAST_NAME, sizeof(m_LAST_NAME), oRow.szLastName);
	_tcscpy_s(m_UCN, sizeof(m_UCN), oRow.szUcn);
	m_CITY_ID = oRow.lCityId;
	_tcscpy_s(m_STREET_ADDRESS, sizeof(m_STREET_ADDRESS), oRow.szStreetAddress);
}

void CPersonsTable::InitFieldsLengthAndStatus()
{
	m_dwIDLength = sizeof(long);
	m_dwUPDATE_COUNTERLength = sizeof(long);
	m_dwFIRST_NAMELength = PERSON_NAME_LENGTH;
	m_dwMIDDLE_NAMELength = PERSON_NAME_LENGTH;
	m_dwLAST_NAMELength = PERSON_NAME_LENGTH;
	m_dwUCNLength = UCN_LENGTH;
	m_dwCITY_IDLength = sizeof(long);
	m_dwSTREET_ADDRESSLength = STREET_ADDRESS_LENGTH;

	m_dwIDStatus = DBSTATUS_S_OK;
	m_dwUPDATE_COUNTERStatus = DBSTATUS_S_OK;
	m_dwFIRST_NAMEStatus = DBSTATUS_S_OK;
	m_dwMIDDLE_NAMEStatus = DBSTATUS_S_OK;
	m_dwLAST_NAMEStatus = DBSTATUS_S_OK;
	m_dwUCNStatus = DBSTATUS_S_OK;
	m_dwCITY_IDStatus = DBSTATUS_S_OK;
	m_dwSTREET_ADDRESSStatus = DBSTATUS_S_OK;
}

long& CPersonsTable::GetUpdateCounterValue(const PERSONS& oRow)
{
	return (long&)*((char*)&oRow + offsetof(PERSONS, lUpdateCounter));
}