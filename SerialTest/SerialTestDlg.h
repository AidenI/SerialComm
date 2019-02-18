
// SerialTestDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "resource.h"

class CSerialPort;


// CSerialTestDlg ��ȭ ����
class CSerialTestDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSerialTestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.	
	~CSerialTestDlg();
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SERIALTEST_DIALOG };

// �������� 
	CSerialPort* m_serial;
	int* g_pCursel;
	int* g_pOpenValue;	
	bool g_bOpenFlag;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonDcb();	
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonSend();
	void SetCombotoDCB();
	void ReadMessage();
	void ConnectPort();
	void ConnectState(bool isOpen);
	CString m_write;
	CString m_read;
	CBrush m_brush;	
	CButton m_cnt_state;	
};
