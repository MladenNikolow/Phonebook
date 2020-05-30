#include "stdafx.h"
#include "ContextMenu.h"


CContextMenu::CContextMenu()
{
	CreatePopupMenu();
}


CContextMenu::~CContextMenu()
{
}


void CContextMenu::InitializeMenu(ContextMenuTypes eMenuType)
{
	switch (eMenuType)
	{
	case ContextMenuModify:
		AppendMenu(MF_STRING, ID_POPUP_VIEW, MENU_STRING_VIEW);
		AppendMenu(MF_STRING, ID_POPUP_EDIT, MENU_STRING_EDIT);
		AppendMenu(MF_STRING, ID_POPUP_DELETE, MENU_STRING_DELETE);
		break;
	case ContextMenuAdd:
		AppendMenu(MF_STRING, ID_POPUP_INSERT, MENU_STRING_INSERT);
		break;
	default:
		break;
	}
}