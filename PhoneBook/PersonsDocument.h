#pragma once

#include "Structures.h"
#include "Contact.h"
#include "TypedAutoPtrArray.h"
#include "ModifyRecordUtilites.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDocument


class CPersonsDocument : public CDocument
{
// Macros
// ----------------
	DECLARE_DYNCREATE(CPersonsDocument)
	DECLARE_MESSAGE_MAP()

// Constants
// ----------------
#define ERROR_LOADING_DATA "An error occurred while loading data!"

// Constructor / Destructor
// ----------------
public:
	CPersonsDocument();
	virtual ~CPersonsDocument();

// MFC Overrides
// ----------------
protected:
	virtual BOOL OnNewDocument();

#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);  
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

// Methods
// ----------------
public:
	///<summary> Взема референция към масива с всички налични записи </summary>
	const CPersonsArray& GetAllRecords() const;

	///<summary> Взема града за конкретен човек </summary>
	///<return> CITIES*, ако съществува град с такова ID или NULL при неуспех/несъществуващ град </return>
	const CITIES* GetPersonCity(const long& lCityId);

	///<summary> Попълва в подадения масив всички телефонни номера за даден човек </summary>
	///<return> TRUE - при успешно извлечени телефонни номера, FALSE - ако e възникнала грешка </return>
	BOOL GetAllPhoneNumbersOfPerson(const long& lPersonId, CPhoneNumbersArray& oPhoneNumbers);

	///<summary> Взема всички налични телефонни типове </summary>
	const CPhoneTypesArray& GetAllPhoneTypes() const;

	///<summary> Взема всички налични градове </summary>
	const CMap<long, long&, CITIES, CITIES&>& GetAllCities() const;

	///<summary> Променя запис в документа и в базата данни </summary>
	BOOL UpdateRecord(CContact& oContact);

	///<summary> Изтрива запис в документа и в базата данни </summary>
	BOOL DeleteRecord(CContact& oContact);

	///<summary> Добавя запис в документа и в базата данни </summary>
	BOOL InsertRecord(CContact& oContact);

private:
	///<summary> Зарежда CPersonsDcoument::m_oAllCities с всички градове </summary>
	BOOL InitializeAllCities();

	///<summary> Зарежда CPersonsDcoument::m_oAllPersonsInfoArray с всички хора </summary>
	BOOL InitializeAllPersons();

	///<summary> Зарежда CPersonsDocument::m_oAllPhoneTypesArray с всички типове телефони </summary>
	BOOL InitializeAllPhoneTypes();



// Members
// ----------------
private:
	CPersonsArray m_oAllPersonsArray;
	CPhoneTypesArray m_oAllPhoneTypesArray;
	CMap <long, long&, CITIES, CITIES&> m_oAllCities;

};
