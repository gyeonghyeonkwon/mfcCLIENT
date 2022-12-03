
// clientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "client.h"
#include "clientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



int MyClient::ProcessRecvData(SOCKET ah_socket, unsigned a_msg_id, char* ap_recv_data, BS a_body_size)

{
	if (a_msg_id == NM_CHAT_DATA) { // 수신된 데이터가 채팅 데이터인 경우 리스트박스에 추가한다
		mp_parent -> AddEventString((wchar_t *)ap_recv_data);
	}
	return 1;
}
// CclientDlg 대화 상자



CclientDlg::CclientDlg(CWnd* pParent /*=nullptr*/) //대화상자의 주소가 넘어옴
	: CDialogEx(IDD_CLIENT_DIALOG, pParent) , m_client(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
}

BEGIN_MESSAGE_MAP(CclientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND_BTN, &CclientDlg::OnBnClickedSendBtn)
	ON_MESSAGE(26001, &CclientDlg::OnConnected)  // 접속한 서버에서 데이터를 전송하거나 접속을 해제할 때 발생하는 메시지를 처리한다.
	ON_MESSAGE(26002, &CclientDlg::OnReadAndClose)  // 접속한 서버에서 데이터를 전송하거나 접속을 해제할 때 발생하는 메시지를 처리한다.
END_MESSAGE_MAP()


// CclientDlg 메시지 처리기

BOOL CclientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	m_client.ConnectToServer(L"192.168.219.104", 50000, m_hWnd); //아이피가 192.168.219.104 이고 포트가 50000 이 설정되어있는 서버에 접속을한다   


	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CclientDlg::OnPaint()
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
HCURSOR CclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CclientDlg::OnBnClickedSendBtn()
{

	CString str;
	// 에디트 컨트롤에 입력된 글을 가져온다.
	GetDlgItemText(IDC_CHAT_EDIT, str);
	SetDlgItemText(IDC_CHAT_EDIT, L"");
	// 채팅 메시지를 서버로 전송한다. 문자열을 전송할 때는 NULL 문자를 포함해서 전송하기 때문에 
	// 문자열 길이에 1을 더하고 유니코드에서 문자 1개는 2바이트를 차지하기 때문에 문자열 길이에 2를 곱한다.
	if (m_client.IsConnected()) {
		m_client.SendFrameData(NM_CHAT_DATA, (const char*)(const wchar_t*)str, (str.GetLength() + 1) * 2);
	}
}

void CclientDlg::AddEventString(const wchar_t* ap_string) //리스트박스에 문자열이 추가가되고 커서가 자동으로 설정이된다
{
	int index = m_event_list.InsertString(-1, ap_string);
	m_event_list.SetCurSel(index); 
}

afx_msg LRESULT CclientDlg::OnConnected(WPARAM wParam, LPARAM lParam)
{
	if (m_client.ResultOfConnection(lParam) == 1) {  // 서버 접속에 대한 결과를 알려주는 메시지를 처리한다.
		AddEventString(L"서버에접속하였습니다");
	}
	else {
		AddEventString(L"서버에 접속 할 수 없습니다"); // 접속한 서버에서 데이터를 전송하거나 접속을 해제할 때 발생하는 메시지를 처리한다.
								
	}

	return 0;
}


afx_msg LRESULT CclientDlg::OnReadAndClose(WPARAM wParam, LPARAM lParam) { // 접속한 서버에서 데이터를 전송하거나 접속을 해제할 때 발생하는 메시지를 처리한다.
								       
	m_client.ProcessServerEvent(wParam, lParam);
	return 0;
}
