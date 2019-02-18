
// SerialTestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>	
#include "SerialPort.h"
#include "SerialTest.h"
#include "SerialTestDlg.h"
#include "afxdialogex.h"

#include "ChildDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSerialTestDlg 대화 상자




CSerialTestDlg::CSerialTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSerialTestDlg::IDD, pParent)
	, m_read(_T(""))
	, m_write(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CSerialTestDlg::~CSerialTestDlg()
{	
	m_serial->Close();		
}
void CSerialTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WRITE, m_write);
	DDX_Text(pDX, IDC_EDIT_READ, m_read);
	DDX_Control(pDX, IDC_EDIT_CNTSTATE, m_cnt_state);
}

BEGIN_MESSAGE_MAP(CSerialTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DCB, &CSerialTestDlg::OnBnClickedButtonDcb)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CSerialTestDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSerialTestDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSerialTestDlg::OnBnClickedButtonSend)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSerialTestDlg 메시지 처리기

BOOL CSerialTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	pCursel = new int[5];
	pOpenValue = new int[5];
	m_serial = NULL;	
	m_serial = new CSerialPort();
	ConnectState(false);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);

	pCursel[0] = 2;
	pCursel[1] = 2; 
	pCursel[2] = 0;
	pCursel[3] = 0;
	pCursel[4] = 2;
	SetCombotoDCB();

	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSerialTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSerialTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSerialTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//void CSerialTestDlg::SetThread()
//{
//	if(pThread == NULL)
//	{
//		pThread = AfxBeginThread(ThreadFunction, m_serial);	
//		if (pThread == NULL)
//		{
//			AfxMessageBox(_T("Error during Set Thread Func"));
//			return;
//		}		
//	}
//}
void CSerialTestDlg::OnBnClickedButtonDcb()
{
	CChildDlg childDlg;
	childDlg.DoModal();
	childDlg.DestroyWindow();
}


void CSerialTestDlg::OnBnClickedButtonOpen()
{
	UpdateData(TRUE);
	
	if(m_serial->IsOpen())
	{
		AfxMessageBox(_T("포트가 이미 열려있습니다."));
		return;
	}
	else
	{		
		ConnectPort();			
	}
	
}

void CSerialTestDlg::ConnectPort()
{
	int strPortNum = GetDlgItemInt(IDC_EDIT_COMPORT);
	bOpenFlag = true;
	

	if(strPortNum == NULL)
	{
		AfxMessageBox(_T("포트를 입력하세요"));
		return;
	}
	else if(strPortNum != NULL)
	{	
		SetCombotoDCB();
		m_serial->Open(strPortNum, pOpenValue[0], (CSerialPort::Parity)pOpenValue[1], pOpenValue[2],
			(CSerialPort::StopBits)pOpenValue[3], (CSerialPort::FlowControl)pOpenValue[4]);	
		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
		ConnectState(true);
	}
}

void CSerialTestDlg::SetCombotoDCB()
{	
	switch(pCursel[0])
	{
	case 0:
		pOpenValue[0] = 19200;
		break;
	case 1:
		pOpenValue[0] = 57600;
		break;
	case 2:
		pOpenValue[0] = 115200;
		break;
	default:
		AfxMessageBox(_T("Baudrate Error"));
	}

	switch(pCursel[1])
	{
	case 0:
		pOpenValue[1] = m_serial->EvenParity;
		break;
	case 1:
		pOpenValue[1] = m_serial->OddParity;
		break;
	case 2:
		pOpenValue[1] = m_serial->NoParity;
		break;
	default:
		AfxMessageBox(_T("Parity Error"));
	}

	switch(pCursel[2])
	{
	case 0:
		pOpenValue[2] = 7;
		break;
	case 1:
		pOpenValue[2] = 8;
		break;
	default:
		AfxMessageBox(_T("DataBit Error"));
	}
	
	switch(pCursel[3])
	{
	case 0:
		pOpenValue[3] = m_serial->OneStopBit;
		break;
	case 1:
		pOpenValue[3] = m_serial->TwoStopBits;
		break;
	default:
		AfxMessageBox(_T("StopBit Error"));
	}
	switch(pCursel[4])
	{
	case 0:
		pOpenValue[4] = m_serial->XonXoffFlowControl;
		break;
	case 1:
		pOpenValue[4] = m_serial->CtsRtsFlowControl;
		break;
	case 2:
		pOpenValue[4] = m_serial->NoFlowControl;
		break;
	default:
		AfxMessageBox(_T("FlowControl Error"));
	}

}

void CSerialTestDlg::OnBnClickedButtonClose()
{
	m_serial->Close();
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	ConnectState(false);
}


