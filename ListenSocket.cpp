// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
//#include "Netmsg.h"
#include "Client_jpg.h"
#include "ListenSocket.h"
#include "NetGameStartDlg.h"
//#include "NetmsgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//The socket that listens for new connections

CListenSocket::CListenSocket(NetGameStartDlg* pDlg)
{
	m_pDlgStartGame = pDlg;
}

CListenSocket::~CListenSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenSocket, CSocket)
	//{{AFX_MSG_MAP(CListenSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions

void CListenSocket::OnAccept(int nErrorCode) 
{
    ASSERT(m_pDlgStartGame);
	m_pDlgStartGame->AcceptSock();
	CSocket::OnAccept(nErrorCode);
}
