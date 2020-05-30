#pragma once
#include "BaseTable.h"
#include "PhoneNumbersAccessor.h"
#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable

class CPhoneNumbersTable : public CBaseTable<CPhoneNumbersAccessor, PHONE_NUMBERS>
{
// Constants
// ----------------
#define PERSON_ID "PERSON_ID"

// Constructor / Destructor
// ----------------
public:
	CPhoneNumbersTable(); 
	CPhoneNumbersTable(CSession& oSession);
	virtual ~CPhoneNumbersTable();

// Overrides
// ----------------
public:
	///<summary> Зарежда всички телефонни номера за определен PERSONS </summary>
	BOOL SelectAllPhoneNumbersOfPersons(const long& lId, CPhoneNumbersArray& oPhoneNumbersArray);

	///<summary> Изтрива всички телефонни номера за определен PERSONS </summary>
	BOOL DeleteAllPhoneNumbersOfPersons(const long& lId);

private:
	/// <summary> Присвоява на табличната структура стойностите от CPhoneNumbersAccessor </summary>
	virtual void GetInfoFromRow(PHONE_NUMBERS& oRow) const override;

	/// <summary> Присвоява на CPhoneNumbersAccessor стойностите от табличната структура </summary>
	virtual void SetInfoForRow(const PHONE_NUMBERS& oRow) override;

	/// <summary> Инициализира дължината и статуса на мембърите на CPhoneNumbersAccessor </summary>
	virtual void InitFieldsLengthAndStatus() override;

	/// <summary> Взема референция на update countera на CitiesTable </summary>
	virtual long& GetUpdateCounterValue(const PHONE_NUMBERS& oRow) override;
};

