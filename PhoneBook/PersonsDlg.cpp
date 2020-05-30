#include "stdafx.h"
#include "PhonebookApp.h"
#include "PersonsDlg.h"
#include "afxdialogex.h"
#include "PhoneNumbersDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDlg

// Macros
// ----------------
IMPLEMENT_DYNAMIC(CPersonsDlg, CDialogEx)
BEGIN_MESSAGE_MAP(CPersonsDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_CMB_PHONE_TYPES, &CPersonsDlg::OnCbnSelchangeCmbPhoneTypes)
	ON_NOTIFY(NM_RCLICK, IDC_LSC_PERSONS_PHONE_NUMBERS, &CPersonsDlg::OnNMRClickLscPersonsPhoneNumbers)
	ON_COMMAND(ID_POPUP_VIEW, &CPersonsDlg::OnContextMenuView)
	ON_COMMAND(ID_POPUP_EDIT, &CPersonsDlg::OnContextMenuEdit)
	ON_COMMAND(ID_POPUP_DELETE, &CPersonsDlg::OnContextMenuDelete)
	ON_COMMAND(ID_POPUP_INSERT, &CPersonsDlg::OnContextMenuInsert)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LSC_PERSONS_PHONE_NUMBERS, &CPersonsDlg::OnLvnItemActivateLscPersonsPhoneNumbers)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPersonsDlg::CPersonsDlg(const ModificationTypes& eModificationType,
						 CContact& oContact,
						 const CMap<long, long&, CITIES, CITIES&>& oCitiesMap,
						 const CPhoneTypesArray& oPhoneTypesArray,
						 CWnd* pParent) : CDialogEx(IDD_DLG_PERSONS, pParent),
										  m_eModificationType(eModificationType),
										  m_oContact(oContact),
										  m_oCitiesMap(oCitiesMap),
										  m_oPhoneTypesArray(oPhoneTypesArray)
{
}

CPersonsDlg::~CPersonsDlg()
{
}

// MFC Overrides
// ----------------
void CPersonsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnPersonsOk);
	DDX_Control(pDX, IDC_EDB_PERSONS_FULL_NAME, m_edbPersonsFullName);
	DDX_Control(pDX, IDC_EDB_PERSONS_UCN, m_edbPersonsUcn);
	DDX_Control(pDX, IDC_CMB_PERSONS_CITY, m_cmbPersonsCities);
	DDX_Control(pDX, IDC_CMB_PHONE_TYPES, m_cmbPersonsPhoneTypes);
	DDX_Control(pDX, IDC_LSC_PERSONS_PHONE_NUMBERS, m_lscPersonsPhoneNumbers);
	DDX_Control(pDX, IDC_EDB_PERSONS_ADDRESS, m_edbPersonsAddress);
	DDX_Control(pDX, IDCANCEL, m_btnPersonsCancel);
}

BOOL CPersonsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitializeDialog(m_eModificationType);

	return TRUE;
}

void CPersonsDlg::OnOK()
{
	PERSONS oPersons = ExtractPersonFromDlgControls();
	m_oContact.oPersons = oPersons;

	if (IsPersonsInfoEmpty())
	{
		AfxMessageBox(DLG_EMPTY_INPUT_ERROR_MESSAGE);
		return;
	}

	CDialogEx::OnOK();
}

void CPersonsDlg::OnCancel()
{
	if (m_eModificationType != ModificationTypeNone)
	{
		INT_PTR nResponse = MessageBox(DLG_ON_CANCEL_TEXT_MESSAGE, DLG_ON_CANCEL_CAPTION_TEXT, MB_OKCANCEL);
		if (nResponse == IDCANCEL)
			return;
	}

	CDialogEx::OnCancel();
}

// Methods
// ----------------
void CPersonsDlg::SetAllControlsToReadOnly()
{
	m_edbPersonsFullName.SetReadOnly();
	m_edbPersonsUcn.SetReadOnly();
	m_edbPersonsAddress.SetReadOnly();
	m_cmbPersonsCities.EnableWindow(FALSE);
	m_lscPersonsPhoneNumbers.EnableWindow(FALSE);
}

