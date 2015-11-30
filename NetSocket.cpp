// NetSocket.cpp : implementation file
//

#include "stdafx.h"

#include "Client_jpg.h"
#include "Contact.h"
//#include "Netmsg.h"
#include "NetSocket.h"
//#include "ContactView.h"
#include "Conversation.h"
#include "ConversationThread.h"
//#include "SoundThread.h"
//#include "FileSend.h"
#include "NetGameStartDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//The class for contact sockets

CNetSocket::CNetSocket()
{
	m_nTimeOut = 100;
	m_pContact = NULL;
    m_pConctMe = NULL;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
    m_bRemoteWasTyping = FALSE;
}

CNetSocket::CNetSocket(CContact *contact)
{
	m_nTimeOut = 100;
	m_pContact = contact;
    m_pConctMe = NULL;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
    m_bRemoteWasTyping = FALSE;
}
CNetSocket::~CNetSocket()
{
	if (m_pArchiveOut != NULL)
	{
		m_pArchiveOut->Abort();
		delete m_pArchiveOut;
		m_pArchiveOut = NULL;
	}
	if (m_pArchiveOut != NULL)
		delete m_pArchiveOut;

	if (m_pArchiveIn != NULL)
		delete m_pArchiveIn;

	if (m_pFile != NULL)
		delete m_pFile;

    ::SendMessage(m_pContact->pPlayApp->GetSafeHwnd(), WM_DESTROYCONTACT, 
                                           (WPARAM)0, (LPARAM)m_pContact);
    Sleep(500);
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CNetSocket, CSocket)
	//{{AFX_MSG_MAP(CNetSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CNetSocket member functions


void CNetSocket::OnClose(int nErrorCode) 
{
	CSocket::OnClose(nErrorCode);
	m_pContact->SignOffline();
    
    // destroy this from DialogApp
    ::SendMessage(m_pContact->pPlayApp->GetSafeHwnd(), WM_DESTROYSOCK, 
                                           (WPARAM)0, (LPARAM)this);
    
    
}

void CNetSocket::Init()
{
	m_pFile = new CSocketFile(this);
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);
}


////////////////////////////////////////
//       OnReceive
/*! Notification of something was received
// \param int nErrorCode : 
*/
void CNetSocket::OnReceive(int nErrorCode) 
{
	CSocket::OnReceive(nErrorCode);
	TRY
	{
		do
		{
			CString tmp;
			m_pArchiveIn->ReadString(tmp);
                            //exams received buffer
			BOOL bDestroyed = Process(tmp);
			if (bDestroyed)
				return;

			if (!m_pContact->GetSock())
				return; //this class was destroyed while we were processing, get out.
		}
		while (!m_pArchiveIn->IsBufferEmpty());
	}
	CATCH(CFileException, e)
	{
		m_pArchiveOut->Abort();
		return;
	}
	END_CATCH
}


////////////////////////////////////////
//       SendString
/*! Send a string
// \param char *fmt : command
// \param ... : arguments
*/
void CNetSocket::SendString(char *fmt, ...)
{
	CString Sends;
	va_list args;
	va_start(args, fmt);
	Sends.FormatV(fmt, args);
	Sends += "\n";
	TRY
	{
		m_pArchiveOut->WriteString(Sends);
		m_pArchiveOut->Flush();
	}
	CATCH (CFileException, e)
	{
		m_pArchiveOut->Abort();
		//abort
		return;
	}
	END_CATCH
}

void CNetSocket::SendStringV(char *fmt, va_list args)
{
	CString Sends;
	Sends.FormatV(fmt, args);
	Sends += "\n";
	TRY
	{
		m_pArchiveOut->WriteString(Sends);
		m_pArchiveOut->Flush();
	}
	CATCH (CFileException, e)
	{
		m_pArchiveOut->Abort();
		//abort
		return;
	}
	END_CATCH
}


////////////////////////////////////////
//       Open
/*! Open the socket
// \param IP Dest : IP destination 
*/
bool CNetSocket::Open(IP Dest)
{
	if (!Create())
        return false;

	if (!Connect(Dest.Get(), PORT_NUM))
        return false;

	m_pFile = new CSocketFile(this);

	m_pContact->WeConnected = true;
    ASSERT( m_pArchiveIn == NULL);

	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);

    if (!(m_pContact->Flags & CContact::CFL_BLOCKED))
	{
		SendString("NAME %s", m_pConctMe->GetScreenName() );
	}
	else
	{
		SendString("OFFLINE");
	}
	return true;
}


