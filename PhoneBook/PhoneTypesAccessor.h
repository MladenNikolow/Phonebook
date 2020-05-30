#pragma once
#include "stdafx.h"
#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesAccessor

///<summary> Клас свързващ таблица PHONE_TYPES с табличната структура </summary>
class CPhoneTypesAccessor
{
// Macros
// ----------------
BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, 2)
	BEGIN_ACCESSOR(0, true)
	COLUMN_ENTRY(1, m_ID)
	END_ACCESSOR()

	BEGIN_ACCESSOR(1, true)
	COLUMN_ENTRY(2, m_UPDATE_COUNTER)
	COLUMN_ENTRY(3, m_PHONE_TYPE)
	END_ACCESSOR()
END_ACCESSOR_MAP()

// Members
// ----------------
public:
	LONG m_ID;
	LONG m_UPDATE_COUNTER;
	TCHAR m_PHONE_TYPE[PHONE_TYPE_LENGTH];
	
	DBSTATUS m_dwIDStatus;
	DBSTATUS m_dwUPDATE_COUNTERStatus;
	DBSTATUS m_dwPHONE_TYPEStatus;

	DBLENGTH m_dwIDLength;
	DBLENGTH m_dwUPDATE_COUNTERLength;
	DBLENGTH m_dwPHONE_TYPELength;
};