CString CPersonsDlg::PrepareFullName()
{
	PERSONS& oPersons = m_oContact.oPersons;

	CString strFullName = oPersons.szFirstName;
	strFullName.AppendChar(' ');
	strFullName.Append(oPersons.szMiddleName);
	strFullName.AppendChar(' ');
	strFullName.Append(oPersons.szLastName);

	return strFullName;
}

CString CPersonsDlg::GetCityAndRegionAsString(const long& lCityId)
{
	CString strCityInfo = "";

	const CMap<long, long&, CITIES, CITIES&>::CPair* pCityInfo;
	pCityInfo = m_oCitiesMap.PLookup((long&)lCityId);

	const CITIES oCities = pCityInfo->value;

	strCityInfo.Append(oCities.szName);
	strCityInfo.Append(", ");
	strCityInfo.Append(oCities.szRegion);

	return strCityInfo;
}

void CPersonsDlg::InitializeDialog(const ModificationTypes& eModificationType)
{

	switch (eModificationType)
	{
	case ModificationTypeNone:
		OnView();
		break;
	case ModificationTypeEdit:
		OnEdit();
		break;
	case ModificationTypeInsert:
		OnInsert();
		break;
	default:
		break;
	}

}

void CPersonsDlg::InitializePhoneTypesCmb()
{
	INT_PTR nIndex = m_cmbPersonsPhoneTypes.AddString(CMB_PHONE_TYPES_ALL_TEXT);
	m_cmbPersonsPhoneTypes.SetItemData(nIndex, CMB_PHONE_TYPES_ALL_DATA);

	for (INT_PTR i = 0; i < m_oPhoneTypesArray.GetCount(); ++i)
	{
		PHONE_TYPES* pPhoneTypes = m_oPhoneTypesArray.GetAt(i);
		int nIndex = m_cmbPersonsPhoneTypes.AddString(pPhoneTypes->szPhoneType);
		m_cmbPersonsPhoneTypes.SetItemData(nIndex, pPhoneTypes->lId);
	}

	// Селектирам All Phone Types 
	m_cmbPersonsPhoneTypes.SetCurSel(m_cmbPersonsPhoneTypes.FindStringExact(0, CMB_PHONE_TYPES_ALL_TEXT));
}

void CPersonsDlg::LoadAllCities()
{
	POSITION oPosition = m_oCitiesMap.GetStartPosition();

	long lCityId = 0;
	int nCmbIndex = 0;
	CITIES oCities;

	while (oPosition != NULL)
	{
		m_oCitiesMap.GetNextAssoc(oPosition, lCityId, oCities);
		nCmbIndex = m_cmbPersonsCities.AddString(GetCityAndRegionAsString(lCityId));
		m_cmbPersonsCities.SetItemData(nCmbIndex, oCities.lId);
	}
}

void CPersonsDlg::InitializeCityCmb()
{
	int nCmbIndex = 0;

	if (m_eModificationType == ModificationTypeNone)
	{
		m_cmbPersonsCities.AddString(GetCityAndRegionAsString(m_oContact.oPersons.lCityId));
		m_cmbPersonsCities.SetCurSel(nCmbIndex);
		return;

	} else
		LoadAllCities();

	//Ако сме в режим на редкатиране - се селектира града на човека
	if (m_eModificationType == ModificationTypeEdit)
	{
		PERSONS& oPersons = m_oContact.oPersons;
		CString strCity = GetCityAndRegionAsString(oPersons.lCityId);
		int nCmbCityIndex = m_cmbPersonsCities.FindString(NULL, strCity);
		m_cmbPersonsCities.SetCurSel(nCmbCityIndex);
	}
	else //Ако сме в друг режим - се селектира първия град в списъка
		m_cmbPersonsCities.SetCurSel(NULL);
}


void CPersonsDlg::InitializePhoneNumbersLsc(const INT_PTR& nPhoneTypesCmbIndex)
{
	CPhoneNumbersArray& oPhoneNumbersArray = m_oContact.oPhoneNumbersArray;

	INT_PTR nItemData = m_cmbPersonsPhoneTypes.GetItemData(nPhoneTypesCmbIndex);
	INT_PTR nItemIndex = 0;

	for (INT_PTR i = 0; i < oPhoneNumbersArray.GetCount(); ++i)
	{
		PHONE_NUMBERS* pPhoneNumbers = oPhoneNumbersArray.GetAt(i);

		if (nItemData == pPhoneNumbers->lPhoneTypeId || nItemData == CMB_PHONE_TYPES_ALL_DATA)
		{
			nItemIndex = m_lscPersonsPhoneNumbers.InsertItem(LSC_PHONE_NUMBERS_COLUMN, pPhoneNumbers->szPhoneNumber);
			m_lscPersonsPhoneNumbers.SetItemData(nItemIndex, i);
		}
	}
}

