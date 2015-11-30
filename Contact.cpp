//Contacts

#include "stdafx.h"
#include "Client_jpg.h"
#include "NetSocket.h"
#include "Contact.h"
#include "NetGameStartDlg.h "



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



////////////////////////////////////////
//       CContact
/*! Constructor
*/
CContact::CContact()
{
	Flags = CFL_OFFLINE;
	pThread = NULL;
	Attempted = false;
	m_pClientSocket = NULL;
    WeConnected = false;
    ListItem = 0;
    m_HostName.Set("0.0.0.0"); 
    m_strScreenName = "NoBody";
    pPlayApp = NULL;
    pDlgList = NULL;
    ePlayStatus = CON_NOTHING;
}

CContact::~CContact()
{

}

void CContact::SetScreenName(char *NewName)
{
	m_strScreenName = NewName;
}

CString CContact::GetScreenName()
{
	return m_strScreenName;
}

CString CContact::GetTruncatedScreenName(int len)
{
	if (m_strScreenName.GetLength() < len) 
        return m_strScreenName;
	
    CString tmp;
	tmp = m_strScreenName.Left(len);
	tmp += "...";
	return tmp;
}

IP CContact::GetHostName()
{
	return m_HostName;
}

void CContact::SetHost(IP host)
{
	m_HostName = host;
}

void CContact::SetSock(CNetSocket *Socket)
{
	m_pClientSocket = Socket;
}

CNetSocket* CContact::GetSock()
{
	return m_pClientSocket;
}


////////////////////////////////////////
//       SignOffline
/*! Socket is closed, inform GUI to eliminate contact from list and eventually chat dialogs
*/
void CContact::SignOffline()
{
   
    if (pPlayApp)
    {
        pPlayApp->SocketContactClose(this);
    }

    if (pDlgList)
    {
        pDlgList->SocketContactClose(this);
    }
   
}


////////////////////////////////////////
//       ShowOnline
/*! The conctact is going online
*/
void CContact::ShowOnline()
{
    if(pPlayApp)
    {
        pPlayApp->ShowContactOnline( this, true);
    }
}


////////////////////////////////////////
//       ShowOffline
/*! conctact goes offline
*/
void CContact::ShowOffline()
{
    Flags |= CContact::CFL_OFFLINE;
	Flags &= ~CContact::CFL_ONLINE;
	
    if(pPlayApp)
    {
        pPlayApp->ShowContactOffline(this);
    }
    if (pDlgList)
    {
        pDlgList->ShowContactOffline(this);
    }
}