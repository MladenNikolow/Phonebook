#pragma once
#include "BaseTable.h"
#include "PersonsAccessor.h"
#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

class CPersonsTable
	: public CBaseTable<CPersonsAccessor, PERSONS>
{

// Constructor / Destructor
// ----------------
public:
	CPersonsTable();
	CPersonsTable(CSession& oSession);
	virtual ~CPersonsTable();

// Overrides
// ----------------
private:
	/// <summary> Присвоява на табличната структура стойностите от CPersonsAccessor </summary>
	virtual void GetInfoFromRow(PERSONS& oRow) const override;

	/// <summary> Присвоява на CPersonsAccessor стойностите от табличната структура </summary>
	virtual void SetInfoForRow(const PERSONS& oRow) override;

	/// <summary> Инициализира дължината и статуса на мембърите на CPersonsAccessor </summary>
	virtual void InitFieldsLengthAndStatus() override;

	/// <summary> Взема референция на update countera на PersonsTable </summary>
	virtual long& GetUpdateCounterValue(const PERSONS& oRow) override;

};