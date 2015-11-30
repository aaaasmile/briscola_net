// NetGameStartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client_jpg.h"
#include "NetGameStartDlg.h"
#include "ListenSocket.h"
#include "NetSocket.h"
#include "NotifyThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NetGameStartDlg dialog


NetGameStartDlg::NetGameStartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(NetGameStartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(NetGameStartDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

    m_pListenSocket = NULL;
    m_pNICInfo = NULL;
    m_iNICCount = 0;
    m_bPlaying = FALSE;
    m_pNotify = NULL;
    m_bTimerNotifySet = FALSE;
    m_byIP_1 = 127;
    m_byIP_2 = 0;
    m_byIP_3 = 0;
    m_byIP_4 = 1;
}


void NetGameStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NetGameStartDlg)
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipRemoteMazziere);
	DDX_Control(pDX, IDC_ANI_WAIT, m_aniWait);
    DDX_Control(pDX, IDC_BT_CHAT, m_btChat);
    DDX_Control(pDX, IDC_BT_STARTMAZZ, m_btStartServer);
    DDX_Control(pDX, IDC_BT_BREAK, m_btStop);
    DDX_Control(pDX, IDC_BT_CONNREMOTE, m_btConnectGameRemote);
    DDX_Control(pDX, IDC_LST_PLAYERS, m_lstbPlayer);
    DDX_Control(pDX, IDC_BT_PLAYWITH, m_btInvite);
    DDX_Control(pDX, IDC_BT_LEAVENET, m_btDisconnet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NetGameStartDlg, CDialog)
	//{{AFX_MSG_MAP(NetGameStartDlg)
	ON_BN_CLICKED(IDC_BT_STARTMAZZ, OnBtStartmazz)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BT_BREAK, OnBtBreak)
	ON_BN_CLICKED(IDC_BT_CHAT, OnBtChat)
	ON_BN_CLICKED(IDC_BT_CONNREMOTE, OnBtConnremote)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BT_LEAVENET, OnBtLeavenet)
	ON_BN_CLICKED(IDC_BT_PLAYWITH, OnBtPlaywith)
    ON_MESSAGE(WM_REMOTENAMENEW, OnNewNameRemote)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NetGameStartDlg message handlers


////////////////////////////////////////
//       OnInitDialog
/*! 
*/
BOOL NetGameStartDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    pickInfoNic();

    m_btStop.EnableWindow(FALSE); 
    if (m_ListCont.GetCount() == 0 )
    {
        m_btChat.EnableWindow(FALSE);
        m_btInvite.EnableWindow(FALSE);
        m_btDisconnet.EnableWindow(FALSE);
    }

    //m_ipRemoteMazziere.SetAddress(192,168,1,1);
    //m_ipRemoteMazziere.SetAddress(127,0,0,1);
	m_ipRemoteMazziere.SetAddress((byte)m_byIP_1, (byte)m_byIP_2, (byte)m_byIP_3, (byte)m_byIP_4);

    if ( m_bNetGame )
    {
        disableBecauseOnPlay();
    }

                            // fill contact list box
    buildList();
		
	return TRUE;  
}


////////////////////////////////////////
//       disableBecauseOnPlay
/*! 
*/
void NetGameStartDlg::disableBecauseOnPlay()
{
    m_btChat.EnableWindow(TRUE);
    m_btDisconnet.EnableWindow(TRUE);

    m_btInvite.EnableWindow(FALSE);
    m_btStop.EnableWindow(FALSE);
    m_btConnectGameRemote.EnableWindow(FALSE);
    m_btStartServer.EnableWindow(FALSE);
}

////////////////////////////////////////
//       OnDestroy
/*! 
*/
void NetGameStartDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
    if (m_pListenSocket)
    {
        delete m_pListenSocket;
        m_pListenSocket = NULL;
    }

    if (m_pNICInfo)
    {
        delete []m_pNICInfo;
        m_pNICInfo = NULL;
    }
    animStop();

}



////////////////////////////////////////
//       pickInfoNic
/*! Retrieve Nic information
*/
void NetGameStartDlg::pickInfoNic()
{
    MibII m;

	int rv = m.Init();
	if (rv < 0)
		return ;

                            // get information about local NIC
	m_iNICCount = m.GetNICCount(true, true);
	if (m_iNICCount > 0)
	{
		m_pNICInfo = new tSTRUCTNICINFO [m_iNICCount];
		m.GetNICInfo(m_pNICInfo);
	}
}

