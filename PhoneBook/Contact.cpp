#include "stdafx.h"
#include "Contact.h"

/////////////////////////////////////////////////////////////////////////////
// CContact

// Constructor / Destructor
// ----------------
CContact::CContact() :
					oPersons(), 
					oPhoneNumbersArray(),
					nPersonsArrayIndex{}
{
}

CContact::CContact(const PERSONS& oPersons, const CPhoneNumbersArray& oPhoneNumbersArray, const INT_PTR& nPersonArrayIndex):
				   oPersons(oPersons),
				   oPhoneNumbersArray(oPhoneNumbersArray),
				   nPersonsArrayIndex(nPersonArrayIndex)
{
}

CContact::CContact(const PERSONS& oPersons, const CPhoneNumbersArray& oPhoneNumbersArray) :
				   oPersons(oPersons),
				   oPhoneNumbersArray(oPhoneNumbersArray),
				   nPersonsArrayIndex{}
{
}

CContact::~CContact()
{
}

// Methods
// ----------------
void CContact::Copy(const CContact& oContact)
{
	this->oPersons = oContact.oPersons;
	this->oPhoneNumbersArray = oContact.oPhoneNumbersArray;
	this->nPersonsArrayIndex = oContact.nPersonsArrayIndex;
}