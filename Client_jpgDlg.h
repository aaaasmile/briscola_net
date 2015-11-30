// Client_jpgDlg.h : header file
//

#if !defined(AFX_CLIENT_JPGDLG_H__04157D26_4F55_11D5_A3F9_0004760ECF99__INCLUDED_)
#define AFX_CLIENT_JPGDLG_H__04157D26_4F55_11D5_A3F9_0004760ECF99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cBriscolaGame.h"


#include "BitmapDialog.h"
#include "cGraphicEngine.h"
#include "GameOptions.h"

class CContact;

typedef CList<CContact *, CContact *> LIST_CONTACT;


/////////////////////////////////////////////////////////////////////////////
// CClient_jpgDlg dialog

class CClient_jpgDlg : public CBitmapDialog
{
public:
    //! enum used for type of opponent
    enum eOpponentStatus
    {
        CPU_LOCAL = 1,
        REMOTE = 2,
        HUMAN_LOCAL = 3
    };

public:
	//! carte del giocatore 1
    axcardBriscola	m_AxMyCard1;
    axcardBriscola	m_AxMyCard2;
    axcardBriscola	m_AxMyCard3;
    //! carte dell'avversario
    axcardBriscola	m_AxOpponent1;
    axcardBriscola	m_AxOpponent2;
    axcardBriscola	m_AxOpponent3;
    //! mazzo
    axcardBriscola	m_AxMazzoDeck;
    //! carta giocata per prima
    axcardBriscola	m_AxFirstPlayed;
    //! carta giocata per seconda
    axcardBriscola	m_AxSecondPlayed;
    //! carta in tavola
	axcardBriscola	m_AXintavola;
    //! prese giocatore 1
    axcardBriscola	m_AxMyDeck;
    //! prese avversario
    axcardBriscola	m_AxOpponentDeck;
	//! graphic engine responsible to draw all cards
	cGraphicEngine  m_graEngine;

	//! name Me
	CStatic         m_lblNameMe;
	//! name Opponent
	CStatic         m_lblNameOpp;
   
// Constructor
public:
	CClient_jpgDlg(CWnd* pParent = NULL);	// standard constructor