////////////////////////////////////////
//       Process
/*! Process received data
// \param CString data : data string to process
*/
BOOL CNetSocket::Process(CString data)
{
	CHAR Data[2128];
    CHAR Process[64];
    CHAR Message[2048];
	BOOL bRet = FALSE;

    ASSERT(m_pContact);

	strcpy_s(Data, data);
    // the first token in the data is the process item (always with a blank separated)
	strcpy_s(Process, strtok(Data, " "));
	
    char *pMsg = strtok(NULL, "");
	if (pMsg)
    {
        strcpy_s(Message, pMsg);
    }
	else
    {
        strcpy_s(Message, "");
    }

	if (!strcmp(Process, "NAME"))
	{
		m_pContact->SetScreenName(Message);
		//m_pContact->ContactView->BuildList();
                            // informs that now a name is aviable
        ::SendMessage(m_pContact->pDlgList->GetSafeHwnd(), WM_REMOTENAMENEW, 0, 0);

        if (m_pContact->Flags & CContact::CFL_ONLINE) 
            return bRet;

		if (m_pContact->Flags & CContact::CFL_AUTHENTICATE_NO)
		{
			m_pContact->Flags &= ~CContact::CFL_AUTHENTICATE_NO;
            /* // ISS: i think in Briscola don't need authentication. If so remove comment follow.
			CHAR buf[512];
			sprintf(buf, "A connection from %s was recieved, is not in your contact list, do you wish to add it? If not the contact will remain on your list blocked.", m_pContact->GetHostName().Get());
			
            if ( MessageBox(NULL, buf, 
				 "New Contact", MB_YESNO|MB_ICONQUESTION) == IDYES)
			{
				if (!m_pContact->GetSock())
                    return;
			}
			else
			{
				if (!m_pContact->GetSock()) 
                    return;
				m_pContact->Flags |= CContact::CFL_BLOCKED;
			}
            */
			if (!(m_pContact->Flags & CContact::CFL_BLOCKED))
			{
				SendString("NAME %s", m_pConctMe->GetScreenName());
			}
		}
		m_pContact->ShowOnline();
	}
	else if (!strcmp(Process, "OFFLINE"))
	{
		m_pContact->WeConnected = false;
        if (m_pContact->Flags & CContact::CFL_OFFLINE) 
            return FALSE;
		
        m_pContact->ShowOffline();
		bRet = TRUE;
		
	}
	else if (!strcmp(Process, "MESSAGE"))
	{
        if (m_pContact->Flags & CContact::CFL_ACTIVE)
		{
			CString cstr = Message;
			cstr.Replace("<%10>", "\r\n");
			m_pContact->pThread->pConv->AppendWindowTextF("< %s >: %s\r\n", m_pContact->GetScreenName(), cstr);
			m_pContact->pThread->pConv->FlashWindow(TRUE);
		}
		else
		{
            TRACE(Message);
                            // remote has sent a message and a 'conversation' is not active: create it
            m_pConctMe->pPlayApp->NewConversation(m_pContact, Message);

			//CSoundThread *SoundThread = new CSoundThread(2);
			//SoundThread->CreateThread();
		}
	}
	else if (!strcmp(Process, "TYPING"))
	{
        if ( (m_pContact->Flags & CContact::CFL_ACTIVE) && !m_bRemoteWasTyping)
		{
			CHAR buf[512];
			sprintf_s(buf, "%s sta scrivendo un messaggio", m_pContact->GetTruncatedScreenName(30));
			m_pContact->pThread->pConv->m_statusBar.SetWindowText(buf);
            m_bRemoteWasTyping = TRUE;
		}
	}
	else if (!strcmp(Process, "NOTTYPING"))
	{
        if ( (m_pContact->Flags & CContact::CFL_ACTIVE) && m_bRemoteWasTyping)
		{
			m_pContact->pThread->pConv->m_statusBar.SetWindowText("");
            m_bRemoteWasTyping = FALSE;
		}
	}
    else if (!strcmp(Process, "PING"))
    {
                            // i am yet here
    }
    // messages for playing briscola
    else if (!strcmp(Process, "PLAY_INVITE"))
    {
        inviteProcess(Message);
    }
    else if (!strcmp(Process, "PLAY_RESP"))
    {
        responceProcess(Message);
    }
    else if (!strcmp(Process, "MAZZO"))
    {
        mazzoProcess(Message);
    }
    else if (!strcmp(Process, "WHOHAVESTART"))
    {
        whostartProcess(Message);
    }
    else if (!strcmp(Process, "CARD_PLAYED"))
    {
        cardplayedProcess(Message);
    }
    else if (!strcmp(Process, "ABORT_SEGNO"))
    {
        abortsegnoProcess(Message);
    }
    else if (!strcmp(Process, "NEW_NAME_PLAYER"))
    {
        newnameplayerProcess(Message);
    }
	else
    {
        //message unknown
        ASSERT(0);
    }
	return bRet;
}


////////////////////////////////////////
//       newnameplayerProcess
/*! Opponent has changed his name
// \param LPCTSTR Message : new name
*/
void CNetSocket::newnameplayerProcess(LPCTSTR Message)
{
    CString strOldName;
    CString strNewName;
    strOldName = Message;
    
    int iComma = strOldName.ReverseFind(','); 
    int iLen = strOldName.GetLength(); 
    strNewName = strOldName.Left(iComma); 
    strOldName = strOldName.Right(iLen - iComma - 1); 

    m_pContact->pPlayApp->NewNameOpponent(strNewName, strOldName);
}

