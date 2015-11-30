#if !defined(AFX_NETGAMESTARTDLG_H__C031DAE4_634E_11D6_99C3_00E07DAF9723__INCLUDED_)
#define AFX_NETGAMESTARTDLG_H__C031DAE4_634E_11D6_99C3_00E07DAF9723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetGameStartDlg.h : header file
//

#include "MibAccess.h"
#include "Contact.h"

class CListenSocket;
class CClient_jpgDlg;
class CNotifyThread;

/////////////////////////////////////////////////////////////////////////////
// NetGameStartDlg dialog

class NetGameStartDlg : public CDialog
{
// Construction
public:
	NetGameStartDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(NetGameStartDlg)
	enum { IDD = IDD_NETWORKGAME };
	CIPAddressCtrl	m_ipRemoteMazziere;
	CAnimateCtrl	m_aniWait;
	//}}AFX_DATA
    //! button chat
    CButton            m_btChat;
    //! start server
    CButton            m_btStartServer;
    //! stop server
    CButton            m_btStop;
    //! invite to play
    CButton            m_btInvite;
    //! connect to remote server
    CButton            m_btConnectGameRemote;
    //! disconnect
    CButton            m_btDisconnet;
    //! list of connected
    CListBox           m_lstbPlayer;
    //! notify thread (not used)
    CNotifyThread*     m_pNotify;
    //! flag to regognize if a network game
    BOOL               m_bNetGame;
    byte               m_byIP_1;
    byte               m_byIP_2;
    byte               m_byIP_3;
    byte               m_byIP_4;

// Implementation
public:
    void    AcceptSock();
    void    SetCallerDlg(CClient_jpgDlg* pDlg){m_pCallerDlg = pDlg;}
    BOOL    ExportConctactList(LIST_CONTACT*  pList);
    BOOL    ImportConctactList(LIST_CONTACT*  pList);
    void    SetPlayerName(LPCTSTR  pVal){m_strPlayerName = pVal;}
    void    ShowContactOffline(CContact* pContact);
    void    NotifyOthers();
    void    RemoveContact( CContact* pContact );
    void    SocketContactClose(CContact* pContact);
    void    BeginNetMatchAsClient();
    void    BeginNetMatchAsServer();

//helper functions
private:
    void        setOnline(IP HostName, CNetSocket *pClientSocket);
    CContact*   findContact(IP HostName);
    int         animStart();
    int         animStop();
    bool        isMyIp(IP Ip);
    CContact*   addContact(IP HostName);
    void        pickInfoNic();
    void        buildList();
    void        removeContactFromList( CContact* pContact );
    void        disableBecauseOnPlay();

// members
private:
    //! socket that listen when player starts as mazziere
    CListenSocket*    m_pListenSocket;
    //! network me nic information
    tSTRUCTNICINFO*   m_pNICInfo;
    //! nic count
    int               m_iNICCount;
    //! list of all contacts
    LIST_CONTACT      m_ListCont;
    //! caller pointer
    CClient_jpgDlg*   m_pCallerDlg;
    //! player name
    CString           m_strPlayerName;
    //! animation started flag
    BOOL              m_bPlaying;
    //! timer set for reconnection
    BOOL              m_bTimerNotifySet;
   


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NetGameStartDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
    LRESULT OnNewNameRemote(WPARAM wParam, LPARAM lParam);

	// Generated message map functions
	//{{AFX_MSG(NetGameStartDlg)
	afx_msg void OnBtStartmazz();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBtBreak();
	afx_msg void OnBtChat();
	afx_msg void OnBtConnremote();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtLeavenet();
	afx_msg void OnBtPlaywith();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETGAMESTARTDLG_H__C031DAE4_634E_11D6_99C3_00E07DAF9723__INCLUDED_)
