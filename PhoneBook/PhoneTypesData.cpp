#include "stdafx.h"
#include "PhoneTypesData.h"
#include "PhoneTypesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData

// Constructor / Destructor
// ----------------
CPhoneTypesData::CPhoneTypesData()
{
}

CPhoneTypesData::~CPhoneTypesData()
{
}

// Methods
// ----------------
BOOL CPhoneTypesData::LoadAllRecords(CPhoneTypesArray& oPhoneTypesArray)
{
	CPhoneTypesTable oPhoneTypesTable;
	return oPhoneTypesTable.SelectAll(oPhoneTypesArray);
}

BOOL CPhoneTypesData::LoadRecordWithSpecificId(const long& lId, PHONE_TYPES& oPhoneTypes)
{
	CPhoneTypesTable oPhoneTypesTable;
	return oPhoneTypesTable.SelectWhereId(lId, oPhoneTypes);
}

BOOL CPhoneTypesData::AddRecord(const PHONE_TYPES& oPhoneTypes)
{
	CPhoneTypesTable oPhoneTypesTable;
	return oPhoneTypesTable.Insert(const_cast<PHONE_TYPES&>(oPhoneTypes));
}

BOOL CPhoneTypesData::UpdateRecord(PHONE_TYPES& oPhoneTypes)
{
	CPhoneTypesTable oPhoneTypesTable;
	return oPhoneTypesTable.UpdateWhereId(oPhoneTypes.lId, oPhoneTypes);
}

BOOL CPhoneTypesData::DeleteRecord(const PHONE_TYPES& oPhoneTypes)
{
	CPhoneTypesTable oPhoneTypesTable;
	return oPhoneTypesTable.DeleteWhereId(oPhoneTypes.lId);
}