////////////////////////////////////////
//       animStart
/*! start animation for aiting to connection
*/
int NetGameStartDlg::animStart()
{
    if (!m_bPlaying) 
    {
        m_aniWait.Open(IDR_ANIMATEWAIT);
		m_aniWait.Play(0, -1, -1);
		m_bPlaying = TRUE;
	}
    return 0;
}


////////////////////////////////////////
//       animStop
/*! Stop animation
*/
int NetGameStartDlg::animStop()
{
    if (m_bPlaying) 
    {
		m_aniWait.Stop();
		m_bPlaying = FALSE;

        m_aniWait.Close();

        Invalidate();
	}
    return 0;
}


////////////////////////////////////////
//       AcceptSock
/*! Callback from socket listener
*/
void NetGameStartDlg::AcceptSock()
{
    unsigned int PeerPort;
	CString PeerAddress;
	                        // create a session socket
    CNetSocket* NewSock = new CNetSocket;
	
    m_pListenSocket->Accept(*NewSock);
	NewSock->Init();
	NewSock->GetPeerName(PeerAddress, PeerPort);

    setOnline(IP(PeerAddress), NewSock);

}


////////////////////////////////////////
//       findContact
/*! Provides contact from IP
// \param IP HostName : IP to be searched
*/
CContact* NetGameStartDlg::findContact(IP HostName)
{
    CContact*  pContact = NULL;
    
    POSITION pos;
	pos = m_ListCont.GetHeadPosition();
	while (pos)
	{
		pContact = m_ListCont.GetNext(pos);
		if (pContact->GetHostName() == HostName)
        {
            break;
        }
        else
        {
            pContact = NULL;
        }
	}

    return pContact;
}


////////////////////////////////////////
//       ExportConctactList
/*! Export the conctact list
// \param CList*  pList : 
*/
BOOL NetGameStartDlg::ExportConctactList(LIST_CONTACT*  pList)
{
    CContact*  pContact = NULL;
    if ( pList == NULL )
    {
        ASSERT(0);
        return FALSE;
    }
    
    pList->RemoveAll();

    POSITION pos;
	pos = m_ListCont.GetHeadPosition();
	while (pos)
	{
		pContact = m_ListCont.GetNext(pos);
                            // dialog is being destroyed, set the pointer of NULL
        pContact->pDlgList = NULL;
        pList->AddTail(pContact); 
	}

    return TRUE;
}


////////////////////////////////////////
//       ImportConctactList
/*! Import conctact list
// \param LIST_CONTACT*  pList : 
*/
BOOL NetGameStartDlg::ImportConctactList(LIST_CONTACT*  pList)
{
    CContact*  pContact = NULL;
    if ( pList == NULL )
    {
        ASSERT(0);
        return FALSE;
    }
    
    m_ListCont.RemoveAll();

    POSITION pos;
	pos = pList->GetHeadPosition();
	while (pos)
	{
		pContact = pList->GetNext(pos);
                            // update the dialog pointer
        pContact->pDlgList = this;
        m_ListCont.AddTail(pContact); 
	}

    return TRUE;
}

