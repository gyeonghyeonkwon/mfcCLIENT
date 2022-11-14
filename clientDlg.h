
// clientDlg.h: 헤더 파일
//

#pragma once
#define NM_CHAT_DATA 1

class CclientDlg;  //컴파일시 에러메세지 발생시키지않음

class MyClient : public TW_ClientSocket
{
private:
	CclientDlg* mp_parent;
public:
	MyClient(CclientDlg* ap_parent) : TW_ClientSocket(0x27)
	{
		mp_parent = ap_parent; //클라이언트 소켓 사용
	}
	virtual int ProcessRecvData(SOCKET ah_socket, unsigned a_msg_id, char* ap_recv_data, BS a_body_size);
};

// CclientDlg 대화 상자
class CclientDlg : public CDialogEx
{
private:
	MyClient m_client;

// 생성입니다.
public:
	CclientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	void AddEventString(const wchar_t* ap_string);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_event_list;
	afx_msg void OnBnClickedSendBtn();
protected:
	afx_msg LRESULT OnConnected(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReadAndClose(WPARAM wParam, LPARAM lParam);
};