void CPersonsDlg::OnPhoneNumbersCtrlChange()
{
	if (m_lscPersonsPhoneNumbers.GetItemCount() > 0)
		m_lscPersonsPhoneNumbers.DeleteAllItems();

	int nIndex = m_cmbPersonsPhoneTypes.GetCurSel();

	if (nIndex == CB_ERR)
		return;

	InitializePhoneNumbersLsc(nIndex);
}

void CPersonsDlg::InitializeAllEdb()
{
	PERSONS oPersons = m_oContact.oPersons;
	CString strFullName = PrepareFullName();
	SetDlgItemText(IDC_EDB_PERSONS_FULL_NAME, strFullName);
	SetDlgItemText(IDC_EDB_PERSONS_UCN, oPersons.szUcn);
	SetDlgItemText(IDC_EDB_PERSONS_ADDRESS, oPersons.szStreetAddress);
}

void CPersonsDlg::SetLimitTextToAllEdb()
{
	//Полето за името е с дължина: максимална дължина за 3 имена + 3 символа (за спейсовете между тях)
	m_edbPersonsFullName.SetLimitText((PERSON_NAME_LENGTH * 3) + 3);
	m_edbPersonsAddress.SetLimitText(STREET_ADDRESS_LENGTH);
	m_edbPersonsUcn.SetLimitText(UCN_LENGTH);
}

void CPersonsDlg::OnView()
{
	SetWindowText(PERSONS_DIALOG_CAPTION_VIEW);
	m_btnPersonsOk.ShowWindow(SW_HIDE);
	m_btnPersonsCancel.SetWindowText(DLG_BUTTON_CAPTION_VIEW);

	SetAllControlsToReadOnly();
	InitializeAllEdb();
	InitializePhoneTypesCmb();
	InitializeCityCmb();
	OnPhoneNumbersCtrlChange();
}

void CPersonsDlg::OnEdit()
{
	SetWindowText(PERSONS_DIALOG_CAPTION_EDIT);
	m_btnPersonsOk.SetWindowText(DLG_BUTTON_CAPTION_EDIT);
	m_lscPersonsPhoneNumbers.ModifyStyle(NULL, LVS_SINGLESEL, NULL);

	SetLimitTextToAllEdb();
	InitializeAllEdb();
	InitializePhoneTypesCmb();
	InitializeCityCmb();
	OnPhoneNumbersCtrlChange();
}

void CPersonsDlg::OnInsert()
{
	SetWindowText(PERSONS_DIALOG_CAPTION_INSERT);
	m_btnPersonsOk.SetWindowText(DLG_BUTTON_CAPTION_INSERT);

	m_lscPersonsPhoneNumbers.ModifyStyle(NULL, LVS_SINGLESEL, NULL);
	SetLimitTextToAllEdb();
	InitializePhoneTypesCmb();
	InitializeCityCmb();
}

INT_PTR CPersonsDlg::GetLscPhoneNumbersData() const 
{
	POSITION oPosition = m_lscPersonsPhoneNumbers.GetFirstSelectedItemPosition();
	return m_lscPersonsPhoneNumbers.GetItemData(m_lscPersonsPhoneNumbers.GetNextSelectedItem(oPosition));
}

BOOL CPersonsDlg::IsSelectedLscItem() const
{
	if (!m_lscPersonsPhoneNumbers.GetFirstSelectedItemPosition())
	{
		return FALSE;
	}

	return TRUE;
}

PHONE_NUMBERS& CPersonsDlg::GetSelectedPhoneNumber()
{
	POSITION oPosition = m_lscPersonsPhoneNumbers.GetFirstSelectedItemPosition();
	INT_PTR nItemData = m_lscPersonsPhoneNumbers.GetItemData(m_lscPersonsPhoneNumbers.GetNextSelectedItem(oPosition));

	CPhoneNumbersArray& oPhoneNumbersArray = m_oContact.oPhoneNumbersArray;
	return *oPhoneNumbersArray.GetAt(nItemData);
}

