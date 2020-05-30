#include "stdafx.h"
#include "PhonebookApp.h"
#include "CitiesDlg.h"
#include "afxdialogex.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDlg

IMPLEMENT_DYNAMIC(CCitiesDlg, CDialogEx)

BEGIN_MESSAGE_MAP(CCitiesDlg, CDialogEx)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CCitiesDlg::CCitiesDlg(const ModificationTypes& eModifyType, CITIES& oCities, CWnd* pParent)
	: CDialogEx(IDD_DLG_CITIES, pParent),
	  m_oCities(oCities),
	  m_eModificationType(eModifyType)
{
}

CCitiesDlg::~CCitiesDlg()
{
}

// MFC Overrides
// ----------------
void CCitiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_CITIES_NAME, m_edbCityName);
	DDX_Control(pDX, IDC_EDB_CITIES_REGION, m_edbCityRegion);
	DDX_Control(pDX, IDOK, m_btnCityOk);
	DDX_Control(pDX, IDCANCEL, m_btnCityCancel);
}

BOOL CCitiesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitDialogControls(m_eModificationType);

	SetDlgItemText(IDC_EDB_CITIES_NAME, m_oCities.szName);
	SetDlgItemText(IDC_EDB_CITIES_REGION, m_oCities.szRegion);

	return TRUE;
}

void CCitiesDlg::OnOK()
{
	m_edbCityName.GetWindowText(m_oCities.szName, CITY_NAME_LENGTH);
	m_edbCityRegion.GetWindowText(m_oCities.szRegion, REGION_NAME_LENGTH);

	if (!IsCityValid())
	{
		AfxMessageBox(DLG_EMPTY_INPUT_ERROR_MESSAGE);
		return;
	}

	CDialogEx::OnOK();
}

void CCitiesDlg::OnCancel()
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
void CCitiesDlg::InitDialogControls(const ModificationTypes& eModificationType)
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

void CCitiesDlg::SetAllEdbTextLimits()
{
	m_edbCityName.SetLimitText(CITY_NAME_LENGTH);
	m_edbCityRegion.SetLimitText(REGION_NAME_LENGTH);
}

void CCitiesDlg::OnViewDlg()
{
	SetWindowText(CITIES_DIALOG_CAPTION_VIEW);
	m_btnCityOk.ShowWindow(SW_HIDE);
	m_btnCityCancel.SetWindowText(DLG_BUTTON_CAPTION_VIEW);
	SetAllEdbToReadOnly();
}

void CCitiesDlg::OnInsertDlg()
{
	SetWindowText(CITIES_DIALOG_CAPTION_INSERT);
	SetAllEdbTextLimits();
	m_btnCityOk.SetWindowText(DLG_BUTTON_CAPTION_INSERT);
}

void CCitiesDlg::OnEditDlg()
{
	SetWindowText(CITIES_DIALOG_CAPTION_EDIT);
	SetAllEdbTextLimits();
	m_btnCityOk.SetWindowText(DLG_BUTTON_CAPTION_EDIT);
}

void CCitiesDlg::SetAllEdbToReadOnly()
{
	m_edbCityName.SetReadOnly();
	m_edbCityRegion.SetReadOnly();
}

BOOL CCitiesDlg::IsCityValid()
{
	//Валидира се само дали името и региона на град са празни

	if (m_oCities.szName[0] == '\0')
	{
		m_edbCityName.SetFocus();
		return FALSE;
	}

	if (m_oCities.szRegion[0] == '\0')
	{
		m_edbCityRegion.SetFocus();
		return FALSE;
	}

	return TRUE;
}
