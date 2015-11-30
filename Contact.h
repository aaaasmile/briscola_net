// Contact.h: interface for the CContact class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTACT_H__804AF4F1_ECC6_4115_9D26_B17214477701__INCLUDED_)
#define AFX_CONTACT_H__804AF4F1_ECC6_4115_9D26_B17214477701__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Client_jpgDlg.h"
#include "Ipclass.h"
#include "NetSocket.h"
#include "ConversationThread.h"

class NetGameStartDlg;




//! class CContact
/*
store information about contact
*/ 
class CContact  
{
public:
    //! status, set in flag
    enum
    {
        CFL_OFFLINE          = 0x01,
        CFL_ONLINE	         = 0x02,
        CFL_AWAY	         = 0x04,
        CFL_AUTHENTICATE_NO  = 0x08, 
        CFL_BLOCKED          = 0x10,
        CFL_ACTIVE           = 0x20
    };

    enum ePLAYSTATUS
    {
        CON_NOTHING,
        CON_WAITRESP_INVITE,
        CON_WAITRESP_MAZZO,
        CON_WAITRESP_CARDPLAYED,
        CON_WAIT_NEWGAME,
        CON_BEGIN_NEWGAME
    };

    //! application pointer
    CClient_jpgDlg*     pPlayApp;
    //! modal dialog for connection
    NetGameStartDlg*    pDlgList;

public:
	CContact();
	virtual     ~CContact();
// Operation
	IP          GetHostName();
	CString     GetScreenName();
	CString     GetTruncatedScreenName(int len);
	void        SetScreenName(char *);
	void        SetHost(IP host);
	CNetSocket* GetSock();
	void        SetSock(CNetSocket *Socket);
    void        SignOffline();
	void        ShowOnline();
	void        ShowOffline();

// Attributes
public:
	long                 Flags;
	int                  ListItem;
	CConversationThread* pThread;
	bool                 Attempted;
	bool                 WeConnected;
    ePLAYSTATUS          ePlayStatus;

//members
private:
    //! ip addres
	IP                  m_HostName;
    //! session socket
	CNetSocket*         m_pClientSocket;
    //! conctact name
	CString             m_strScreenName;
    
};

#endif // !defined(AFX_CONTACT_H__804AF4F1_ECC6_4115_9D26_B17214477701__INCLUDED_)
