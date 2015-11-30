#if !defined(AFX_NETSOCKET_H__09ED99DB_C8BC_40B0_AF49_8F8D03BDB364__INCLUDED_)
#define AFX_NETSOCKET_H__09ED99DB_C8BC_40B0_AF49_8F8D03BDB364__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetSocket.h : header file
//

//#include "Contact.h"
#include "Ipclass.h"


class CContact;

/////////////////////////////////////////////////////////////////////////////
// CNetSocket command target



class CNetSocket : public CSocket
{
public:
    enum
    {
        //! socket port number
        PORT_NUM = 8400
    };

// Operations
public:
	CNetSocket();
	CNetSocket(CContact *contact);

	virtual ~CNetSocket();
	bool    Open(IP Dest);
	void    SendString(char*, ...);
	void    SendStringV(char* fmt, va_list args);
	void    Init();
    void       SetMeContact(CContact* pCon){m_pConctMe = pCon;}
    CContact*  GetConctactMe(){return m_pConctMe;}
    void       SetRemoteContact(CContact* pCon){m_pContact = pCon;}
    CContact*  GetConctact(){return m_pContact;}

// Overrides
public:

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CNetSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
//! helper functions
	BOOL    Process(CString data);
    void    inviteProcess(LPCTSTR Message);
    void    responceProcess(LPCTSTR Message);
    void    mazzoProcess(LPCTSTR Message);
    void    whostartProcess(LPCTSTR Message);
    void    cardplayedProcess(LPCTSTR Message);
    void    abortsegnoProcess(LPCTSTR Message);
    void    newnameplayerProcess(LPCTSTR Message);

protected:
    //! contac associated with the socket
    CContact*       m_pContact;
    //! Me information contact
    CContact*       m_pConctMe;
	CSocketFile*    m_pFile;
	CArchive*       m_pArchiveIn;
	CArchive*       m_pArchiveOut;
    //! remote was typing
    BOOL            m_bRemoteWasTyping;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSOCKET_H__09ED99DB_C8BC_40B0_AF49_8F8D03BDB364__INCLUDED_)
