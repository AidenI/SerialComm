#pragma once
#include "afxwin.h"


// CChildDlg 대화 상자입니다.

class CChildDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlg)

public:
	CChildDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChildDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DCBDLG };

	CSerialTestDlg *pParentDlg;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_baudrate;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	void SetCombo_Value();
	CComboBox m_parity;
	CComboBox m_databit;
	CComboBox m_stopbit;
	CComboBox m_flowcontrol;
};