void CSerialTestDlg::OnBnClickedButtonSend()
{
	if(m_serial != NULL)
	{
		UpdateData(TRUE);
		char czPacket[512];
		memset(czPacket, NULL, sizeof(czPacket));
		sprintf_s(czPacket, "%s\r", m_write);
		m_serial->Purge(PURGE_TXABORT| PURGE_RXABORT |PURGE_TXCLEAR |PURGE_RXCLEAR );
		m_serial->Write(czPacket, (DWORD)strlen(czPacket));
		Delay(500);
		ReadMessage();
	}
	else
	{
		AfxMessageBox(_T("Please Open the Port"));
	}
}

void CSerialTestDlg::ReadMessage()
{	
	char rPacket[1024];
	memset(rPacket, NULL, sizeof(rPacket));
	m_serial->Read(rPacket, static_cast<DWORD>(strlen(rPacket))); 
	// C++ 형식 캐스팅 static_cast는 컴파일러에서 오류 체크로 인해 캐스팅 버그를 사전에 피할 수 있다.
	// sizeof() 반환값은 size_t로 unsigned int형에 해당한다. (DWORD는 unsigned long)
	if(rPacket != NULL)
	{
		GetDlgItem(IDC_EDIT_READ)->SetWindowTextA(static_cast<LPCTSTR>(rPacket));
		//UpdateData(FALSE); 쓰레드 사용이 updatedata는 에러를 발생시킨다.각 컨트롤마다 setwindowtest를 통해 처리하거나, 
		//PostMessage와 같이 유저메세지를 만들어 보내야한다.
	}
	else if(rPacket == NULL)
	{
		return;
	}
}

//UINT CSerialTestDlg::ThreadFunction(LPVOID _mothod)
//{	
//	CSerialTestDlg* pDlg = (CSerialTestDlg*)AfxGetApp()->GetMainWnd();
//
//	while(pDlg->bOpenFlag == true)
//	{
//		if(pDlg == NULL)
//		{
//			AfxMessageBox(_T("NULL POINTER ERROR"));
//			break;
//		}
//		else
//		{
//			pDlg->ReadMessage();
//		}		
//	}
//	return 0;
//}
	/*
	
	CServerManagerDlg 메인 다이얼로그 

	스레드와 관련없는 함수들은 타 클래스에서
	CServerManagerDlg* lpDlg = (CServerManagerDlg*)AfxGetMainWnd();
	이렇게 선언해서 가져다 썼다.
	하지만, 스레드안에서는 메인다이얼로그 포인터를 얻을수 없다.
	이유인 즉, AfxGetMainWnd() 안으로 들어가보면 

	_AFXWIN_INLINE CWnd* AFXAPI AfxGetMainWnd()
	{
		CWinThread* pThread = AfxGetThread();

		return pTrhead != NULL ? pThread->GetMainWnd() : NULL;
	}
	내부에서 AfxGetThread() 함수를 사용하는 것을 볼수가 있다.
	이것은 현재 스레드의 GetMainWnd() 함수를 호출한다.
	이것은 다른 스레드에서 메인 윈도우의 핸들이 필요할때는 문제가 된다.
	즉 다른 스레드에서 다음과 같이 AfxGetMainWnd() 함수를 호출하면 메인 윈도우의 핸들을 얻을수가 없게 된다.
	해서, 스레드에 연결된 모든 맴버 함수내에서는

	CServerManagerDlg* lpDlg = (CServerManagerDlg*)AfxGetApp()->GetMainWnd();

	이렇게 해주면 된다.
	[출처] [MFC] 다른 스레드에서 메인다이얼로그 포인터 받아오기 AfxGetMainWnd()|작성자 BaseJoe
	*/



HBRUSH CSerialTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CNTSTATE);
	if((nCtlColor == CTLCOLOR_EDIT)&&(pEdit->GetSafeHwnd() == pWnd->GetSafeHwnd()))
	{
		pDC->SetBkMode(TRANSPARENT); // 백그라운드 모드 설정
		pDC->SetTextColor(RGB(255,255,255));
		return m_brush;
	}

	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	return hbr;
}

void CSerialTestDlg::ConnectState(bool isOpen)
{		
	if(isOpen == true)
	{
		GetDlgItem(IDC_EDIT_CNTSTATE)->SetWindowTextA(TEXT("연결 중"));
	}
	else if(isOpen == false)
	{
		GetDlgItem(IDC_EDIT_CNTSTATE)->SetWindowTextA(TEXT("연결 대기 중"));
	}
}

void CSerialTestDlg::Delay(int ms)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();	

	while(GetTickCount() - dwStart < ms)  
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
