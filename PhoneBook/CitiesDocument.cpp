#include "stdafx.h"
#include "CitiesDocument.h"
#include <propkey.h>

#ifndef SHARED_HANDLERS
#include "PhoneBookApp.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CCitiesDocument

// Macros
// ----------------
IMPLEMENT_DYNCREATE(CCitiesDocument, CDocument)

BEGIN_MESSAGE_MAP(CCitiesDocument, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CCitiesDocument::CCitiesDocument() : CBaseDocument()
{
}

CCitiesDocument::~CCitiesDocument()
{
}