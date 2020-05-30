#include "stdafx.h"
#include "PhoneNumbersDlg.h"
#include "afxdialogex.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersDlg

IMPLEMENT_DYNAMIC(CPhoneNumbersDlg, CDialogEx)

BEGIN_MESSAGE_MAP(CPhoneNumbersDlg, CDialogEx)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPhoneNumbersDlg::CPhoneNumbersDlg(const ModificationTypes& eModificationType, 
								   PHONE_NUMBERS& oPhoneNumbers,
							       const CPhoneTypesArray& oPhoneTypesArray,
								   CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_PHONE_NUMBERS, pParent),
	  m_eModificationType(eModificationType),
	  m_oPhoneNumbers(oPhoneNumbers),
	  m_oPhoneTypesArray(oPhoneTypesArray)
{
}

CPhoneNumbersDlg::~CPhoneNumbersDlg()
{
}

// MFC Overrides
// ----------------
void CPhoneNumbersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_PHONE_NUMBERS_TYPE, m_cmbPhoneNumbersType);
	DDX_Control(pDX, IDC_EDB_PHONE_NUMBER, m_edbPhoneNumber);
	DDX_Control(pDX, IDOK, m_btnPhoneNumbersOk);
	DDX_Control(pDX, IDCANCEL, m_btnPhoneNumbersCancel);
}

BOOL CPhoneNumbersDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	switch (m_eModificationType)
	{
	case ModificationTypeNone:
		OnInitViewDlg();
		break;

	case ModificationTypeEdit:
		OnInitEditDlg();
		break;

	case ModificationTypeInsert:
	default:
		OnInitInsertDlg();
		break;
	}

	return TRUE;
}

void CPhoneNumbersDlg::OnOK()
{
	m_edbPhoneNumber.GetWindowText(m_oPhoneNumbers.szPhoneNumber, PHONE_NUMBER_LENGTH);

	if (IsPhoneNumberEmpty() || !IsPhoneTypeSelected())
	{
		AfxMessageBox("Please fill in all fields!");
		return;
	}

	INT_PTR nCmbIndex = m_cmbPhoneNumbersType.GetCurSel();
	m_oPhoneNumbers.lPhoneTypeId = m_cmbPhoneNumbersType.GetItemData(nCmbIndex);

	CDialogEx::OnOK();
}

void CPhoneNumbersDlg::OnCancel()
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
void CPhoneNumbersDlg::SetPhoneNumberInfo()
{
	SetPhoneTypeInfo();
	SetDlgItemText(IDC_EDB_PHONE_NUMBER, m_oPhoneNumbers.szPhoneNumber);
}

void CPhoneNumbersDlg::SetPhoneTypeInfo()
{
	INT_PTR nCmbIndex = 0;
	for (INT_PTR i = 0; i < m_oPhoneTypesArray.GetCount(); ++i)
	{
		PHONE_TYPES* pPhoneTypes = m_oPhoneTypesArray.GetAt(i);

		nCmbIndex = m_cmbPhoneNumbersType.AddString(pPhoneTypes->szPhoneType);
		m_cmbPhoneNumbersType.SetItemData(nCmbIndex, pPhoneTypes->lId);
	}

	if (m_eModificationType != ModificationTypeInsert)
	{
		CString strPhoneType = GetPhoneTypeOfNumber();
		nCmbIndex = m_cmbPhoneNumbersType.FindString(NULL, strPhoneType);
		m_cmbPhoneNumbersType.SetCurSel(nCmbIndex);
	}
	else
	{
		m_cmbPhoneNumbersType.SetCurSel(NULL);
	}
}


CString CPhoneNumbersDlg::GetPhoneTypeOfNumber()
{
	CString strPhoneType = "";
	for (INT_PTR i = 0; i < m_oPhoneTypesArray.GetCount(); ++i)
	{
		PHONE_TYPES* pPhoneTypes = m_oPhoneTypesArray.GetAt(i);

		if (pPhoneTypes->lId == m_oPhoneNumbers.lPhoneTypeId)
		{
			strPhoneType.Format("%s", pPhoneTypes->szPhoneType);
			break;
		}
	}

	return strPhoneType;
}

void CPhoneNumbersDlg::OnInitViewDlg()
{
	SetPhoneNumberInfo();
	m_edbPhoneNumber.SetReadOnly();
	m_cmbPhoneNumbersType.EnableWindow(FALSE);
	m_btnPhoneNumbersOk.ShowWindow(HIDE_WINDOW);
	m_btnPhoneNumbersCancel.SetWindowText(DLG_BUTTON_CAPTION_VIEW);
}

void CPhoneNumbersDlg::OnInitEditDlg()
{
	SetPhoneNumberInfo();
	m_edbPhoneNumber.SetLimitText(PHONE_NUMBER_LENGTH);
	m_btnPhoneNumbersOk.SetWindowText(DLG_BUTTON_CAPTION_EDIT);
}

void CPhoneNumbersDlg::OnInitInsertDlg()
{
	SetPhoneTypeInfo();
	m_edbPhoneNumber.SetLimitText(PHONE_NUMBER_LENGTH);
	m_btnPhoneNumbersOk.SetWindowText(DLG_BUTTON_CAPTION_INSERT);
}

BOOL CPhoneNumbersDlg::IsPhoneNumberEmpty()
{
	if (m_oPhoneNumbers.szPhoneNumber[0] != '\0')
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPhoneNumbersDlg::IsPhoneTypeSelected()
{
	INT_PTR nCmbIndex = m_cmbPhoneNumbersType.GetCurSel();

	if (nCmbIndex == CB_ERR)
		return FALSE;

	return TRUE;
}

