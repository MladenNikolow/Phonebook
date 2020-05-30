#include "stdafx.h"
#include "PhoneBookApp.h"
#include "PersonsDocument.h"

#include "PersonsData.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDocument

IMPLEMENT_DYNCREATE(CPersonsDocument, CDocument)

BEGIN_MESSAGE_MAP(CPersonsDocument, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPersonsDocument::CPersonsDocument()
{
}

CPersonsDocument::~CPersonsDocument()
{
}

// MFC Overrides
// ----------------
BOOL CPersonsDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if (!InitializeAllPersons())
	{
		AfxMessageBox(ERROR_LOADING_DATA);
		return FALSE;
	}

	if (!InitializeAllCities())
	{
		AfxMessageBox(ERROR_LOADING_DATA);
		return FALSE;
	}

	if (!InitializeAllPhoneTypes())
	{
		AfxMessageBox(ERROR_LOADING_DATA);
		return FALSE;
	}

	return TRUE;
}

#ifdef _DEBUG
void CPersonsDocument::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonsDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
void CPersonsDocument::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
#endif

// Methods
// ----------------
const CPersonsArray& CPersonsDocument::GetAllRecords() const
{
	return (const CPersonsArray&)m_oAllPersonsArray;
}

const CITIES* CPersonsDocument::GetPersonCity(const long& lCityId)
{
	CMap<long, long&, CITIES, CITIES&>::CPair* pCityInfo;

	pCityInfo = m_oAllCities.PLookup((long&)lCityId);
	if (!pCityInfo)
	{
		return NULL;
	}

	return &pCityInfo->value;
}

BOOL CPersonsDocument::InitializeAllCities()
{
	CPersonsData oPersonsData;
	CCitiesArray oCitiesArray;
	if (!oPersonsData.GetAllCities(oCitiesArray))
		return FALSE;

	for (INT_PTR i = 0; i < oCitiesArray.GetCount(); ++i)
	{
		CITIES* pCity = oCitiesArray.GetAt(i);
		m_oAllCities.SetAt(pCity->lId, *pCity);
	}

	return TRUE;
}

BOOL CPersonsDocument::GetAllPhoneNumbersOfPerson(const long& lPersonId, CPhoneNumbersArray& oPhoneNumbers)
{
	CPersonsData oPersonsData;
	return oPersonsData.GetAllPhoneNumbersOfPerson(lPersonId, oPhoneNumbers);
}

const CMap<long, long&, CITIES, CITIES&>& CPersonsDocument::GetAllCities() const
{
	return m_oAllCities;
}

const CPhoneTypesArray& CPersonsDocument::GetAllPhoneTypes() const
{
	return m_oAllPhoneTypesArray;
}

BOOL CPersonsDocument::InitializeAllPersons()
{
	CPersonsData oPersonsData;
	if (!oPersonsData.LoadAllRecords(m_oAllPersonsArray))
		return FALSE;

	return TRUE;
}

BOOL CPersonsDocument::InitializeAllPhoneTypes()
{
	CPersonsData oPersonsData;
	if (!oPersonsData.GetAllPhoneTypes(m_oAllPhoneTypesArray))
		return FALSE;

	return TRUE;
}

BOOL CPersonsDocument::UpdateRecord(CContact& oContact)
{
	CPersonsData oPersonsData;
	if (!oPersonsData.UpdateRecord(oContact))
		return FALSE;

	//Заеждам на ново данните за човека и номерата му
	PERSONS* pPersons = m_oAllPersonsArray.GetAt(oContact.nPersonsArrayIndex);
	oPersonsData.LoadRecordWithSpecificId(pPersons->lId, *pPersons);

	oContact.oPersons = *pPersons;

	SetModifiedFlag();
	UpdateAllViews(NULL, ModificationTypeEdit, &oContact);

	return TRUE;
}

BOOL CPersonsDocument::DeleteRecord(CContact& oContact)
{
	CPersonsData oPersonsData;
	if (!oPersonsData.DeleteRecord(oContact))
	{
		return FALSE;
	}

	m_oAllPersonsArray.RemoveAt(oContact.nPersonsArrayIndex);

	SetModifiedFlag();
	UpdateAllViews(NULL, ModificationTypeDelete, &oContact);

	return TRUE;
}

BOOL CPersonsDocument::InsertRecord(CContact& oContact)
{
	CPersonsData oPersonsData;
	if (!oPersonsData.AddRecord(oContact))
	{
		return FALSE;
	}

	PERSONS* pPersons = new PERSONS();
	*pPersons = oContact.oPersons;

	INT_PTR nPersonsArrayIndex = m_oAllPersonsArray.Add(pPersons);
	oContact.nPersonsArrayIndex = nPersonsArrayIndex;

	SetModifiedFlag();
	UpdateAllViews(NULL, ModificationTypeInsert, &oContact);

	return TRUE;
}