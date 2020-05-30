#pragma once

#include "Structures.h"
#include "Contact.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

///<summary> Клас, съдържащ бизнес логиката за таблица PERSONS </summary>
class CPersonsData
{
// Constants
// ----------------
#define PERSON_ID "PERSON_ID"

#define MODIFY_PHONE_NUMBERS_ERROR -1

// Constructor / Destructor
// ----------------
public:
	CPersonsData();
	virtual ~CPersonsData();

// Methods
// ----------------
public:
	///<summary> Зарежда всички хора от базата данни </summary>
	///<return> TRUE - ако зареждането на записите е успешно, False - ако е неуспешно </return>
	BOOL LoadAllRecords(CPersonsArray& oAllPersons);

	///<summary> Зарежда данните за човек с определено ID </summary>
	///<return> TRUE - ако зареждането на записа е успешно, False - ако е неуспешно </return>
	BOOL LoadRecordWithSpecificId(const long& lId, PERSONS& oPersons);

	///<summary> Добавя данните за човек и номерата му в базата данни </summary>
	///<return> TRUE - ако данните са добавени успешно, False - ако е неуспешно </return>
	BOOL AddRecord(CContact& oContact);

	///<summary> Променя информацията за даден човек и/или номерата му в базата данни </summary>
	///<return> TRUE - ако информацията е редактирана успешно, False - ако е неуспешно </return>
	BOOL UpdateRecord(CContact& oContact);

	///<summary> Изтрива инфомрацията за човек и/или номерата му от базата данни </summary>
	///<return> TRUE - ако записът е изтрит успешно, False - ако изтриването е неуспешно </return>
	BOOL DeleteRecord(const CContact& oContact);

	///<summary> Взема всички телефонни номера за човек </summary>
	///<return> TRUE - ако информацията е извлчена успешно, False - при възникнала грешка </return>
	BOOL GetAllPhoneNumbersOfPerson(const long& lPersonId, CPhoneNumbersArray& oPhoneNumbersArray);

	///<summary> Вземи всички градове от базата данни </summary>
	///<return> TRUE - ако информацията е извлчена успешно, False - при възникнала грешка </return>
	BOOL GetAllCities(CCitiesArray& oAllCities);

	///<summary> Вземи всички телефонни типове от базата данни </summary>
	///<return> TRUE - ако информацията е извлчена успешно, False - при възникнала грешка </return>
	BOOL GetAllPhoneTypes(CPhoneTypesArray& oAllPhoneTypes);

private:
	///<summary> Добавя данните за човек в базата данни </summary>
	///<return> TRUE - при успешно добавяне и FALSE при възникнала грешка </return>
	BOOL AddPerson(CSession& oSession, CContact& oContact);

	///<summary> Променя данните за човек в базата данни </summary>
	///<return> TRUE - при успешна редакция и FALSE при възникнала грешка </return>
	BOOL UpdatePerson(CSession& oSession, CContact& oContact);

	///<summary> Изтрива данните за човек в базата данни </summary>
	///<return> TRUE - при успешно изтриване и FALSE при възникнала грешка </return>
	BOOL DeletePerson(CSession& oSession, const CContact& oContact);

	///<summary> Променя, добавя и изтрива телефонните номера за даден контакт </summary>
	///<return> TRUE - при успешно направени модификации и FALSE при възникнала грешка </return>
	BOOL ModifyPhoneNumbers(CSession& oSession, CContact& oContact);

	///<summary> Променя или изтрива телефонните номера за даден човек </summary>
	///<return> Връща MODIFY_PHONE_NUMBERS_ERROR (-1) при грешка или индекс,
	///от който да започне добавянето на номера </return>
	BOOL DeletePhoneNumbers(CSession& oSession,		
							   const CPhoneNumbersArray& oNewPhoneNumbersArray, 
							   const CPhoneNumbersArray& oOldPhoneNumbersArray);
	
	///<summary> Добавя новите телефонни номера за даден човек </summary>
	///<return> TRUE - при успешно добавени номра и FALSE при възникнала грешка </return>
	BOOL AddOrUpdatePhoneNumbers(CSession& oSession,
								 const CContact& oContact);

	///<summary> Променя данните за телефонен номер в базата данни </summary>
	///<return> TRUE - при успешна редакция и FALSE при възникнала грешка </return>
	BOOL UpdatePhoneNumber(CSession& oSession, PHONE_NUMBERS& oPhoneNumbers);

	///<summary> Изтрива телефонен номер от базата данни </summary>
	///<return> TRUE - при успешно изтриване и FALSE при възникнала грешка </return>
	BOOL DeletePhoneNumber(CSession& oSession, const PHONE_NUMBERS& oPhoneNumbers);

	///<summary> Добавя нов телефонен номер в базата данни </summary>
	///<return> TRUE - при успешно добавяне и FALSE при възникнала грешка </return>
	BOOL InsertPhoneNumber(CSession& oSession, PHONE_NUMBERS& oPhoneNumbers);

	///<summary> Търси номер в даден масив от номера по ID </summary>
	///<return> TRUE - ако открие номера и FALSE ако номерът не е част от масива </return>
	BOOL FindPhoneNumber(const CPhoneNumbersArray& oPhoneNumbersArray, const INT_PTR& nSearchedId);
};

