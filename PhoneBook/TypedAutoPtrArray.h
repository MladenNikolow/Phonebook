#pragma once
#include "afxtempl.h"

template <class T>
class CTypedAutoPtrArray : public CTypedPtrArray<CPtrArray, T*>
{
// Constructor / Destructor
// ----------------
public:
	CTypedAutoPtrArray() = default;

	CTypedAutoPtrArray(const CTypedAutoPtrArray<T>& oTypedAutoPtrArray)
	{
		this->DeleteAll();

		for (INT_PTR i = 0; i < oTypedAutoPtrArray.GetCount(); ++i)
		{
			T* pData = new T();
			*pData = *oTypedAutoPtrArray.GetAt(i);
			CPtrArray::Add(pData);
		}

	}

	CTypedAutoPtrArray& operator=(const CTypedAutoPtrArray<T>& oTypedAutoPtrArray)
	{
		if (this != &oTypedAutoPtrArray)
		{
			DeleteAll();

			for (INT_PTR i = 0; i < oTypedAutoPtrArray.GetCount(); ++i)
			{
				T* pData = new T();
				*pData = *oTypedAutoPtrArray.GetAt(i);
				CPtrArray::Add(pData);
			}

		}

		return *this;
	}
			
	virtual ~CTypedAutoPtrArray()
	{
		DeleteAll();
	}

// Methods
// ----------------
public:
	//<summary>Освобождава паметта за всички елементи в контейнера</summary>
	void DeleteAll()
	{
		for (INT_PTR i = 0; i < this->m_nSize; ++i)
		{
			T* pData = this->GetAt(i);

			if (pData != NULL)
			{
				delete pData;
				pData = NULL;
			}
		}

		RemoveAll();
	}

};


