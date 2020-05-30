#pragma once
#include "afxwin.h"
#include "Resource.h"

enum ContextMenuTypes
{
	ContextMenuAdd,
	ContextMenuModify
};

#define MENU_STRING_VIEW "View"
#define MENU_STRING_EDIT "Edit"
#define MENU_STRING_DELETE "Delete"
#define MENU_STRING_INSERT "Add Record"

/// <summary> Конектсуално меню с опции за модифициране (View, Edit, Delete, Add) </summary>
class CContextMenu :
	public CMenu
{
// Constructor / Destructor
// ----------------
public:
	CContextMenu();
	virtual ~CContextMenu();

// Methods
// ----------------
public:
	void InitializeMenu(ContextMenuTypes eMenuType);
};

