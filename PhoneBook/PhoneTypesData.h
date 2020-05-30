#pragma once
#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData

///<summary> Клас, съдържащ бизнес логиката за таблица PhoneTypes </summary>
class CPhoneTypesData
{
// Constructor / Destructor
// ----------------
public:
	CPhoneTypesData();
	virtual ~CPhoneTypesData();

// Methods
// ----------------
public:
	///<summary> Зарежда всички телефонни типове от базата данни </summary>
	///<return> TRUE - ако зареждането на записите е успешно, False - ако е неуспешно </return>
	BOOL LoadAllRecords(CPhoneTypesArray& oPhoneTypesArray);

	///<summary> Зарежда данните за телефонен тип с определено ID </summary>
	BOOL LoadRecordWithSpecificId(const long& lId, PHONE_TYPES& oPhoneTypes);

	///<summary> Добавя нов телефонен тип в базата данни </summary>
	///<return> TRUE - ако е добавен успешно, False - ако добавянето е неуспешно </return>
	BOOL AddRecord(const PHONE_TYPES& oPhoneTypes);

	///<summary> Променя информацията за даден телефонен тип в базата данни </summary>
	///<return> TRUE - ако е редактиран успешно, False - ако редактирането е неуспешно </return>
	BOOL UpdateRecord(PHONE_TYPES& oPhoneTypes);

	///<summary> Изтрива телефонен тип от базата данни </summary>
	///<return> TRUE - ако телефонният тип е изтрит успешно, False - ако изтриването е неуспешно </return>
	BOOL DeleteRecord(const PHONE_TYPES& oPhoneTypes);
};

