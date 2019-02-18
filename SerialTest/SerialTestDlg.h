
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

	CSerialPort* m_serial;
	int* pCursel;
	int* pOpenValue;
	HANDLE hnd;
	CWinThread *pThread;
	bool bOpenFlag;
	CCriticalSection g_CriticalSection;

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
	afx_msg void OnBnClickedButtonDcb();	
	afx_msg void OnBnClickedButtonOpen();
	void SetCombotoDCB();
	void ReadMessage();
	void ConnectPort();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonSend();
	static UINT ThreadFunction(LPVOID _mothod);
	CString m_write;
	CString m_read;
	CBrush m_brush;
	void ConnectState(bool isOpen);
	void SetThread();
	static void CallbackFunc(LPSTR lpszText, LPVOID lpData) 
    { 
        TRACE("%s", lpszText);
		AfxMessageBox(_T("��Ʈ ���� ����"));
    } 
	CButton m_cnt_state;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void Delay(int ms);
};
