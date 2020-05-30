#pragma once
#include "PhonebookApp.h"
#include "ModifyRecordUtilites.h"
#include "TypedAutoPtrArray.h"

/////////////////////////////////////////////////////////////////////////////
// CBaseDocument

template <class Type, class CTypeData>
class CBaseDocument : public CDocument
{
// Constructor / Destructor
// ----------------
public:
	CBaseDocument() = default;
	virtual ~CBaseDocument() = default;

// MFC Overrides
// ----------------
public:
	virtual BOOL OnNewDocument()
	{
		if (!CDocument::OnNewDocument())
			return FALSE;

		CTypeData oTypeData;
		if (!oTypeData.LoadAllRecords(m_oTypeArray))
		{
			return FALSE;
			AfxMessageBox("An error occurred while loading data!");
		}

		return TRUE;
	}

	virtual void Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			// TODO: add storing code here
		}
		else
		{
			// TODO: add loading code here
		}
	}

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent()
	{
		CString strSearchContent;
		SetSearchContent(strSearchContent);
	}
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
	{
		// Modify this code to draw the document's data
		dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

		CString strText = _T("TODO: implement thumbnail drawing here");
		LOGFONT lf;

		CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
		pDefaultGUIFont->GetLogFont(&lf);
		lf.lfHeight = 36;

		CFont fontDraw;
		fontDraw.CreateFontIndirect(&lf);

		CFont* pOldFont = dc.SelectObject(&fontDraw);
		dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
		dc.SelectObject(pOldFont);
	}
#endif // SHARED_HANDLERS

	// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const
	{
		CDocument::AssertValid();
	}
	virtual void Dump(CDumpContext& dc) const
	{
		CDocument::Dump(dc);
	}
#endif

	// Methods
	// ----------------
public:
	///<summary> Променя запис в документа и в базата данни</summary>
	///<return> Връща TRUE при успех и FALSE при възникнала грешка </return>
	BOOL UpdateRecord(Type& oType, const INT_PTR& nArrayIndexOfModifiedRecord)
	{
		CTypeData oTypeData;
		if (!oTypeData.UpdateRecord(oType))
			return FALSE;

		Type* pType = m_oTypeArray.GetAt(nArrayIndexOfModifiedRecord);
		oTypeData.LoadRecordWithSpecificId(pType->lId, *pType);

		ModifiedRecordInfo oModifiedRecordInfo(nArrayIndexOfModifiedRecord, ModificationTypeEdit);

		SetModifiedFlag();
		UpdateAllViews(NULL, (LPARAM)&oModifiedRecordInfo);

		return TRUE;
	}

	///<summary> Добавя запис в документа и в базата данни</summary>
	///<return> Връща TRUE при успех и FALSE при възникнала грешка </return>
	BOOL AddRecord(const Type& oType)
	{
		CTypeData oTypeData;

		if (!oTypeData.AddRecord(oType))
			return FALSE;

		Type* pType = new Type();
		oTypeData.LoadRecordWithSpecificId(oType.lId, (*pType));

		INT_PTR nArrayIndexOfAddedRecord = m_oTypeArray.Add(pType);

		ModifiedRecordInfo oModifiedRecordInfo(nArrayIndexOfAddedRecord, ModificationTypeInsert);

		SetModifiedFlag();
		UpdateAllViews(NULL, (LPARAM)&oModifiedRecordInfo);

		return TRUE;
	}

	///<summary> Изтрива запис в документа и в базата данни</summary>
	///<return> Връща TRUE при успех и FALSE при възникнала грешка </return>
	BOOL DeleteRecord(const INT_PTR& nArrayIndexOfModifiedRecord)
	{
		Type* pType = m_oTypeArray.GetAt(nArrayIndexOfModifiedRecord);

		CTypeData oTypeData;
		if (!oTypeData.DeleteRecord(*pType))
			return FALSE;

		m_oTypeArray.RemoveAt(nArrayIndexOfModifiedRecord);

		ModifiedRecordInfo oModifiedRecordInfo(nArrayIndexOfModifiedRecord, ModificationTypeDelete);

		SetModifiedFlag();
		UpdateAllViews(NULL, (LPARAM)&oModifiedRecordInfo);

		return TRUE;
	}

	///<summary> Взема референция към масива с всички налични записи </summary>
	const CTypedAutoPtrArray<Type>& GetAllRecords() const
	{
		return m_oTypeArray;
	}

	///<summary> Зарежда запис от базата данни с актуалната информация </summary>
	BOOL GetRecord(const long& lId, Type& oType) const
	{
		CTypeData oTypeData;
		if (!oTypeData.LoadRecordWithSpecificId(lId, oType))
			return FALSE;

		return TRUE;
	}

	// Members
	// ----------------
private:
	CTypedAutoPtrArray<Type> m_oTypeArray;

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value)
	{
		if (value.IsEmpty())
		{
			RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
}
		else
		{
			CMFCFilterChunkValueImpl *pChunk = NULL;
			ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
			if (pChunk != NULL)
			{
				pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
				SetChunkValue(pChunk);
			}
		}
	}
#endif // SHARED_HANDLERS
};