    //! start a new chat
    void    NewConversation(CContact* With, char* pDefaultMsg);
    //! show contact being go online
    void    ShowContactOnline(CContact* pContact, bool bShowpopup);
    //! show contact going offline
    void    ShowContactOffline(CContact* pContact);
    //! request of socket
    void    ClaimSock(SOCKET Sock, CContact* pContact);
    //! socket is closed
    void    SocketContactClose(CContact* pContact);
    //! set player name
    void    SetPlayerName(LPCTSTR  pVal);
    //! invite a contact to play
    void    InviteToPlay(CContact* pWith, LPCTSTR pDefaultMsg);
    //! begin the game
    void    StartNetGame(CContact* pWith);
    //! set opponent
    void    SetOpponent(eOpponentStatus eVal){m_eOpponent = eVal;}
    //! server flag
    void    SetMazzoServer(BOOL bVal){m_bIamServer=bVal;}
    //! flag type of game (scoperta or normale)
    void    SetTypeOfGame(BOOL bVal);
    //! remote send mazzo for starting a new game
    void    InitPlayWithMazzo(VCT_LONG &vct_Temp);
    //! remote send who must start
    void    SetWhoFirstStart(int iIndex);
    //! interrupt a match 
    void    BreakAGame();
    //! remote has played a card
    void    OpponentPlay(long lPosHand);
    //! remote has aborted the segno
    void    OpponentAbortPlay(LPCTSTR  lpstrName );
    //! remote ha changed his name
    void    NewNameOpponent(LPCTSTR  lpstrName,  LPCTSTR lpstrOldName  );

// Dialog Data
	//{{AFX_DATA(CClient_jpgDlg)
	enum { IDD = IDD_CLIENT_JPG_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClient_jpgDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    //! game icon
	HICON               m_hIcon;
    //! game menu
    CMenu               m_menuHead; 
    //! used to put the played card on the first position
    bool                m_bUseFirst;
    //! multply factor of timer to terminate a hand
    static long         stCounter;
    //! pointer to briscola core class
    cBriscolaCore*      m_pBriscolada;
    //! game status
    eBriscolaStatus     m_eGameStaus;
    //! index of player that begin the game
    long                m_PlayerBegin;
    //! used if the player don't use autoterminate
    bool                m_bHandIsTerm;
    //! used to mark if hint is alredy shown
    bool                m_bInfoNotShown;
    //! special guest info
    int                 m_iGuestId;
    //! number of cards on deck
    int                 m_lNumCardOnDeck;
    //! list of all contacts player on network
    LIST_CONTACT        m_ListCont;
    //! destroy flag
    BOOL                m_bIamDestroy;
    //! net dialog box flag if it present on display
    BOOL                m_bDlgNetListShow;
    //! flag dont change the name on initdialog
    BOOL                m_bNoChangeName;
    //! type of opponent
    eOpponentStatus     m_eOpponent;
    //! initial page destroyed flag
    BOOL                m_bSplashDestroyed;
    //! opponent contact
    CContact*           m_pOpponent;
    //! last status
    eBriscolaStatus     m_eLastStatus;
    //! opponent name 
    CString             m_strOppName;
    //! flag for server
    BOOL                m_bIamServer;
    //! flag if network game is in progress
    BOOL                m_bNetGameInProgress;
    //! opponent played card for no synchron state machine
    long                m_lOppPlayed_nosync;
    //! mazzo is recieved
    BOOL                m_bMazzoRecieved;

protected:
// message handler
    LRESULT OnSendMessage(WPARAM wParam, LPARAM lParam);
    LRESULT OnDestroyThread(WPARAM wParam, LPARAM lParam);
    LRESULT OnTypeNotify(WPARAM wParam, LPARAM lParam);
    LRESULT OnBlockThisContact(WPARAM wParam, LPARAM lParam);
    LRESULT OnSockConnect(WPARAM wParam, LPARAM lParam);
    LRESULT OnSockDestroy(WPARAM wParam, LPARAM lParam);
    LRESULT OnContactDestroy(WPARAM wParam, LPARAM lParam);

	// Generated message map functions
#ifdef _TEST_SOCKET
  	afx_msg void OnBtTestcard3();
	afx_msg void OnBtTestcard2();
	afx_msg void OnBtTestcard1();
#endif

	//{{AFX_MSG(CClient_jpgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLMouseClickMycard1();
	afx_msg void OnLMouseClickMycard2();
	afx_msg void OnLMouseClickMycard3();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnNewgame();
	afx_msg void OnContaPtPlayer();
	afx_msg void OnWhatBriscola();
	afx_msg void OnAbout();
	afx_msg void OnOptions();
	afx_msg void OnLMouseClickMazzocop();
	afx_msg void OnBtNetwork();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    afx_msg void  OnPartitaExit();
    afx_msg void  OnAbortSegno();
    afx_msg void  OnHelp();

// helper functions
private:
    BOOL    InitTable(long lPlayerIx);
    BOOL    MainLoop();
    void    TerminateTheGame();
    void    HandIsTerminated();
    void    ShowErrorCondition();
    void    PlayACard(long lIndex);
    void    CpuIsPlaying();
    void    ShowCpuPlay(long lIndex);
    void    blockContact(CContact *pContact, bool bBlock);
    void    removeContact(CContact* pContact);
    void    showMsgBoxUserOffLine(CContact* pContact);
    void    startNewGame( eOpponentStatus eVal );
    void    loopHandTerminated();
    void    loopNewGame();
    void    loopNewSegno();
    void    loopTerminateTheSegno();
    void    loopNewNetGame();
    void    sendMazzoToRemote();
    void    sendWhoHaveToStart();
    void    visualizeCards();
    BOOL    sendCardPlayed(int iIndex);
    void    loopNewNetSegno();
    void    showMsgAsInfo(CString strMsg);
    void    loopPlayer2HaveToPlay();
    void    updateTypeOfName(CString strOldName);
	
    
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT_JPGDLG_H__04157D26_4F55_11D5_A3F9_0004760ECF99__INCLUDED_)
