
// SerialTestDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "resource.h"

class CSerialPort;


// CSerialTestDlg 대화 상자
class CSerialTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CSerialTestDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.	
	~CSerialTestDlg();
// 대화 상자 데이터입니다.
	enum { IDD = IDD_SERIALTEST_DIALOG };

// 전역변수 
	CSerialPort* m_serial;
	int* g_pCursel;
	int* g_pOpenValue;	
	bool g_bOpenFlag;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
