#pragma once
#include "DataBase.h"
#include "TypedAutoPtrArray.h"
#include "Structures.h"
#include "SQLCommandUtilities.h"

/////////////////////////////////////////////////////////////////////////////
// CBaseTable

template <class AccessorType, class TableStructure>
class CBaseTable : public CCommand<CAccessor<AccessorType>>
{

// Constructor / Destructor
// ----------------
public:

CBaseTable(const CString& strNameOfTable, CSession& oSession) : strTableName(strNameOfTable),
																m_pSession(&oSession),
																m_bIsSessionInternal(FALSE)
{
}

CBaseTable(const CString& strNameOfTable) : strTableName(strNameOfTable),
											m_pSession(new CSession()),
											m_bIsSessionInternal(TRUE)
{
}

virtual ~CBaseTable()
{
	if (m_pSession && m_bIsSessionInternal)
		delete m_pSession;
}

// Virtual Methods
// ----------------
private:

	virtual void InitFieldsLengthAndStatus() = 0;
	virtual void GetInfoFromRow(TableStructure& oRow) const = 0;
	virtual void SetInfoForRow(const TableStructure& oRow) = 0;
	virtual long& GetUpdateCounterValue(const TableStructure& oRow) = 0;

// Methods
// ----------------
public:

BOOL SelectAll(CTypedAutoPtrArray<TableStructure>& oTableStructureArray)
{
	CString strQuery = CreateSelectAllCommand(LockModeNoLock);

	if (!OpenSession())
		return FALSE;
	
	if (!ExecuteQuery(strQuery))
		return FALSE;

	if (!LoadData(oTableStructureArray))
		return FALSE;

	CloseSession();

	return TRUE;
}

template <class T = long>
BOOL SelectWhereId(const T& lId, TableStructure& oRow)
{
	if (!OpenSession())
		return FALSE;

	if (!SelectWhereIdWithLockMode(lId, oRow, *m_pSession, LockModeNoLock))
		return FALSE;

	CloseSession();

	return TRUE;
}

template <class T = long>
BOOL UpdateWhereId(const T& lId, TableStructure& oRow)
{
	if (!OpenSession())
		return FALSE;

	if (!StartTransaction())
		return FALSE;

	TableStructure oTableStructure;
	if (!SelectWhereIdWithLockMode(lId, oTableStructure, *m_pSession, LockModeUpdateLock))
	{
		AbortAndCloseSession();
		return FALSE;
	}

	if (GetUpdateCounterValue(oRow) != GetUpdateCounterValue(oTableStructure))
	{
		TRACE("Update failed because of different versions!");
		AbortAndCloseSession();
		return FALSE;
	}

	if (!UpdateRecord(oRow))
		return FALSE;

	if (!CommitTransaction())
		return FALSE;

	CloseSession();

	return TRUE;
}

BOOL Insert(TableStructure& oRow)
{
	if (!OpenSession())
		return FALSE;

	CDBPropSet oDBPropSet(DBPROPSET_ROWSET);
	InitDBPropSet(oDBPropSet);

	CString strQuery = CreateSelectAllCommand(LockModeNoLock);
	
	if(!ExecuteQuery(strQuery, &oDBPropSet))
		return FALSE;
	
	if (!InsertRecord(oRow))
		return FALSE;

	if (!GetInsertedData(oRow))
		return FALSE;

	CloseSession();

	return TRUE;
}

template <class T = long>
BOOL DeleteWhereId(const T& lId)
{
	if (!OpenSession())
		return FALSE;

	TableStructure oTableStructure;
	if (!SelectWhereIdWithLockMode(lId, oTableStructure, *m_pSession, LockModeNoLock))
		return FALSE;

	HRESULT oResult = Delete();
	if (oResult != S_OK)
	{
		CloseSession();
		return FALSE;
	}

	CloseSession();

	return TRUE;

}

// PROTECTED METHODS
protected:
///<summary> Изтрива всички записи по даден Foreign Key </summary>
BOOL DeleteAllWhereForeignKey(const CString& strField, const long& lForeignKey)
{
	if (!OpenSession())
		return FALSE;

	CString strCommand = CreateSelectAllCommand(LockModeNoLock);
	AddWhereCondition(strCommand, strField, lForeignKey);

	CDBPropSet oDBPropSet(DBPROPSET_ROWSET);
	InitDBPropSet(oDBPropSet);

	if (!ExecuteQuery(strCommand, &oDBPropSet))
		return FALSE;

	if (!DeleteAllDataFromTheRowset())
		return FALSE;

	CloseSession();

	return TRUE;
}

///<summary> Селектира всички записи по даден Foreign Key </summary>
template <class T>
BOOL SelectAllWhereForeignKey(const CString& strField, const T& lForeignKey, CTypedAutoPtrArray<TableStructure>& oTableStructureArray)
{
	if (!OpenSession())
		return FALSE;

	CString strCommand = CreateSelectAllCommand(LockModeNoLock);
	AddWhereCondition(strCommand, strField, lForeignKey);

	if (!ExecuteQuery(strCommand))
		return FALSE;

	if (!LoadData(oTableStructureArray))
		return FALSE;

	CloseSession();

	return TRUE;
}

// PRIVATE METHODS

private:
///<summary> Взема референция към сесията </summary>
CSession& GetSession() const
{
	return *m_pSession;
}

///<summary> Отваря сесията, ако е вътрешна </summary>
BOOL OpenSession()
{
	if (!m_bIsSessionInternal)
		return TRUE;
	
	HRESULT oResult = GetSession().Open(CDataBase::GetDataBase().GetDataSource());

	if (oResult != S_OK)
	{
		TRACE(_T("Unable to open session."));
		return FALSE;
	}
	
	return TRUE;
}

///<summary> Затваря сесията, ако е вътрешна </summary>
void CloseSession()
{
	if (m_bIsSessionInternal)
		GetSession().Close();
	
	Close();
}

///<summary> Изпълнява SQL заявка </summary>
BOOL ExecuteQuery(const CString& strQuery, CDBPropSet* pDbPropSet = NULL)
{
	HRESULT oResult = Open(*m_pSession, CT2W(strQuery), pDbPropSet);

	if (FAILED(oResult))
	{
		CloseSession();
		return FALSE;
	}

	return TRUE;
}

///<summary> Пълни масив със селектираните данни </summary>
BOOL LoadData(CTypedAutoPtrArray<TableStructure>& oTableStructureArray)
{
	HRESULT oResult = MoveFirst();
	while (oResult == S_OK)
	{
		TableStructure* pTableStructure = new TableStructure();
		GetInfoFromRow(*pTableStructure);
		oTableStructureArray.Add(pTableStructure);

		oResult = MoveNext();
	}

	if (oResult != DB_S_ENDOFROWSET)
	{
		CloseSession();
		return FALSE;
	}

	return TRUE;
}

///<summary> Пълни таблична структура със селектираните данни </summary>
BOOL LoadData(TableStructure& oTableStructure)
{
	HRESULT oResult = MoveFirst();
	if (FAILED(oResult))
	{
		CloseSession();
		return FALSE;
	}

	GetInfoFromRow(oTableStructure);

	return TRUE;
}

///<summary> Започва транзакция, ако сесията в вътрешна за класа </summary>
BOOL StartTransaction()
{
	if (!m_bIsSessionInternal)
		return TRUE;

	HRESULT oResult = m_pSession->StartTransaction();
	if (FAILED(oResult))
	{
		GetSession().Close();
		TRACE("The transaction is denied!");
		return FALSE;
	}

	return TRUE;
}

///<summary> Rollback-ва транзакцията и затваря сесията </summary>
BOOL AbortAndCloseSession()
{
	if (!m_bIsSessionInternal)
		return TRUE;
	
	HRESULT oResult = GetSession().Abort();
	if (FAILED(oResult))
	{
		TRACE("An error occurred while aborting the transaction!");
		return FALSE;
	}


	CloseSession();
	
	return TRUE;
}

///<summary> Променя селектирания запис в базата данни и го записва обратно в табличната структура </summary>
BOOL UpdateRecord(TableStructure& oTableStructure)
{
	GetUpdateCounterValue(oTableStructure)++;
	SetInfoForRow(oTableStructure);

	HRESULT oResult = SetData(SecondAccessor);
	if (FAILED(oResult))
	{
		TRACE("Editing has failed! The data is incomplete or inaccurate!");
		AbortAndCloseSession();
		return FALSE;
	}

	return TRUE;
}

///<summary> Добавя нов запис в базата данни  </summary>
BOOL InsertRecord(TableStructure& oTableStructure)
{
	SetInfoForRow(oTableStructure);

	HRESULT oResult = CCommand<CAccessor<AccessorType>>::Insert(SecondAccessor);
	if (FAILED(oResult))
	{
		CloseSession();
		return FALSE;
	}

	return TRUE;
}

///<summary> Записва последния запис в Rowset-a в таблична структура </summary>
BOOL GetInsertedData(TableStructure& oTableStructure)
{
	MoveLast();
    HRESULT	oResult = GetData(FirstAccessor);
	if (FAILED(oResult))
	{
		CloseSession();
		TRACE("The record was added to the database, but there is a problem with GetData() after that!");
	}

	GetInfoFromRow(oTableStructure);

	return TRUE;
}

///<summary> Изтрива всички селектирани записи в базата данни </summary>
BOOL DeleteAllDataFromTheRowset()
{
	HRESULT oResult = MoveFirst();
	while (oResult == S_OK)
	{
		oResult = Delete();
		if (oResult != S_OK)
		{
			TRACE("An error occurred while deleting the data!");
			CloseSession();
			return FALSE;
		}

		oResult = MoveNext();
	}

	if (oResult != DB_S_ENDOFROWSET)
	{
		TRACE("An error occurred while deleting the data!");
		CloseSession();
		return FALSE;
	}

	return TRUE;
}

BOOL CommitTransaction()
{
	if (!m_bIsSessionInternal)
		return TRUE;

	HRESULT oResult = GetSession().Commit();
	if (FAILED(oResult))
	{
		GetSession().Abort();
		return FALSE;
	}

	return TRUE;
}

void InitDBPropSet(CDBPropSet& oDBProperties)
{
	oDBProperties.AddProperty(DBPROP_CANFETCHBACKWARDS, true); //индикира дали може да отиде и да вземе назад rowset
	oDBProperties.AddProperty(DBPROP_IRowsetScroll, true);
	oDBProperties.AddProperty(DBPROP_IRowsetChange, true);
	oDBProperties.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	oDBProperties.AddProperty(DBPROP_IMMOBILEROWS, true);
}

template <class T = long>
BOOL SelectWhereIdWithLockMode(const T& lId, TableStructure& oTableStructure, CSession& oSession, const LockModes& eLockMode)
{
	CString strQuery = CreateSelectAllCommand(eLockMode);
	AddWhereCondition(strQuery, ID_FIELD, lId);

	CDBPropSet oDBPropSet(DBPROPSET_ROWSET);
	InitDBPropSet(oDBPropSet);

	if(!ExecuteQuery(strQuery, &oDBPropSet))
		return FALSE;

	if (!LoadData(oTableStructure))
		return FALSE;

	return TRUE;
}

CString CreateSelectAllCommand(const LockModes& eLockMode) const
{
	CString strQuery;
	strQuery.Format(SELECT_ALL_FROM_TABLE_COMMAND);

	strQuery.Replace("{TABLE_NAME}", strTableName);

	switch (eLockMode)
	{
	case LockModeUpdateLock:
		strQuery.Append(UPDLOCK);
		break;

	case LockModeNoLock:
	default:
		break;
	}

	return strQuery;
}

void AddWhereCondition(CString& strSqlCommand, const CString& strFieldName, const long& lValue) const
{
	CString strCondition;
	strCondition.Format(" WHERE %s = %i", strFieldName, lValue);
	strSqlCommand.Append(strCondition);
}

// Members
// ----------------
private:
	CString strTableName;
	CSession* m_pSession;
	BOOL m_bIsSessionInternal;
};