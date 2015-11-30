// NotifyThread.cpp : implementation file
//

#include "stdafx.h"
//#include "Netmsg.h"
#include "Client_jpg.h"
#include "NotifyThread.h"
#include "NetSocket.h"
#include "Contact.h"
#include "NetGameStartDlg.h"
//#include "MainFrm.h"
//#include "ContactView.h"
//#include "NetmsgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//This thread is running most of the time attepting to connect to the offline contacts
//once it makes a connection it will pass the socket back to the main thread

IMPLEMENT_DYNCREATE(CNotifyThread, CWinThread)

CNotifyThread::CNotifyThread()
{
}

CNotifyThread::~CNotifyThread()
{
}

BOOL CNotifyThread::InitInstance()
{
    POSITION pos;
	pos = pList->GetHeadPosition();
	view->m_pNotify = NULL;
	while (pos)
	{
		SOCKET Sock;
		CContact* pContact = pList->GetNext(pos);
		
		if ( pContact->GetSock() ) 
            continue;

		CNetSocket*  pNewSocket = new CNetSocket(pContact);	
		if (!pNewSocket->Open(pContact->GetHostName()))
		{		
			pContact->WeConnected = false;
			delete pNewSocket;
		}
		else
		{
			Sock = pNewSocket->Detach();
			::SendMessage(pContact->pPlayApp->GetSafeHwnd(), WM_SOCKCONNECT, 
                                           (WPARAM)Sock, (LPARAM)pContact);
			//pass the new socket to the main thread
			delete pNewSocket;
		}
		PostThreadMessage(WM_QUIT, 0, 0);

	}
	Sleep(1000);
	//view->Load++;
	return TRUE;
}

int CNotifyThread::ExitInstance()
{
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CNotifyThread, CWinThread)
	//{{AFX_MSG_MAP(CNotifyThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotifyThread message handlers
