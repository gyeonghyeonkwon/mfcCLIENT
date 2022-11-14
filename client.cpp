
// client.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "client.h"
#include "clientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CclientApp

BEGIN_MESSAGE_MAP(CclientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CclientApp 생성

CclientApp::CclientApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CclientApp 개체입니다.

CclientApp theApp;


// CclientApp 초기화

BOOL CclientApp::InitInstance()
{
	
	CWinApp::InitInstance();

	CclientDlg dlg;
	m_pMainWnd = &dlg;
    dlg.DoModal();
	
	return FALSE;
}

