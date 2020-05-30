#pragma once
#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsAccessor

///<summary> Клас свързващ таблица PERSONS с табличната структура </summary>
class CPersonsAccessor
{
// Macros
// ----------------
	BEGIN_ACCESSOR_MAP(CPersonsAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(1, m_ID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(2, m_UPDATE_COUNTER)
		COLUMN_ENTRY(3, m_FIRST_NAME)
		COLUMN_ENTRY(4, m_MIDDLE_NAME)
		COLUMN_ENTRY(5, m_LAST_NAME)
		COLUMN_ENTRY(6, m_UCN)
		COLUMN_ENTRY(7, m_CITY_ID)
		COLUMN_ENTRY(8, m_STREET_ADDRESS)
		END_ACCESSOR()
	END_ACCESSOR_MAP()

// Members
// ----------------
public:
	LONG m_ID;
	LONG m_UPDATE_COUNTER;
	TCHAR m_FIRST_NAME[256];
	TCHAR m_MIDDLE_NAME[256];
	TCHAR m_LAST_NAME[256];
	TCHAR m_UCN[32];
	LONG m_CITY_ID;
	TCHAR m_STREET_ADDRESS[128];

	DBSTATUS m_dwIDStatus;
	DBSTATUS m_dwUPDATE_COUNTERStatus;
	DBSTATUS m_dwFIRST_NAMEStatus;
	DBSTATUS m_dwMIDDLE_NAMEStatus;
	DBSTATUS m_dwLAST_NAMEStatus;
	DBSTATUS m_dwUCNStatus;
	DBSTATUS m_dwCITY_IDStatus;
	DBSTATUS m_dwSTREET_ADDRESSStatus;

	DBLENGTH m_dwIDLength;
	DBLENGTH m_dwUPDATE_COUNTERLength;
	DBLENGTH m_dwFIRST_NAMELength;
	DBLENGTH m_dwMIDDLE_NAMELength;
	DBLENGTH m_dwLAST_NAMELength;
	DBLENGTH m_dwUCNLength;
	DBLENGTH m_dwCITY_IDLength;
	DBLENGTH m_dwSTREET_ADDRESSLength;
};
