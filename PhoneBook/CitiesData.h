#pragma once
#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData

///<summary> Клас, съдържащ бизнес логиката за таблица CITIES </summary>
class CCitiesData
{
// Constructor / Destructor
// ----------------
public:
	CCitiesData();
	virtual ~CCitiesData();

// Methods
// ----------------
public:
	///<summary> Зарежда всички градове от базата данни </summary>
	///<return> TRUE - ако зареждането на записите е успешно, False - ако е неуспешно </return>
	BOOL LoadAllRecords(CCitiesArray& oAllCities);

	///<summary> Зарежда данните за град </summary>
	BOOL LoadRecordWithSpecificId(const long& lId, CITIES& oCities);

	///<summary> Добавя град в базата данни </summary>
	///<return> TRUE - ако градът е добавен успешно, False - ако добавянето е неуспешно </return>
	BOOL AddRecord(const CITIES& oCities);

	///<summary> Променя информацията за град в базата данни </summary>
	///<return> TRUE - ако градът е редактиран успешно, False - ако редактирането е неуспешно </return>
	BOOL UpdateRecord(CITIES& oCities);

	///<summary> Изтрива град от базата данни </summary>
	///<return> TRUE - ако градът е изтрит успешно, False - ако изтриването е неуспешно </return>
	BOOL DeleteRecord(const CITIES& oCities);

};