////////////////////////////////////////
//       setOnline
/*! Remote contact is going online
// \param IP HostName : remote host 
// \param CNetSocket *ClientSocket : associated session socket 
*/
void NetGameStartDlg::setOnline(IP HostName, CNetSocket *pClientSocket)
{
	CContact* pContact = findContact(HostName);
    CContact* pConMe = NULL;
	if (!pContact)
	{
                            // create a new contact and make a recursive call
		pContact = new CContact;
        pConMe = new CContact;
        pConMe->SetHost(IP(m_pNICInfo->IP[0], m_pNICInfo->IP[1], m_pNICInfo->IP[2], m_pNICInfo->IP[3]));
        pConMe->SetScreenName(const_cast<char*>((LPCTSTR)m_strPlayerName));
        pConMe->SetSock(pClientSocket);
        pConMe->pPlayApp = m_pCallerDlg;

		pContact->SetSock(pClientSocket);
		pClientSocket->SetRemoteContact(pContact);
        pClientSocket->SetMeContact(pConMe);

		pContact->SetScreenName("Sfidante sconosciuto");
		pContact->SetHost(HostName);
		m_ListCont.AddTail(pContact);
        
        CContact* pNewContact = findContact(HostName);
        ASSERT(pNewContact);
        pNewContact->Flags |= CContact::CFL_AUTHENTICATE_NO;
		
        setOnline(HostName, pClientSocket);
		return;
	}
	else if ( pContact && !(pContact->Flags & CContact::CFL_BLOCKED) && 
              !(pContact->Flags & CContact::CFL_AUTHENTICATE_NO))
	{
        pContact->SetSock(pClientSocket);
        CNetSocket* pSocket = pContact->GetSock();
        ASSERT(pSocket->GetConctactMe());
        
		pSocket->SendString("NAME %s", pSocket->GetConctactMe()->GetScreenName());
	}
	else if ( pContact && (pContact->Flags & CContact::CFL_BLOCKED) && 
              !(pContact->Flags & CContact::CFL_AUTHENTICATE_NO))
	{
		pContact->SetSock(pClientSocket);
		pContact->GetSock()->SendString("OFFLINE");
	}
	pClientSocket->SetRemoteContact(pContact);
    pContact->SetSock(pClientSocket);
    if (pClientSocket->GetConctactMe() == NULL )
    {
        pConMe = new CContact;
        pConMe->SetHost(IP(m_pNICInfo->IP[0], m_pNICInfo->IP[1], m_pNICInfo->IP[2], m_pNICInfo->IP[3]));
        pConMe->SetScreenName(const_cast<char*>((LPCTSTR)m_strPlayerName));
        pConMe->SetSock(pClientSocket);
        pClientSocket->SetMeContact(pConMe);
        pConMe->pPlayApp = m_pCallerDlg;
    }
	
                            // contact have to pointer to client_jpg and this dialog 
                            //to update the name list
    ASSERT(m_pCallerDlg);
	pContact->pPlayApp = m_pCallerDlg;
    pContact->pDlgList = this;

    buildList();
}


////////////////////////////////////////
//       buildList
/*! visualize the list of all contacts
*/
void NetGameStartDlg::buildList()
{
    POSITION pos;
    BOOL bEnableChat = FALSE;
    m_lstbPlayer.ResetContent();
	pos = m_ListCont.GetHeadPosition();
    BOOL bOffline = FALSE;
	while (pos)
	{
		CContact* pContact = m_ListCont.GetNext(pos);
        CString strName = pContact->GetScreenName();
        
        strName += "( " + pContact->GetHostName().Get()  + ")";
        
        bEnableChat = TRUE;
        
        m_lstbPlayer.AddString(strName);
        
	}
    if ( bEnableChat )
    {
        m_btChat.EnableWindow(TRUE);
        if (!m_bNetGame)
            m_btInvite.EnableWindow(TRUE);

        m_btDisconnet.EnableWindow(TRUE);
    }
}

////////////////////////////////////////
//       addContact
/*! Add a new mazziere contact 
// \param IP HostName : remote mazziere hostname
*/
CContact* NetGameStartDlg::addContact(IP HostName)
{
	if (findContact(HostName)) 
        return findContact(HostName);

                            // create a new contact
	CContact* pContact = new CContact;
    CContact* pConMe = new CContact;
    

                            // initialize value's contact
	pContact->SetScreenName("User sconosciuto");
	pContact->SetHost(HostName);
    CNetSocket* pClientSocket = new CNetSocket(pContact);
	pContact->SetSock(pClientSocket);
    pContact->pPlayApp = m_pCallerDlg;
	pContact->pDlgList = this;

    
    pConMe->SetHost(IP(m_pNICInfo->IP[0], m_pNICInfo->IP[1], m_pNICInfo->IP[2], m_pNICInfo->IP[3]));
    pConMe->SetScreenName(const_cast<char*>((LPCTSTR)m_strPlayerName));
    pConMe->SetSock(pClientSocket);

    pClientSocket->SetMeContact(pConMe);
    pClientSocket->SetRemoteContact(pContact);

                            // add to contact list
    m_ListCont.AddTail(pContact);
	
    if (!pContact->GetSock()->Open(HostName))
	{
                            // error on open
		CNetSocket* pSock = pContact->GetSock();
		pContact->SetSock(NULL);

		MessageBox("Al momento non è possibile connettersi con l'host desiderato. Riprovare la connessione in altro momento",
			"Connessione fallita", MB_OK|MB_ICONWARNING);

        RemoveContact(pContact);
        delete pSock; // delete sock also delete contact
	}
	else
	{
                            // update the host name in the listbox
        m_pCallerDlg->ShowContactOnline(pContact, true);
        buildList();
	}
	return pContact;
}



