#include "stdafx.h"

#include "PersonsData.h"
#include "PersonsTable.h"
#include "PhoneNumbersTable.h"
#include "PhoneTypesTable.h"

#include "CitiesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

// Constructor / Destructor
// ----------------
CPersonsData::CPersonsData()
{
}

CPersonsData::~CPersonsData()
{
}

// Methods
// ----------------
BOOL CPersonsData::LoadAllRecords(CPersonsArray& oAllPersons)
{
	CPersonsTable oPersonsTable;

	if (!oPersonsTable.SelectAll(oAllPersons))
		return FALSE;

	return TRUE;
}

BOOL CPersonsData::LoadRecordWithSpecificId(const long& lId, PERSONS& oPersons)
{
	CPersonsTable oPersonsTable;
	return oPersonsTable.SelectWhereId(lId, oPersons);
}

BOOL CPersonsData::AddRecord(CContact& oContact)
{
	CSession oSession;

	if (FAILED(oSession.Open(CDataBase::GetDataBase().GetDataSource())))
		return FALSE;

	if (FAILED(oSession.StartTransaction()))
		return FALSE;

	if (!AddPerson(oSession, oContact))
		return FALSE;

	if (!AddOrUpdatePhoneNumbers(oSession, oContact))
		return FALSE;

	oSession.Commit();

	return TRUE;
}

BOOL CPersonsData::UpdateRecord(CContact& oContact)
{
	CSession oSession;

	if (FAILED(oSession.Open(CDataBase::GetDataBase().GetDataSource())))
		return FALSE;

	if (FAILED(oSession.StartTransaction()))
		return FALSE;

	if (!UpdatePerson(oSession, oContact))
		return FALSE;

	if (!ModifyPhoneNumbers(oSession, oContact))
		return FALSE;

	oSession.Commit();

	return TRUE;
}


BOOL CPersonsData::DeleteRecord(const CContact& oContact)
{
	CSession oSession;

	if (FAILED(oSession.Open(CDataBase::GetDataBase().GetDataSource())))
		return FALSE;

	if (FAILED(oSession.StartTransaction()))
		return FALSE;
	
	CPhoneNumbersTable oPhoneNumbersTable(oSession);
	if (!oPhoneNumbersTable.DeleteAllPhoneNumbersOfPersons(oContact.oPersons.lId))
	{
		oSession.Abort();
		return FALSE;
	}

	if (!DeletePerson(oSession, oContact))
		return FALSE;
	

	oSession.Commit();
	return TRUE;
}

BOOL CPersonsData::GetAllPhoneNumbersOfPerson(const long& lPersonId, CPhoneNumbersArray& oPhoneNumbersArray)
{
	CPhoneNumbersTable oPhoneNumbersTable;
	return oPhoneNumbersTable.SelectAllPhoneNumbersOfPersons(lPersonId, oPhoneNumbersArray);
}

BOOL CPersonsData::GetAllCities(CCitiesArray& oAllCities)
{
	CCitiesTable oCitiesTable;
	return oCitiesTable.SelectAll(oAllCities);
}

BOOL CPersonsData::GetAllPhoneTypes(CPhoneTypesArray& oAllPhoneTypes)
{
	CPhoneTypesTable oPhoneTypesTable;
	return oPhoneTypesTable.SelectAll(oAllPhoneTypes);
}

BOOL CPersonsData::DeletePhoneNumbers(CSession& oSession,
								const CPhoneNumbersArray& oNewPhoneNumbersArray, 
								const CPhoneNumbersArray& oOldPhoneNumbersArray)
{
	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	for (INT_PTR i = 0; i < oOldPhoneNumbersArray.GetCount(); ++i)
	{
		PHONE_NUMBERS* pPhoneNumbersFromDatabase = oOldPhoneNumbersArray.GetAt(i);
		
		if (FindPhoneNumber(oNewPhoneNumbersArray, pPhoneNumbersFromDatabase->lId))
			continue;

		if (!DeletePhoneNumber(oSession, *pPhoneNumbersFromDatabase))
				return FALSE;

	}

	return TRUE;
}