////////////////////////////////////////
//       abortsegnoProcess
/*! Opponet has sent segno abort
// \param LPCTSTR Message : name of opponent
*/
void CNetSocket::abortsegnoProcess(LPCTSTR Message)
{
    m_pContact->pPlayApp->OpponentAbortPlay(Message);
}

////////////////////////////////////////
//       cardplayedProcess
/*! Remote send the card on hand  that have played
// \param LPCTSTR Message : card hand index
*/
void CNetSocket::cardplayedProcess(LPCTSTR Message)
{
    long lIndex;
    sscanf_s(Message, "%d", &lIndex);
    m_pContact->pPlayApp->OpponentPlay(lIndex);
}

////////////////////////////////////////
//       whostartProcess
/*! Remote send who have to start the game
// \param LPCTSTR Message : index of player that must start (already correct, don't need inversion)
*/
void CNetSocket::whostartProcess(LPCTSTR Message)
{
    long lIndex;
    sscanf_s(Message, "%d", &lIndex);
    m_pContact->pPlayApp->SetWhoFirstStart(lIndex);
}

////////////////////////////////////////
//       mazzoProcess
/*! Remote send the mazzo. Mazzo is in message comma separeted
// \param LPCTSTR Message : mazzo on message 
*/
void CNetSocket::mazzoProcess(LPCTSTR Message)
{
    VCT_LONG vct_Temp;
    long lVal = 0;
    int iCount = 0;

    char seps[]   = ",\t\n";
    char* pToken = strtok( const_cast<char*>(Message), seps );
    while ( pToken != NULL )
    {
        sscanf(pToken, "%d", &lVal);
        if ( iCount > 42 )
        {
                            // mazzo sent is not correct
            ASSERT(0);
            break;
        }
        iCount++;
        vct_Temp.push_back(lVal);
        
        pToken = strtok( NULL, seps );
    }
    m_pContact->pPlayApp->InitPlayWithMazzo(vct_Temp);
}

////////////////////////////////////////
//       inviteProcess
/*! Remote send  an invite to play a new match
*/
void CNetSocket::inviteProcess(LPCTSTR Message)
{
    if ( m_pConctMe->ePlayStatus != CContact::CON_NOTHING)
    {
                        // me is already playing, don't accept a new match
        m_pContact->ePlayStatus = CContact::CON_NOTHING;
        SendString("PLAY_RESP %s", "NOPLAY");
        return;
    }
    
    CString strMsg;
    strMsg.Format("%s vuole iniziare una partita a briscola (%s), accetti la sfida?", m_pContact->GetScreenName(), Message  );
    if ( MessageBox(NULL, strMsg, 
			 "Nuova partita", MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
        m_pContact->ePlayStatus = CContact::CON_WAITRESP_MAZZO;
        
                        // set Me as client
        if ( m_pContact->pDlgList )
        {
            m_pContact->pDlgList->BeginNetMatchAsClient();
        }
        m_pContact->pPlayApp->SetMazzoServer(FALSE);
        m_pContact->pPlayApp->BreakAGame();
        
        strMsg = Message;
         
        if ( !strMsg.Compare("scoperta"))
        {
            m_pContact->pPlayApp->SetTypeOfGame(TRUE);
        }
        else
        {
            m_pContact->pPlayApp->SetTypeOfGame(FALSE);
        }
                        // begin a new net game
        m_pContact->pPlayApp->StartNetGame(m_pContact); 

        SendString("PLAY_RESP %s", "OK");
    }
    else
    {
        m_pContact->ePlayStatus = CContact::CON_NOTHING;
        SendString("PLAY_RESP %s", "NOPLAY");
    }
}


////////////////////////////////////////
//       responceProcess
/*! Process a responce from contact
*/
void CNetSocket::responceProcess(LPCTSTR Message)
{
    if ( (m_pContact->ePlayStatus == CContact::CON_WAITRESP_INVITE))
    {
        if (!strcmp(Message, "OK"))
        {
                            // contact have accept to play a new game
            m_pContact->ePlayStatus = CContact::CON_BEGIN_NEWGAME;
            
                            // set Me as mazziere
            if ( m_pContact->pDlgList )
            {
                m_pContact->pDlgList->BeginNetMatchAsServer();
            }
            
            m_pContact->pPlayApp->SetMazzoServer(TRUE);
            
                            // begin a new net game
            m_pContact->pPlayApp->StartNetGame(m_pContact); 
        }
        else
        {
            m_pContact->ePlayStatus = CContact::CON_NOTHING;
            CString strMsg;
            strMsg.Format("%s non ha accettato la sfida!", m_pContact->GetScreenName() );
            MessageBox(NULL, strMsg, "Sfida non accettata", MB_OK|MB_ICONINFORMATION);
        }
    }
}

void CNetSocket::OnConnect(int nErrorCode) 
{
	
	CSocket::OnConnect(nErrorCode);
}

void CNetSocket::OnAccept(int nErrorCode) 
{
	
	CSocket::OnAccept(nErrorCode);
}