INT_PTR CPersonsDlg::FindLscItemWhereData(const LPARAM& lParam)
{
	LVFINDINFOA oSearchedItem{};
	oSearchedItem.flags = LVFI_PARAM;
	oSearchedItem.lParam = lParam;
	
	return m_lscPersonsPhoneNumbers.FindItem(&oSearchedItem);
}


void CPersonsDlg::ChangeLscItemsDataAfterDelete(INT_PTR& nIndex)
{
	int nItemData = 0;
	for (int i = --nIndex; i >= 0; --i)
	{
		nItemData = m_lscPersonsPhoneNumbers.GetItemData(i);
		m_lscPersonsPhoneNumbers.SetItemData(i, (--nItemData));
	}
}

CString CPersonsDlg::GetPhoneTypeOfSelectedNumberAsString(const PHONE_NUMBERS& oPhoneNumbers)
{
	CString strType = "";
	for (INT_PTR i = 0; i < m_oPhoneTypesArray.GetCount(); ++i)
	{
		PHONE_TYPES* pPhoneTypes = m_oPhoneTypesArray.GetAt(i);

		if (pPhoneTypes->lId == oPhoneNumbers.lPhoneTypeId)
		{
			strType.Format("%s", pPhoneTypes->szPhoneType);
			break;
		}
	}

	return strType;
}

PERSONS CPersonsDlg::ExtractPersonFromDlgControls()
{
	PERSONS oPersons;
	oPersons.lId = m_oContact.oPersons.lId;
	oPersons.lUpdateCounter = m_oContact.oPersons.lUpdateCounter;

	ExtractFullNameFromDlg(oPersons);

	oPersons.lCityId = m_cmbPersonsCities.GetItemData(m_cmbPersonsCities.GetCurSel());
	
	m_edbPersonsUcn.GetWindowText(oPersons.szUcn, UCN_LENGTH);
	m_edbPersonsAddress.GetWindowText(oPersons.szStreetAddress, STREET_ADDRESS_LENGTH);

	return oPersons;
}

void CPersonsDlg::ExtractName(CString& strName, TCHAR* pName)
{
	strName.Trim();

	CString strNameToRemove = "";
	INT_PTR nLetterCounter = 0;

	for (nLetterCounter; nLetterCounter < strName.GetLength(); ++nLetterCounter)
	{
		if (strName.GetAt(nLetterCounter) != ' ')
		{
			*pName = strName.GetAt(nLetterCounter);
			strNameToRemove.AppendChar(*pName);
			pName++;
		}
		else
			break;
	}

	INT_PTR nDelete = strName.Delete(NULL, nLetterCounter);
}

void CPersonsDlg::ExtractFullNameFromDlg(PERSONS& oPersons)
{
	CString strFullName = "";
	m_edbPersonsFullName.GetWindowText(strFullName);

	ExtractName(strFullName, oPersons.szFirstName);
	ExtractName(strFullName, oPersons.szMiddleName);
	ExtractName(strFullName, oPersons.szLastName);
}

BOOL CPersonsDlg::IsPersonsInfoEmpty()
{
	PERSONS& oPersons = m_oContact.oPersons;

	return (oPersons.szFirstName[0] == '\0' ||
			oPersons.szMiddleName[0] == '\0' ||
			oPersons.szLastName[0] == '\0' ||
			oPersons.szStreetAddress[0] == '\0' ||
			oPersons.szUcn[0] == '\0');
}

void CPersonsDlg::OnContextMenuView()
{
	PHONE_NUMBERS& oPhoneNumbers = GetSelectedPhoneNumber();
	CString strPhoneType = GetPhoneTypeOfSelectedNumberAsString(oPhoneNumbers);
	INT_PTR nIndex = GetLscPhoneNumbersData();

	CPhoneNumbersDlg oPhoneNumbersDlg(ModificationTypeNone, GetSelectedPhoneNumber(), m_oPhoneTypesArray);
	INT_PTR nDlgResponse = oPhoneNumbersDlg.DoModal();
}

