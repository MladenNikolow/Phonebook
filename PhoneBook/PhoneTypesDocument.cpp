#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "PhoneBookApp.h"
#endif

#include "PhoneTypesDocument.h"
#include <propkey.h>

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDocument

// Macros
// ----------------
IMPLEMENT_DYNCREATE(CPhoneTypesDocument, CDocument)

BEGIN_MESSAGE_MAP(CPhoneTypesDocument, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPhoneTypesDocument::CPhoneTypesDocument() : CBaseDocument()
{
}

CPhoneTypesDocument::~CPhoneTypesDocument()
{
}
