// ChildDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "resource.h"
#include "SerialTestDlg.h"
#include "ChildDlg.h"



// CChildDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CChildDlg, CDialogEx)

CChildDlg::CChildDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChildDlg::IDD, pParent)
{
}

CChildDlg::~CChildDlg()
{
}

void CChildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_baudrate);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_parity);
	DDX_Control(pDX, IDC_COMBO_DATABIT, m_databit);
	DDX_Control(pDX, IDC_COMBO_STOPBIT, m_stopbit);
	DDX_Control(pDX, IDC_COMBO_FLOWCONTROL, m_flowcontrol);
}


BEGIN_MESSAGE_MAP(CChildDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChildDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CChildDlg �޽��� ó�����Դϴ�.


BOOL CChildDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pParentDlg = (CSerialTestDlg*)GetParent();	
	
	SetCombo_Value();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CChildDlg::SetCombo_Value()
{
	if(pParentDlg != NULL)
	{
		m_baudrate.SetCurSel(pParentDlg->pCursel[0]);	
		m_parity.SetCurSel(pParentDlg->pCursel[1]);
		m_databit.SetCurSel(pParentDlg->pCursel[2]);
		m_stopbit.SetCurSel(pParentDlg->pCursel[3]);
		m_flowcontrol.SetCurSel(pParentDlg->pCursel[4]);
	}
}
void CChildDlg::OnBnClickedOk()
{
	pParentDlg->pCursel[0] = m_baudrate.GetCurSel();
	pParentDlg->pCursel[1] = m_parity.GetCurSel();
	pParentDlg->pCursel[2] = m_databit.GetCurSel();
	pParentDlg->pCursel[3] = m_stopbit.GetCurSel();
	pParentDlg->pCursel[4] = m_flowcontrol.GetCurSel();
	CDialogEx::OnOK();
}
