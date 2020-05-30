#pragma once
#include "atldbcli.h"
#include "CitiesAccessor.h"
#include "Structures.h"
#include "SQLCommandUtilities.h"
#include "BaseTable.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary>Клас за работа с таблица CITIES</summary>
class CCitiesTable : public CBaseTable<CCitiesAccessor, CITIES>
{

// Constructor / Destructor
// ----------------
public:
	CCitiesTable();
	CCitiesTable(CSession& oSession);
	virtual ~CCitiesTable();

// Overrides
// ----------------
private:

	/// <summary> Присвоява на табличната структура стойностите от CCitiesAccessor </summary>
	virtual void GetInfoFromRow(CITIES& oCities) const override;

	/// <summary> Присвоява на CCitiesAccessor стойностите от табличната структура </summary>
	virtual void SetInfoForRow(const CITIES& oCities) override;

	/// <summary> Инициализира дължината и статуса на мембърите на CitiesAccessor </summary>
	virtual void InitFieldsLengthAndStatus() override;

	/// <summary> Взема референция на update countera на CitiesTable </summary>
	virtual long& GetUpdateCounterValue(const CITIES& oRow) override;
};