////////////////////////////////////////
//       isMyIp
/*! Check if the Ip is the same to the local ip
// \param IP Ip : ip to check
*/
bool NetGameStartDlg::isMyIp(IP Ip)
{
	int i;
	for (i = 1; i < m_iNICCount; i++)
	{
		tSTRUCTNICINFO *Info = &m_pNICInfo[i - 1];
		if (Ip == IP(Info->IP[0], Info->IP[1], Info->IP[2], Info->IP[3]))
			return true;
	}
	return false;
}

////////////////////////////////////////
//       OnNewNameRemote
/*! A conctact name is updated
// \param WPARAM wParam : 
// \param LPARAM lParam : new name
*/
LRESULT NetGameStartDlg::OnNewNameRemote(WPARAM wParam, LPARAM lParam)
{
    
    buildList();

    return 0;
}


////////////////////////////////////////
//       NotifyOthers
/*! 
*/
void NetGameStartDlg::NotifyOthers()
{
	m_pNotify = new CNotifyThread;
	m_pNotify->pList = &m_ListCont;
    m_pNotify->view = this;
	m_pNotify->CreateThread();
}


////////////////////////////////////////
//       OnTimer
/*! 
// \param UINT nIDEvent : 
*/
void NetGameStartDlg::OnTimer(UINT nIDEvent) 
{
    switch (nIDEvent)
	{
	    case 1:
		    
		    break;
	    case 2:
		    
		    break;
	}

	CDialog::OnTimer(nIDEvent);
}


////////////////////////////////////////
//       RemoveContact
/*! Remove contact from list box, delete socket, me and thread.
*/
void NetGameStartDlg::RemoveContact( CContact* pContact )
{
    CNetSocket* pSocket = pContact->GetSock(); 
    CContact* pMe = NULL;
    if ( pSocket )
    {
        pMe = pSocket->GetConctactMe();
    }
    if ( pContact->pThread )
    {
        delete pContact->pThread;
        pContact->pThread = NULL;
    }
    if (pSocket)
	{
		pSocket->Close();
                            // deletion of netsocket mean deletion of conctact (see destructor of netsocket)
		delete pSocket;
        pSocket = NULL;
	}
    POSITION pos = m_ListCont.Find(pContact);
    if ( pos )
    {
	    m_ListCont.RemoveAt( pos );
    }

    if (pMe)
    {
        delete pMe;
        pMe = NULL;
    }
    
}

////////////////////////////////////////
//       removeContactFromList
/*! Remove contact only from listBox
// \param CContact* pContact : contact to remove
*/
void NetGameStartDlg::removeContactFromList( CContact* pContact )
{
    POSITION pos = m_ListCont.Find(pContact);
    if ( pos )
    {
	    m_ListCont.RemoveAt( pos );
    }
}

////////////////////////////////////////
//       ShowContactOffline
/*! 
// \param CContact* pContact : 
*/
void NetGameStartDlg::ShowContactOffline(CContact* pContact)
{
    removeContactFromList(pContact);
    buildList();
}


////////////////////////////////////////
//       SocketContactClose
/*! Socket on contact is closed. Remove contact from list.
// \param CContact* pContact : 
*/
void NetGameStartDlg::SocketContactClose(CContact* pContact)
{
    CNetSocket* pSocket = pContact->GetSock(); 
    CContact* pMe = NULL;
    if ( pSocket )
    {
        pMe = pSocket->GetConctactMe();
    }
    if ( pContact->pThread )
    {
        delete pContact->pThread;
        pContact->pThread = NULL;
    }
    
    POSITION pos = m_ListCont.Find(pContact);
    if ( pos )
    {
	    m_ListCont.RemoveAt( pos );
    }

    if (pMe)
    {
        delete pMe;
        pMe = NULL;
    }

    buildList();
}

///// COMMANDS /////////////////

////////////////////////////////////////
//       OnBtStartmazz
/*! Player want to start a new play as mazziere
*/
void NetGameStartDlg::OnBtStartmazz() 
{   

                            // disable connect remote button
    m_btConnectGameRemote.EnableWindow(FALSE);

    animStart();

                            // start listener socket
    m_pListenSocket = new CListenSocket(this);
    if (!m_pListenSocket->Create(CNetSocket::PORT_NUM))
	{
        CString strMsg;
        //strMsg.Format("Unable to bind to port %d, ensure program is not already running", CNetSocket::PORT_NUM); 
        strMsg.Format("Impossibile collegarsi alla porta %d, \nassicurarsi che non ci sia già un server in azione su questa macchina", CNetSocket::PORT_NUM); 
		MessageBox(strMsg, "Errore", MB_OK|MB_ICONSTOP);
        
        animStop();
        
        delete m_pListenSocket;
        m_pListenSocket = NULL;
                            // start is not aviable
        m_btStartServer.EnableWindow(FALSE);
                            // connect is the only aviable now
        m_btConnectGameRemote.EnableWindow(TRUE);
		return;
	}
	m_pListenSocket->Listen();

                            // disable start button
    m_btStartServer.EnableWindow(FALSE);
                            // enable break
    m_btStop.EnableWindow(TRUE);

}


