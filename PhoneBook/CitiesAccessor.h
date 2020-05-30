#pragma once
#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesAccessor

///<summary> Клас свързващ таблица CITIES с табличната структура </summary>
class CCitiesAccessor
{
// Macros
// ----------------
BEGIN_ACCESSOR_MAP(CCitiesAccessor, 2)
	BEGIN_ACCESSOR(0, true)
	COLUMN_ENTRY(1, m_ID)
	END_ACCESSOR()

	BEGIN_ACCESSOR(1, true)
	COLUMN_ENTRY(2, m_UPDATE_COUNTER)
	COLUMN_ENTRY(3, m_NAME)
	COLUMN_ENTRY(4, m_REGION)
	END_ACCESSOR()
END_ACCESSOR_MAP()

// Members
// ----------------
public:
	LONG m_ID;
	LONG m_UPDATE_COUNTER;
	TCHAR m_NAME[256];
	TCHAR m_REGION[256];

	DBSTATUS m_dwIDStatus;
	DBSTATUS m_dwUPDATE_COUNTERStatus;
	DBSTATUS m_dwNAMEStatus;
	DBSTATUS m_dwREGIONStatus;

	DBLENGTH m_dwIDLength;
	DBLENGTH m_dwUPDATE_COUNTERLength;
	DBLENGTH m_dwNAMELength;
	DBLENGTH m_dwREGIONLength;
};


