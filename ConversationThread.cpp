// ConversationThread.cpp : implementation file
//

#include "stdafx.h"
//#include "Netmsg.h"
#include "ConversationThread.h"

#include "Contact.h"
//#include "ContactView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//The thread that drives the conversation dialog

IMPLEMENT_DYNCREATE(CConversationThread, CWinThread)

CConversationThread::CConversationThread(CContact *With, char *DefaultMsg)
{
	strDefaultMsg = DefaultMsg;
	pWith = With;
    pConv = NULL;
}

CConversationThread::~CConversationThread()
{
}

BOOL CConversationThread::InitInstance()
{
    
	pConv = new CConversation(NULL, pWith, &strDefaultMsg);
	m_pMainWnd = pConv;
	pConv->DoModal();
	
    delete pConv;
	
                            // send signal to destroy the thread
    ::SendMessage(pWith->pPlayApp->GetSafeHwnd(), WM_DESTROYME, 0, (LPARAM) this);
	
    return TRUE;
}

int CConversationThread::ExitInstance()
{
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CConversationThread, CWinThread)
	//{{AFX_MSG_MAP(CConversationThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConversationThread message handlers

BOOL CConversationThread::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	
	return CWinThread::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
