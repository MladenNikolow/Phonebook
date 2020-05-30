#include "stdafx.h"
#include "DataBase.h"

/////////////////////////////////////////////////////////////////////////////
// CDataBase

// Constructor / Destructor
// ----------------
CDataBase::CDataBase()
{
	OpenConnection();
}

CDataBase::~CDataBase()
{
}

// Methods
// ----------------
CDataBase& CDataBase::GetDataBase()
{
	static CDataBase oDataBase;

	return oDataBase;
}

CDataSource CDataBase::GetDataSource() const
{
	return m_oDataSource;
}

void CDataBase::InitDbPropSet(CDBPropSet& oDbPropSet) const
{
	oDbPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-UCGTPN5"));	// сървър
	oDbPropSet.AddProperty(DBPROP_AUTH_USERID, _T("Mladen2"));			// потребител
	oDbPropSet.AddProperty(DBPROP_AUTH_PASSWORD, _T("mladen"));			// парола
	oDbPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PHONEBOOK"));	// база данни
	oDbPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDbPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDbPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));
}

BOOL CDataBase::OpenConnection()
{
	CDBPropSet oDbPropSet(DBPROPSET_DBINIT);
	InitDbPropSet(oDbPropSet);
	HRESULT oResult = m_oDataSource.Open("SQLOLEDB", &oDbPropSet);

	if (FAILED(oResult))
	{
		AfxMessageBox("Error opening data base!");
		return FALSE;
	}

	return TRUE;
}

void CDataBase::CloseConnection()
{
	 m_oDataSource.Close();
}
