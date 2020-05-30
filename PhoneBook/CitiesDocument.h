#pragma once
#include "CitiesData.h"
#include "ModifyRecordUtilites.h"
#include "BaseDocument.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDocument

class CCitiesDocument : public CBaseDocument <CITIES, CCitiesData>
{
// Macros
// ----------------
protected: 
	DECLARE_DYNCREATE(CCitiesDocument)
	DECLARE_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
public:
	CCitiesDocument();
	virtual ~CCitiesDocument();
};
