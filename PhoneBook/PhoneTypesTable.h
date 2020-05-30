#pragma once
#include "BaseTable.h"
#include "PhoneTypesAccessor.h"
#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable

class CPhoneTypesTable : 
	public CBaseTable<CPhoneTypesAccessor, PHONE_TYPES>
{
// Constructor / Destructor
// ----------------
public:
	CPhoneTypesTable();
	CPhoneTypesTable(CSession& oSession);
	virtual ~CPhoneTypesTable();

// Overrides
// ----------------
private:
	/// <summary> Присвоява на табличната структура стойностите от CPhoneTypesAccessor </summary>
	virtual void GetInfoFromRow(PHONE_TYPES& oRow) const override;

	/// <summary> Присвоява на CPhoneTypesAccessor стойностите от табличната структура </summary>
	virtual void SetInfoForRow(const PHONE_TYPES& oRow) override;

	/// <summary> Инициализира дължината и статуса на мембърите на CPhoneNumbersAccessor </summary>
	virtual void InitFieldsLengthAndStatus() override;

	/// <summary> Взема референция на update countera на CitiesTable </summary>
	virtual long& GetUpdateCounterValue(const PHONE_TYPES& oRow) override;
};

