#pragma once
#include "PhoneTypesData.h"
#include "ModifyRecordUtilites.h"
#include "BaseDocument.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDocument

class CPhoneTypesDocument : public CBaseDocument<PHONE_TYPES, CPhoneTypesData>
{
// Macros
// ----------------
	DECLARE_DYNCREATE(CPhoneTypesDocument)
	DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
public:
	CPhoneTypesDocument();
	virtual ~CPhoneTypesDocument();
};
