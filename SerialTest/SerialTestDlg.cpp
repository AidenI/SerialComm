
// SerialTestDlg.cpp : 구현 파일
//

#include "stdafx.h"
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
	m_brush.DeleteObject();
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
	g_pCursel = new int[5];
	g_pOpenValue = new int[5];
	m_serial = NULL;	
	m_serial = new CSerialPort();
	ConnectState(false);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	m_brush.CreateSolidBrush(RGB(0, 255, 0));

	g_pCursel[0] = 2;
	g_pCursel[1] = 2; 
	g_pCursel[2] = 0;
	g_pCursel[3] = 0;
	g_pCursel[4] = 2;
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
		AfxMessageBox(_T("포트가 이미 열려있습니다.\n 입력된 포트로 재연결합니다."));
		ConnectState(false);
		ConnectPort();
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

	if(strPortNum == NULL)
	{
		AfxMessageBox(_T("포트를 입력하세요"));
		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE); // 포트 연결 후 portnum을 빈칸 상태로 재 OPEN하였을 때 send버튼 비활성화 추가.(2019.02.19)
		return;
	}
	else if(strPortNum != NULL)
	{	
		SetCombotoDCB();
		m_serial->Open(strPortNum, g_pOpenValue[0], (CSerialPort::Parity)g_pOpenValue[1], g_pOpenValue[2],
			(CSerialPort::StopBits)g_pOpenValue[3], (CSerialPort::FlowControl)g_pOpenValue[4]);	
		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
		ConnectState(true);
	}
}

void CSerialTestDlg::SetCombotoDCB()
{	
	switch(g_pCursel[0])
	{
	case 0:
		g_pOpenValue[0] = 19200;
		break;
	case 1:
		g_pOpenValue[0] = 57600;
		break;
	case 2:
		g_pOpenValue[0] = 115200;
		break;
	default:
		AfxMessageBox(_T("Baudrate Error"));
	}

	switch(g_pCursel[1])
	{
	case 0:
		g_pOpenValue[1] = m_serial->EvenParity;
		break;
	case 1:
		g_pOpenValue[1] = m_serial->OddParity;
		break;
	case 2:
		g_pOpenValue[1] = m_serial->NoParity;
		break;
	default:
		AfxMessageBox(_T("Parity Error"));
	}

	switch(g_pCursel[2])
	{
	case 0:
		g_pOpenValue[2] = 7;
		break;
	case 1:
		g_pOpenValue[2] = 8;
		break;
	default:
		AfxMessageBox(_T("DataBit Error"));
	}
	
	switch(g_pCursel[3])
	{
	case 0:
		g_pOpenValue[3] = m_serial->OneStopBit;
		break;
	case 1:
		g_pOpenValue[3] = m_serial->TwoStopBits;
		break;
	default:
		AfxMessageBox(_T("StopBit Error"));
	}

	switch(g_pCursel[4])
	{
	case 0:
		g_pOpenValue[4] = m_serial->XonXoffFlowControl;
		break;
	case 1:
		g_pOpenValue[4] = m_serial->CtsRtsFlowControl;
		break;
	case 2:
		g_pOpenValue[4] = m_serial->NoFlowControl;
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
	// sizeof() 반환값은 size_t로 unsigned int형에 해당한다.
	GetDlgItem(IDC_EDIT_READ)->SetWindowText(static_cast<CString>(rPacket));		
}

HBRUSH CSerialTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(g_bOpenFlag == true)
	{		
		if(nCtlColor == CTLCOLOR_STATIC&& pWnd->GetDlgCtrlID() == IDC_EDIT_CNTSTATE)
		{
			pDC->SetTextColor(RGB(0,0,0));
			pDC->SetBkColor(RGB(0, 255, 0)); // 텍스트 부분 백그라운드 컬러가 변하지 않아 텍스트의 백그라운드 컬러 추가(2019.02.19)
			hbr = m_brush;
		}
	}
	else
	{
		hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	}

	return hbr;
}

void CSerialTestDlg::ConnectState(bool isOpen)
{		
	if(isOpen == true && m_serial->IsOpen() == true)
	{
		GetDlgItem(IDC_EDIT_CNTSTATE)->SetWindowText(TEXT("연결 중"));
		g_bOpenFlag = true;
	}
	else if(isOpen == false)
	{
		GetDlgItem(IDC_EDIT_CNTSTATE)->SetWindowText(TEXT("연결 대기 중"));
		g_bOpenFlag = false;
	}
}