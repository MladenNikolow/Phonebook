#pragma once

///<summary> Типовете за обработка на данните </summary>
enum ModificationTypes
{
	ModificationTypeEdit = 0,
	ModificationTypeInsert = 1,
	ModificationTypeDelete = 2,
	ModificationTypeNone = 3
};

///<summary> Съдържа информация за изменения елемент в документа </summary>
struct ModifiedRecordInfo
{
	///<summary> Дефолтен конструктор, зануляващ всички мембъри </summary>
	ModifiedRecordInfo()
	{
		eModificationType = ModificationTypeNone;
		nArrayIndex = 0;
	}

	///<summary> Custom конструктор, който инициализира всички мембъри </summary>
	ModifiedRecordInfo(const INT_PTR& nIndex, const ModificationTypes& eModificationMode) : 
														nArrayIndex(nIndex),
														eModificationType(eModificationMode)
	{
	}

	// Индекс на модифицирания елемент в документа
	INT_PTR nArrayIndex;

	// Тип на модификацията
	ModificationTypes eModificationType;
};

