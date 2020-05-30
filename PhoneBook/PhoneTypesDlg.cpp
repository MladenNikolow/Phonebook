#include "stdafx.h"
#include "PhonebookApp.h"
#include "PhoneTypesDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDlg

IMPLEMENT_DYNAMIC(CPhoneTypesDlg, CDialogEx)

BEGIN_MESSAGE_MAP(CPhoneTypesDlg, CDialogEx)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------	
CPhoneTypesDlg::CPhoneTypesDlg(const ModificationTypes& eModificationType, 
							   PHONE_TYPES& oPhoneTypes, 
	                           CWnd* pParent)
							   : CDialogEx(IDD_DLG_PHONE_TYPES, pParent),
								 m_eModificationType(eModificationType),
							     m_oPhoneTypes(oPhoneTypes)
{

}

CPhoneTypesDlg::~CPhoneTypesDlg()
{
}

// MFC Overrides
// ----------------
void CPhoneTypesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_TYPES_TYPE, m_edbPhoneTypesType);
	DDX_Control(pDX, IDOK, m_btnPhoneTypesOk);
	DDX_Control(pDX, IDCANCEL, m_btnPhoneTypesCancel);
}

BOOL CPhoneTypesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitDialogControls(m_eModificationType);

	SetDlgItemText(IDC_EDB_PHONE_TYPES_TYPE, m_oPhoneTypes.szPhoneType);

	return TRUE;
}

void CPhoneTypesDlg::OnOK()
{
	m_edbPhoneTypesType.GetWindowText(m_oPhoneTypes.szPhoneType, PHONE_TYPE_LENGTH);

	if (!IsPhoneTypeEmpty())
	{
		AfxMessageBox(DLG_EMPTY_INPUT_ERROR_MESSAGE);
		return;
	}

	CDialogEx::OnOK();
}

void CPhoneTypesDlg::OnCancel()
{
	if (m_eModificationType != ModificationTypeNone)
	{
		INT_PTR nResponse = MessageBox(DLG_ON_CANCEL_TEXT_MESSAGE, DLG_ON_CANCEL_CAPTION_TEXT, MB_OKCANCEL);
		if (nResponse == IDCANCEL)
			return;
	}

	CDialogEx::OnCancel();
}

void CPhoneTypesDlg::InitDialogControls(const ModificationTypes& eModificationType)
{
	switch (eModificationType)
	{
	case ModificationTypeNone:
		OnViewDlg();
		break;

	case ModificationTypeInsert:
		OnInsertDlg();
		break;

	case ModificationTypeEdit:
		OnEditDlg();
		break;

	default:
		break;
	}
}

void CPhoneTypesDlg::OnViewDlg()
{
	SetWindowText(PHONE_TYPES_DLG_CAPTION_VIEW);
	m_btnPhoneTypesOk.ShowWindow(SW_HIDE);
	m_btnPhoneTypesCancel.SetWindowText(DLG_BUTTON_CAPTION_VIEW);
	m_edbPhoneTypesType.SetReadOnly();
}

void CPhoneTypesDlg::OnInsertDlg()
{
	SetWindowText(PHONE_TYPES_DLG_CAPTION_INSERT);
	m_edbPhoneTypesType.SetLimitText(PHONE_TYPE_LENGTH);
	m_btnPhoneTypesOk.SetWindowText(DLG_BUTTON_CAPTION_INSERT);
}

void CPhoneTypesDlg::OnEditDlg()
{
	SetWindowText(PHONE_TYPES_DLG_CAPTION_UPDATE);
	m_edbPhoneTypesType.SetLimitText(PHONE_TYPE_LENGTH);
	m_btnPhoneTypesOk.SetWindowText(DLG_BUTTON_CAPTION_EDIT);
}

BOOL CPhoneTypesDlg::IsPhoneTypeEmpty()
{
	if (m_oPhoneTypes.szPhoneType[0] == '\0')
	{
		m_edbPhoneTypesType.SetFocus();
		return FALSE;
	}

	return TRUE;
}