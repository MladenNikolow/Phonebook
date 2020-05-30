#pragma once
#include <atlstr.h>
#include "TypedAutoPtrArray.h"

#define PERSON_NAME_LENGTH 256
#define UCN_LENGTH 16
#define STREET_ADDRESS_LENGTH 128

#define CITY_NAME_LENGTH 256
#define REGION_NAME_LENGTH 256

#define PHONE_TYPE_LENGTH 8

#define PHONE_NUMBER_LENGTH 16


//<summary> 
//Структура за таблица PERSONS от PHONEBOOK DB 
//</summary>
struct PERSONS
{
	//<summary> 
	//Дефолтен конструктор, зануляващ всички мембъри
	//</summary>
	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

	//<summary>Уникално ID</summary>
	long lId;

	//<summary>Брояч на промените за записа</summary>
	long lUpdateCounter;

	//<summary>Първо име на човека</summary>
	TCHAR szFirstName[PERSON_NAME_LENGTH];

	//<summary>Презиме на човека</summary>
	TCHAR szMiddleName[PERSON_NAME_LENGTH];

	//<summary>Фамилия на човека</summary>
	TCHAR szLastName[PERSON_NAME_LENGTH];

	//<summary>ЕГН</summary>
	TCHAR szUcn[UCN_LENGTH];

	//<summary>Уникален ключ за града</summary>
	long lCityId;

	//<summary>Уличен адрес</summary>
	TCHAR szStreetAddress[STREET_ADDRESS_LENGTH];

};

typedef CTypedAutoPtrArray<PERSONS> CPersonsArray;

//<summary> 
//Дискова структура за таблица CITIES от PHONEBOOK DB 
//</summary>
struct CITIES
{
	//<summary> 
	//Дефолтен конструктор, зануляващ всички мембъри
	//</summary>
	CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

	//<summary>Уникално ID</summary>
	long lId;

	//<summary>Брояч на промените на записа</summary>
	long lUpdateCounter;

	//<summary>Име на града</summary>
	TCHAR szName[CITY_NAME_LENGTH];

	//<summary>Име на региона</summary>
	TCHAR szRegion[REGION_NAME_LENGTH];


};

typedef CTypedAutoPtrArray<CITIES> CCitiesArray;

//<summary> 
//Дискова структура за таблица PHONE_TYPES от PHONEBOOK DB 
//</summary>
struct PHONE_TYPES
{
	//<summary> 
	//Дефолтен конструктор, зануляващ всички мембъри
	//</summary>
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

	//<summary>Уникално ID</summary>
	long lId;

	//<summary>Брояч на промените за записа</summary>
	long lUpdateCounter;

	//<summary>Тип на телефонния номер</summary>
	TCHAR szPhoneType[PHONE_TYPE_LENGTH];
};

typedef CTypedAutoPtrArray<PHONE_TYPES> CPhoneTypesArray;

//<summary> 
//Дискова структура за таблица PHONE_NUMBERS от PHONEBOOK DB 
//</summary>
struct PHONE_NUMBERS
{
	//<summary> 
	//Дефолтен конструктор, зануляващ всички мембъри
	//</summary>
	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

	//<summary>Уникалno ID</summary>
	long lId;

	//<summary>Брояч на промените за записа</summary>
	long lUpdateCounter;

	//<summary>Уникално ID на човека</summary>
	long lPersonId;

	//<summary>Уникално ID на типа на телефонния номер</summary>
	long lPhoneTypeId;

	//<summary>Телефонен номер</summary>
	TCHAR szPhoneNumber[PHONE_NUMBER_LENGTH];
};

typedef CTypedAutoPtrArray<PHONE_NUMBERS> CPhoneNumbersArray;