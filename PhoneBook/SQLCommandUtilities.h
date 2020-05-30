#pragma once

//Аксесори
#define FirstAccessor 0
#define SecondAccessor 1

//SQL заявки
#define SELECT_ALL_FROM_TABLE_COMMAND "SELECT * FROM [{TABLE_NAME}]"

//Имента на таблици
#define CitiesTableName "CITIES"
#define PersonsTableName "PERSONS"
#define PhoneNumbersTableName "PHONE_NUMBERS"
#define PhoneTypesTableName "PHONE_TYPES"

//Заключвания
#define UPDLOCK " WITH (UPDLOCK)"
#define NOLOCK " WITH (NOLOCK)"

//Имена на таблични полета
#define ID_FIELD "ID"

enum LockModes
{
	LockModeNoLock = 0,
	LockModeUpdateLock = 1,
	LockModeRowLock = 2
};

enum WhereConditions
{
	WhereConditionNoCondition = 0,
	WhereConditionSingleCondition = 1
};