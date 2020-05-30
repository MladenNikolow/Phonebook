#pragma once

struct SortViewInfo
{
	const CListCtrl& oListCtrl;
	INT_PTR nColumnIndex;

	SortViewInfo() = delete;
	SortViewInfo(const CListCtrl& oListCtrl, const INT_PTR& nIndex) : oListCtrl(oListCtrl), nColumnIndex(nIndex) {}
};

