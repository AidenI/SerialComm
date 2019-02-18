// ChildDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "resource.h"
#include "SerialTestDlg.h"
#include "ChildDlg.h"



// CChildDlg 대화 상자입니다.

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


// CChildDlg 메시지 처리기입니다.


BOOL CChildDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pParentDlg = (CSerialTestDlg*)GetParent();	
	
	SetCombo_Value();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CChildDlg::SetCombo_Value()
{
	if(pParentDlg != NULL)
	{
		m_baudrate.SetCurSel(pParentDlg->g_pCursel[0]);	
		m_parity.SetCurSel(pParentDlg->g_pCursel[1]);
		m_databit.SetCurSel(pParentDlg->g_pCursel[2]);
		m_stopbit.SetCurSel(pParentDlg->g_pCursel[3]);
		m_flowcontrol.SetCurSel(pParentDlg->g_pCursel[4]);
	}
}
void CChildDlg::OnBnClickedOk()
{
	pParentDlg->g_pCursel[0] = m_baudrate.GetCurSel();
	pParentDlg->g_pCursel[1] = m_parity.GetCurSel();
	pParentDlg->g_pCursel[2] = m_databit.GetCurSel();
	pParentDlg->g_pCursel[3] = m_stopbit.GetCurSel();
	pParentDlg->g_pCursel[4] = m_flowcontrol.GetCurSel();
	CDialogEx::OnOK();
}
