#pragma once

#include "Structures.h"
#include "ModifyRecordUtilites.h"
/////////////////////////////////////////////////////////////////////////////
// CContact

///<summary> Клас с инфромация за конракт: инфорамция за човека и номерата му </summary>
class CContact : public CObject
{
// Constructor / Destructor
// ----------------
public:
	CContact();

	CContact(const PERSONS& pPersons, const CPhoneNumbersArray& m_oPhoneNumbersArray, const INT_PTR& nPersonArrayIndex);

	CContact(const PERSONS& pPersons, const CPhoneNumbersArray& m_oPhoneNumbersArray);

	virtual ~CContact();

// Methods
// ----------------
public:
	void Copy(const CContact& oContact);

// Methods
// ----------------
public:
	// Съдържа инофрмация за човека
	PERSONS oPersons;

	// Съдържа телефонните номера за човека
	CPhoneNumbersArray oPhoneNumbersArray;

	// Съхранява индекс на човека в CPersonsDocument::m_oPersonsArray
	INT_PTR nPersonsArrayIndex;
};

