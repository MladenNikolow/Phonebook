#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDataBase

//<summary> Клас, който се грижи за DataSource-а в програмата </summary>
class CDataBase
{

// Constructor / Destructor
// ----------------
private:
	CDataBase();

public:
	virtual ~CDataBase();

// Methods
// ----------------
public:
	///<summary>Създава / използва единствената инстанция на CDatabase</summary>
	static CDataBase& GetDataBase();

	///<summary> Взема data source-a </summary>
	CDataSource GetDataSource() const;

	///<summary> Затваря връзката са базата данни </summary>
	void CloseConnection();

	///<summary> Copy ctr-a е изтрит</summary>
	CDataBase (CDataBase const&) = delete;

	///<summary> Copy assignment operator-ът е изтрит </summary>
	void operator=(CDataBase const&) = delete;

private:
	void InitDbPropSet(CDBPropSet& oDbPropSet) const;
	BOOL OpenConnection();

// Members
// ----------------
private:
	CDataSource m_oDataSource;
};