////////////////////////////////////////
//       OnBtBreak
/*! User break listening
*/
void NetGameStartDlg::OnBtBreak() 
{
    m_btStop.EnableWindow(FALSE);
    m_btStartServer.EnableWindow(TRUE);

    if ( m_ListCont.GetCount() == 0 )
    {
        m_btConnectGameRemote.EnableWindow(TRUE);
    }

                            // destroy the listener
    if (m_pListenSocket)
    {
        delete m_pListenSocket;
        m_pListenSocket = NULL;
    }

    animStop();

}


////////////////////////////////////////
//       OnBtChat
/*! Player want to chat with a remote player
*/
void NetGameStartDlg::OnBtChat() 
{
	int iNumItems = m_lstbPlayer.GetCount();
    POSITION pos = m_ListCont.GetHeadPosition();

    for (int i = 0; i < iNumItems && pos; i++)
    {
        CContact *pContact = m_ListCont.GetNext(pos); 
        if ( m_lstbPlayer.GetSel(i) > 0 )
        {
                            // item is selected
            ASSERT(m_pCallerDlg);
                            // start a chat
            m_pCallerDlg->NewConversation(pContact, NULL);
            break;
        }
    }
}


////////////////////////////////////////
//       OnBtConnremote
/*! Connect to remote mazziere
*/
void NetGameStartDlg::OnBtConnremote() 
{
    char pHost[64];

    m_ipRemoteMazziere.GetWindowText(pHost, 64);
    
    IP Ip(pHost);
    
	addContact(IP(pHost));

    m_ipRemoteMazziere.GetAddress(m_byIP_1, m_byIP_2, m_byIP_3, m_byIP_4);
	
}

////////////////////////////////////////
//       OnBtLeavenet
/*! User go offline
*/
void NetGameStartDlg::OnBtLeavenet() 
{
    POSITION pos;
   	pos = m_ListCont.GetHeadPosition();
   	while (pos)
	{
		CContact* pContact = m_ListCont.GetNext(pos);
        pContact->ShowOffline();
        
        RemoveContact(pContact);
        
	}
    buildList();

                            // set opponent as local
    m_pCallerDlg->SetOpponent(CClient_jpgDlg::CPU_LOCAL); 
}



////////////////////////////////////////
//       OnBtPlaywith
/*! Invite selected remote player to start a game
*/
void NetGameStartDlg::OnBtPlaywith() 
{
	int iNumItems = m_lstbPlayer.GetCount();
    POSITION pos = m_ListCont.GetHeadPosition();

    for (int i = 0; i < iNumItems && pos; i++)
    {
        CContact* pContact = m_ListCont.GetNext(pos); 
        if ( m_lstbPlayer.GetSel(i) > 0 )
        {
                            // item is selected
            if(m_pCallerDlg)
            {
                            // Invite contact for a new play
                CNetSocket* pSock =  pContact->GetSock(); 
                if ( pSock )
                {
                    CContact* pMe = pSock->GetConctactMe(); 
                    if ( pMe )
                    {
                        m_pCallerDlg->InviteToPlay(pContact, pMe->GetScreenName());
                    }
                }
            }
            break;
        }
    }
}



////////////////////////////////////////
//       BeginNetMatchAsClient
/*! Local player has accept to play with a remote mazziere. Close the dialog and wait for the cards.
*/
void    NetGameStartDlg::BeginNetMatchAsClient()
{
    m_pCallerDlg->SetMazzoServer(FALSE);
    EndDialog(ID_DONOTHING);
}


////////////////////////////////////////
//       BeginNetMatchAsServer
/*! Local player has inveted a remote player to start a match. He has accepts the match. Now local
// have to start a match as mazziere. Dialog is ended.
*/
void    NetGameStartDlg::BeginNetMatchAsServer()
{
    EndDialog(ID_DONOTHING);
    m_pCallerDlg->SetMazzoServer(TRUE);
}

void NetGameStartDlg::OnOK() 
{
    m_ipRemoteMazziere.GetAddress(m_byIP_1, m_byIP_2, m_byIP_3, m_byIP_4);
	
	CDialog::OnOK();
}