BOOL CPersonsData::AddOrUpdatePhoneNumbers(CSession& oSession,
										   const CContact& oContact)
{
	const CPhoneNumbersArray& oPhoneNumbersArray = oContact.oPhoneNumbersArray;

	for (INT_PTR i = 0; i < oPhoneNumbersArray.GetCount(); ++i)
	{
		PHONE_NUMBERS* pPhoneNumbers = oPhoneNumbersArray.GetAt(i);

		if (pPhoneNumbers->lId == 0)
		{
			pPhoneNumbers->lPersonId = oContact.oPersons.lId;
			if (!InsertPhoneNumber(oSession, *pPhoneNumbers))
				return FALSE;
		}
		else
		{
			if (!UpdatePhoneNumber(oSession, *pPhoneNumbers))
				return FALSE;
		}

	}

	return TRUE;
}

BOOL CPersonsData::ModifyPhoneNumbers(CSession& oSession, CContact& oContact)
{
	CPhoneNumbersArray& oNewPhoneNumbersArray = oContact.oPhoneNumbersArray;

	CPhoneNumbersArray oOldPhoneNumbersArray;
	GetAllPhoneNumbersOfPerson(oContact.oPersons.lId, oOldPhoneNumbersArray);

	if (!DeletePhoneNumbers(oSession, oNewPhoneNumbersArray, oOldPhoneNumbersArray))
	{
		oSession.Abort();
		return FALSE;
	}

	if (!AddOrUpdatePhoneNumbers(oSession, oContact))
	{
		oSession.Abort();
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::UpdatePerson(CSession& oSession, CContact& oContact)
{
	PERSONS& oPersons = oContact.oPersons;
	CPersonsTable oPersonsTable(oSession);

	if (!oPersonsTable.UpdateWhereId(oPersons.lId, oPersons))
	{
		oSession.Abort();
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::UpdatePhoneNumber(CSession& oSession, PHONE_NUMBERS& oPhoneNumbers)
{
	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	if (!oPhoneNumbersTable.UpdateWhereId(oPhoneNumbers.lId, oPhoneNumbers))
	{
		oSession.Abort();
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::DeletePhoneNumber(CSession& oSession, const PHONE_NUMBERS& oPhoneNumbers)
{
	CPhoneNumbersTable oPhoneNumbersTable(oSession);
	if (!oPhoneNumbersTable.DeleteWhereId(oPhoneNumbers.lId))
	{
		oSession.Abort();
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::InsertPhoneNumber(CSession& oSession, PHONE_NUMBERS& oPhoneNumbers)
{
	CPhoneNumbersTable oPhoneNumbersTable(oSession);
	if (!oPhoneNumbersTable.Insert(oPhoneNumbers))
	{
		oSession.Abort();
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::FindPhoneNumber(const CPhoneNumbersArray& oPhoneNumbersArray, const INT_PTR& nSearchedId)
{
	BOOL bResult = FALSE;
	for (INT_PTR i = 0; i < oPhoneNumbersArray.GetCount(); ++i)
	{
		PHONE_NUMBERS* pPhoneNumbers = oPhoneNumbersArray.GetAt(i);

		if (pPhoneNumbers->lId == nSearchedId)
		{
			bResult = TRUE;
			break;
		}

	}

	return bResult;
}

BOOL CPersonsData::AddPerson(CSession& oSession, CContact& oContact)
{
	CPersonsTable oPersonsTable(oSession);

	if (!oPersonsTable.Insert(oContact.oPersons))
	{
		oSession.Abort();
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::DeletePerson(CSession& oSession, const CContact& oContact)
{
	CPersonsTable oPersonsTable(oSession);
	if (!oPersonsTable.DeleteWhereId(oContact.oPersons.lId))
	{
		oSession.Abort();
		return FALSE;
	}
}