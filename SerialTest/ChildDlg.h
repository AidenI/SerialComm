#pragma once
#include "afxwin.h"


// CChildDlg ��ȭ �����Դϴ�.

class CChildDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlg)

public:
	CChildDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChildDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DCBDLG };

	CSerialTestDlg *pParentDlg;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