void CPersonsDlg::OnContextMenuEdit()
{
	PHONE_NUMBERS& oPhoneNumbers = GetSelectedPhoneNumber();
	INT_PTR nIndex = GetLscPhoneNumbersData();

	CPhoneNumbersDlg oPhoneNumbersDlg(ModificationTypeEdit, GetSelectedPhoneNumber(), m_oPhoneTypesArray);
	INT_PTR nDlgResponse = oPhoneNumbersDlg.DoModal();

	if (nDlgResponse == IDCANCEL)
		return;

	// Ако телефонният тип е непроменен - променям само номера
	if (oPhoneNumbers.lId == m_cmbPersonsPhoneTypes.GetItemData(m_cmbPersonsPhoneTypes.GetCurSel()))
		m_lscPersonsPhoneNumbers.SetItemText(FindLscItemWhereData(nIndex), LSC_PHONE_NUMBERS_COLUMN, oPhoneNumbers.szPhoneNumber);
	else
		OnPhoneNumbersCtrlChange();

}

void CPersonsDlg::OnContextMenuDelete()
{
	PHONE_NUMBERS& oPhoneNumbers = GetSelectedPhoneNumber();
	INT_PTR nIndex = GetLscPhoneNumbersData();

	CString strDeleteConfirmationMessage = MESSAGE_BOX_DELETE_PHONE_NUMBER_TEXT;
	strDeleteConfirmationMessage.Replace("{PHONE_NUMBER}", oPhoneNumbers.szPhoneNumber);
	INT_PTR nBoxResponse = MessageBox(strDeleteConfirmationMessage, MESSAGE_BOX_DELETE_PHONE_NUMBER_CAPTION, MB_OKCANCEL);

	if (nBoxResponse == IDCANCEL)
		return;

	m_oContact.oPhoneNumbersArray.RemoveAt(nIndex);

	INT_PTR nLscIndex = FindLscItemWhereData(nIndex);
	m_lscPersonsPhoneNumbers.DeleteItem(nLscIndex);

	ChangeLscItemsDataAfterDelete(nLscIndex);
}

void CPersonsDlg::OnContextMenuInsert()
{
	PHONE_NUMBERS* pPhoneNumbers = new PHONE_NUMBERS;

	CPhoneNumbersDlg oPhoneNumbersDlg(ModificationTypeInsert, *pPhoneNumbers, m_oPhoneTypesArray);
	INT_PTR nDlgResponse = oPhoneNumbersDlg.DoModal();

	if (nDlgResponse == IDCANCEL)
		return;

	INT_PTR nPhoneNumberIndex = m_oContact.oPhoneNumbersArray.Add(pPhoneNumbers);

	//Ако добавеният телефон е от селектирания тип - го добавям в LscPersonsPhoneNumbers
	INT_PTR nLscIndex = m_cmbPersonsPhoneTypes.GetItemData(m_cmbPersonsPhoneTypes.GetCurSel());
	if (nLscIndex == pPhoneNumbers->lPhoneTypeId || nLscIndex == CMB_PHONE_TYPES_ALL_DATA)
	{
		INT_PTR nLscIndex = m_lscPersonsPhoneNumbers.InsertItem(LSC_PHONE_NUMBERS_COLUMN, pPhoneNumbers->szPhoneNumber);
		m_lscPersonsPhoneNumbers.SetItemData(nLscIndex, nPhoneNumberIndex);
	}
}

// MFC Message Handlers
// ----------------
void CPersonsDlg::OnCbnSelchangeCmbPhoneTypes()
{
	OnPhoneNumbersCtrlChange();
}

void CPersonsDlg::OnNMRClickLscPersonsPhoneNumbers(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	CContextMenu oContextMenu;

	if (IsSelectedLscItem())
		oContextMenu.InitializeMenu(ContextMenuModify);
	else
		oContextMenu.InitializeMenu(ContextMenuAdd);

	CPoint oPoint;
	ClientToScreen(&oPoint);
	GetCursorPos(&oPoint);

	oContextMenu.TrackPopupMenu(TPM_LEFTALIGN, oPoint.x, oPoint.y, this);

	*pResult = 0;
}

void CPersonsDlg::OnLvnItemActivateLscPersonsPhoneNumbers(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	OnContextMenuView();

	*pResult = 0;
}
