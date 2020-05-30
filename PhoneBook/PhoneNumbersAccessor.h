#pragma once
#include "stdafx.h"
#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersAccessor

///<summary> Клас свързващ таблица PHONE_NUMBERS с табличната структура </summary>
class CPhoneNumbersAccessor
{
// Macros
// ----------------
BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, 2)
	BEGIN_ACCESSOR(0, true)
	COLUMN_ENTRY(1, m_ID)
	END_ACCESSOR()

	BEGIN_ACCESSOR(1, true)
	COLUMN_ENTRY(2, m_UPDATE_COUNTER)
	COLUMN_ENTRY(3, m_PERSON_ID)
	COLUMN_ENTRY(4, m_PHONE_TYPE_ID)
	COLUMN_ENTRY(5, m_PHONE_NUMBER)
	END_ACCESSOR()
END_ACCESSOR_MAP()
// Members
// ----------------
public:
	LONG m_ID;
	LONG m_UPDATE_COUNTER;
	LONG m_PERSON_ID;
	LONG m_PHONE_TYPE_ID;
	TCHAR m_PHONE_NUMBER[PHONE_NUMBER_LENGTH];

	DBSTATUS m_dwIDStatus;
	DBSTATUS m_dwUPDATE_COUNTERStatus;
	DBSTATUS m_dwPERSON_IDStatus;
	DBSTATUS m_dwPHONE_TYPE_IDStatus;
	DBSTATUS m_dwPHONE_NUMBERStatus;

	DBLENGTH m_dwIDLength;
	DBLENGTH m_dwUPDATE_COUNTERLength;
	DBLENGTH m_dwPERSON_IDLength;
	DBLENGTH m_dwPHONE_TYPE_IDLength;
	DBLENGTH m_dwPHONE_NUMBERLength;
};