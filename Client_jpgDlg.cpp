// Client_jpgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client_jpg.h"
#include "Client_jpgDlg.h"

#include "NetGameStartDlg.h"
#include "ConversationThread.h"
#include "save_utility.h"
#include "InsertName_Dlg.h"
#include "DlgContaYourPoints.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define ID_TIMER_LOOP 45

long CClient_jpgDlg::stCounter = 0;
extern GAME_SETTINGS g_GameSettings;

///////////////////// About dialog box stuff (we want a html site shown)///////////////////////////


//////////////////
// About dialog uses HTML control to display contents.
//
class CAboutDialog : public CDialog 
{
	DECLARE_DYNAMIC(CAboutDialog)
protected:
	CMyHtmlCtrl m_page;
	virtual BOOL OnInitDialog(); 
public:
	CAboutDialog() : CDialog(IDD_ABOUTBOX, NULL) { }
};

IMPLEMENT_DYNAMIC(CAboutDialog, CDialog)

BOOL CAboutDialog::OnInitDialog()
{
	VERIFY(CDialog::OnInitDialog());
	VERIFY(m_page.CreateFromStatic(IDC_HTMLVIEW, this));
	m_page.LoadFromResource(_T("about.htm"));
	return TRUE;
}

////////////////////////////////////////
//       OnAbout
/*! User click on about buttom
*/
void CClient_jpgDlg::OnAbout() 
{
    static CAboutDialog dlg;     // static to remember state of hyperlinks
	dlg.DoModal();				 // run it
}



//////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//   APPLICATION DIALOG
/////////////////////////////////////////////////////////////////////////////
// CClient_jpgDlg dialog

CClient_jpgDlg::CClient_jpgDlg(CWnd* pParent /*=NULL*/)
	: CBitmapDialog(CClient_jpgDlg::IDD, pParent),
      m_eGameStaus(NOT_READY_TO_PLAY),
      m_pBriscolada(NULL)
{
	//{{AFX_DATA_INIT(CClient_jpgDlg)
	
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_bIamDestroy = FALSE;
    m_bDlgNetListShow = FALSE;
    m_bNoChangeName   = FALSE;
    m_eOpponent       = CPU_LOCAL;
    m_bSplashDestroyed  = FALSE;
    m_pOpponent       = NULL;
    m_eLastStatus     = FAULT;
    m_bIamServer      = FALSE;
    m_bNetGameInProgress = FALSE;
    m_lOppPlayed_nosync = -1;
    m_bMazzoRecieved    = FALSE;
}

void CClient_jpgDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClient_jpgDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_ST_NAME_ME, m_lblNameMe);
	DDX_Control(pDX, IDC_ST_NAME_OPP, m_lblNameOpp);
	/*
#ifndef _TEST_SOCKET
    DDX_Control(pDX, IDC_MYCARD1, m_AxMyCard1);
    DDX_Control(pDX, IDC_MYCARD2, m_AxMyCard2);
    DDX_Control(pDX, IDC_MYCARD3, m_AxMyCard3);
    DDX_Control(pDX, IDC_MYCARD_TAKEN, m_AxMyDeck);
    DDX_Control(pDX, IDC_OPPONENT1, m_AxOpponent1);
    DDX_Control(pDX, IDC_OPPONENT2, m_AxOpponent2);
    DDX_Control(pDX, IDC_OPPONENT3, m_AxOpponent3);
    DDX_Control(pDX, IDC_OPPONENT_TAKEN, m_AxOpponentDeck);
    DDX_Control(pDX, IDC_PLAYEDFIRST, m_AxFirstPlayed);
    DDX_Control(pDX, IDC_PLAYEDSECOND, m_AxSecondPlayed);
	DDX_Control(pDX, IDC_CARTAINTAVOLA, m_AXintavola);
    DDX_Control(pDX, IDC_MAZZOCOP, m_AxMazzoDeck);
#endif
	*/
}

BEGIN_MESSAGE_MAP(CClient_jpgDlg, CBitmapDialog)
	//{{AFX_MSG_MAP(CClient_jpgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_NEWGAME, OnNewgame)
	ON_BN_CLICKED(IDC_CONTA_PT_PLAYER, OnContaPtPlayer)
	ON_BN_CLICKED(IDC_WHAT_BRISCOLA, OnWhatBriscola)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_OPTIONS, OnOptions)
	ON_BN_CLICKED(IDC_BT_NETWORK, OnBtNetwork)
    ON_MESSAGE(WM_SENDTHISMESSAGE, OnSendMessage)
    ON_MESSAGE(WM_DESTROYME, OnDestroyThread)
    ON_MESSAGE(WM_TYPENOTIFY, OnTypeNotify)
    ON_MESSAGE(WM_BLOCKTHISCONTACT, OnBlockThisContact)
    ON_MESSAGE(WM_SOCKCONNECT, OnSockConnect)
    ON_MESSAGE(WM_DESTROYSOCK, OnSockDestroy)
    ON_MESSAGE(WM_DESTROYCONTACT, OnContactDestroy)
	//}}AFX_MSG_MAP
    ON_COMMAND (ID_PARTITA_ESCI, OnPartitaExit )
    ON_COMMAND (ID_PARTITA_NUOVA, OnNewgame )
    ON_COMMAND (ID_PARTITA_TRADENTER, OnAbortSegno)
    ON_COMMAND (ID_EXTRA_RETE, OnBtNetwork)
    ON_COMMAND (ID_EXTRA_OPZIONI, OnOptions)
    ON_COMMAND (ID_INFO_BRISCOLANET, OnAbout)
    ON_COMMAND (ID_INFO_HELP, OnHelp)
#ifdef _TEST_SOCKET
	ON_BN_CLICKED(IDC_BT_TESTCARD3, OnBtTestcard3)
	ON_BN_CLICKED(IDC_BT_TESTCARD2, OnBtTestcard2)
	ON_BN_CLICKED(IDC_BT_TESTCARD1, OnBtTestcard1)
#endif

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClient_jpgDlg message handlers


////////////////////////////////////////
//       OnInitDialog
/*! 
*/
BOOL CClient_jpgDlg::OnInitDialog()
{
	CBitmapDialog::OnInitDialog();

    SetBitmap(IDB_BIT_BACKGRD, BITMAP_CENTER);


	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    m_menuHead.LoadMenu(IDR_MENU1);
    SetMenu (&m_menuHead);
    DrawMenuBar ();
	
                            // create core briscola
	m_pBriscolada = new cBriscolaCore(2);
    ASSERT(m_pBriscolada!= NULL);

    int iCase = rand() % 2; 
    if (iCase > 0)
        m_PlayerBegin = PLAYER_ME;
    else
        m_PlayerBegin = PLAYER_OPPONENT;

                            // set all card controls invisibile 
    //allcardsInvisible(); 

                            // set status for the main loop
    m_pBriscolada->GetStatus(&m_eGameStaus);
    
    /*
    long lStatInv = CSW_ST_INVISIBLE;
    m_AxMyDeck.SetCardStatus(&lStatInv);
    m_AxOpponentDeck.SetCardStatus(&lStatInv);
	*/

	
    m_lblNameOpp.SetWindowText("");
    m_lblNameMe.SetWindowText("");

                            // change the name if it wasn't
    if ( g_GameSettings.sPlayerName.Compare("Anonimo") == 0)
    {
        InsertName_Dlg dlg;
        dlg.m_strPlayerName = g_GameSettings.sPlayerName;
        if (dlg.DoModal() == IDOK ) 
        {
            g_GameSettings.sPlayerName = dlg.m_strPlayerName;
        }
    }

                            // check cards decks
	m_graEngine.SetParentWnd(this);
	m_graEngine.Init();
	
	return TRUE;  
}


////////////////////////////////////////
//       SetPlayerName
/*! 
// \param LPCTSTR  pVal : 
*/
void CClient_jpgDlg::SetPlayerName(LPCTSTR  pVal)
{
	g_GameSettings.sPlayerName = pVal; 
	m_bNoChangeName = TRUE;
}


////////////////////////////////////////
//       SetTypeOfGame
/*! 
// \param BOOL bVal : 
*/
void  CClient_jpgDlg::SetTypeOfGame(BOOL bVal)
{
	g_GameSettings.bUnDecked = bVal;
}

////////////////////////////////////////
//       OnPartitaExit
/*! Program exit
*/
void CClient_jpgDlg::OnPartitaExit()
{
    PostMessage (WM_CLOSE, 0, 0);
}



////////////////////////////////////////
//       OnAbortSegno
/*! Resign segno
*/
void CClient_jpgDlg::OnAbortSegno()
{
    if ( m_eGameStaus == GAME_WAIT_FOR_NEWGAME)
        return;

                            // game is in progress: request confirm to the user
    CString strMsg;
    strMsg.Format("Vuoi veramente lasciare il segno a %s?", m_strOppName); 
    int iRes = AfxMessageBox( strMsg, MB_YESNO ); 
    if ( iRes == IDYES )
    { 
        if ( m_bNetGameInProgress )
        {
            TRACE("Send abort segno  \n");
                            // send to the opponent that me has abort the segno
            m_pOpponent->GetSock()->SendString("ABORT_SEGNO %s",g_GameSettings.sPlayerName );

        }
        BOOL bGameTerm = m_pBriscolada->PlayerAbortTheSegno(PLAYER_ME, FALSE); 
        if ( bGameTerm )
        {
            AfxMessageBox("Era il segno decisivo, mi dispiace hai perso la partita");
            m_eGameStaus = GAME_WAIT_FOR_NEWGAME;
        }
        else
        {
            m_pBriscolada->GetStatus( &m_eGameStaus ); 
        }

        
    }
}


////////////////////////////////////////
//       OnHelp
/*! Show Help file
*/
void CClient_jpgDlg::OnHelp()
{
    WinHelp(0,HELP_CONTENTS);
}




////////////////////////////////////////
//       OnSysCommand
/*! 
// \param UINT nID : 
// \param LPARAM lParam : 
*/
void CClient_jpgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		OnAbout();
	}
	else
	{
		CBitmapDialog::OnSysCommand(nID, lParam);
	}
}



////////////////////////////////////////
//       OnPaint
/*! 
*/
void CClient_jpgDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CBitmapDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClient_jpgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

////////////////////////////////////////
//       OnCreate
/*! Dilago is being creating
// \param LPCREATESTRUCT lpCreateStruct : 
*/
int CClient_jpgDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBitmapDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

    if (g_GameSettings.bAutoTerminate)
    {
        m_bHandIsTerm = true;
    }
    else
    {
        m_bHandIsTerm = false;
    }
    
    // create game timer 
    if (!SetTimer (ID_TIMER_LOOP, 400, NULL)) 
    {
        MessageBox (_T ("Errore in  SetTimer"));
        return -1;
    }

    m_bInfoNotShown = true;

    
	return 0;
}


////////////////////////////////////////
//       OnDestroy
/*! Application is terminating
*/
void CClient_jpgDlg::OnDestroy() 
{
	CBitmapDialog::OnDestroy();

    m_bIamDestroy = TRUE;
	
	if ( m_pBriscolada != NULL)
    {
        delete m_pBriscolada;
        m_pBriscolada = NULL;
    }
    // destry the timer
    KillTimer (ID_TIMER_LOOP);

    
    // clear conctact list
    // there are to delete for each player connected: 
    // contact, contactMe, Conversationthread and netsocket
    POSITION pos;
	pos = m_ListCont.GetHeadPosition();
	while (pos)
	{
		CContact* pContact = m_ListCont.GetNext(pos);
        CContact* pMe = NULL;
		CNetSocket* pSocket = pContact->GetSock();
        
        if ( pContact->pThread )
        {
            ShowContactOffline(pContact);
            delete pContact->pThread;
            pContact->pThread = NULL;
        }
        if (pSocket)
		{
            pMe = pSocket->GetConctactMe();
            delete pMe;

            pContact->SetSock(NULL);
			pSocket->Close();
			delete pSocket ;
            // pcontact is automatically deleted from socket destructor
		}
        else
        {
		    delete pContact;
        }
	}	
}

BEGIN_EVENTSINK_MAP(CClient_jpgDlg, CBitmapDialog)
    //{{AFX_EVENTSINK_MAP(CClient_jpgDlg)
	ON_EVENT(CClient_jpgDlg, 1100, 1 /* LMouseClick */, OnLMouseClickMycard1, VTS_NONE)
	ON_EVENT(CClient_jpgDlg, 1100+1, 1 /* LMouseClick */, OnLMouseClickMycard2, VTS_NONE)
	ON_EVENT(CClient_jpgDlg, 1100+2, 1 /* LMouseClick */, OnLMouseClickMycard3, VTS_NONE)
	ON_EVENT(CClient_jpgDlg, 1100+6, 1 /* LMouseClick */, OnLMouseClickMazzocop, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


////////////////////////////////////////
//       OnLMouseClickMycard1
/*! User click on the first player card
*/
void CClient_jpgDlg::OnLMouseClickMycard1() 
{
    if ( m_eGameStaus == WAITINGPLAYER_TOPLAY)
    {
        m_eGameStaus = NOT_READY_TO_PLAY;
	    tagCARDSHOWSTATUS lStatusId = CSW_ST_EMPTY;
        long lIndex;
        tagCARDSHOWSTATUS lOldStatus = *m_AxMyCard1.GetCardStatus();
        if ( lOldStatus == CSW_ST_EMPTY)
        {
            showMsgAsInfo("Carta già giocata");
            m_eGameStaus = WAITINGPLAYER_TOPLAY;
            return;
        }

                                // current card is empty
        m_AxMyCard1.SetCardStatus(&lStatusId);
        lIndex = m_AxMyCard1.GetCardIndex(); 
	                            // play the card
        m_pBriscolada->CardIsPlayed( PLAYER_ME, 0); 
        PlayACard(lIndex);
        if (m_bNetGameInProgress)
        {
            sendCardPlayed(0);
        }
    }
	
}


////////////////////////////////////////
//       OnLMouseClickMycard2
/*! User click on the second player card
*/
void CClient_jpgDlg::OnLMouseClickMycard2() 
{
	if (m_eGameStaus == WAITINGPLAYER_TOPLAY)
    {
        m_eGameStaus = NOT_READY_TO_PLAY;
	    tagCARDSHOWSTATUS lStatusId = CSW_ST_EMPTY;
        long lIndex;
        tagCARDSHOWSTATUS lOldStatus = *m_AxMyCard2.GetCardStatus();
        if ( lOldStatus == CSW_ST_EMPTY)
        {
            showMsgAsInfo("Carta già giocata");
            m_eGameStaus = WAITINGPLAYER_TOPLAY;
            return;
        }
                                // current card is empty
        m_AxMyCard2.SetCardStatus(&lStatusId);
        lIndex = m_AxMyCard2.GetCardIndex(); 
	                            // play the card
        m_pBriscolada->CardIsPlayed( PLAYER_ME,1); 
        PlayACard(lIndex);
        if (m_bNetGameInProgress)
        {
            sendCardPlayed(1);
        }

    }
	
}


////////////////////////////////////////
//       OnLMouseClickMycard3
/*! User click on the third player card
*/
void CClient_jpgDlg::OnLMouseClickMycard3() 
{
	if (m_eGameStaus == WAITINGPLAYER_TOPLAY)
    {
        m_eGameStaus = NOT_READY_TO_PLAY;
	    tagCARDSHOWSTATUS lStatusId = CSW_ST_EMPTY;
        long lIndex;
        tagCARDSHOWSTATUS lOldStatus = *m_AxMyCard3.GetCardStatus();
        if ( lOldStatus == CSW_ST_EMPTY)
        {
            showMsgAsInfo("Carta già giocata");
            m_eGameStaus = WAITINGPLAYER_TOPLAY;
            return;
        }

                                // current card is empty
        m_AxMyCard3.SetCardStatus(&lStatusId);
        lIndex = m_AxMyCard3.GetCardIndex(); 
	                            // play the card
        m_pBriscolada->CardIsPlayed( PLAYER_ME,2); 
        PlayACard(lIndex);
        if (m_bNetGameInProgress)
        {
            sendCardPlayed(2);
        }
    }
	
}


////////////////////////////////////////
//       PreTranslateMessage
/*! 
// \param MSG* pMsg : 
*/
BOOL CClient_jpgDlg::PreTranslateMessage(MSG* pMsg) 
{
	return CBitmapDialog::PreTranslateMessage(pMsg);
}


////////////////////////////////////////
//       OnTimer
/*! timer handler
// \param UINT nIDEvent : 
*/
void CClient_jpgDlg::OnTimer(UINT nIDEvent) 
{
	
    switch (nIDEvent)
    {
        case ID_TIMER_LOOP:
            MainLoop();
            break;

        default:
            ASSERT(0);

    }

	CBitmapDialog::OnTimer(nIDEvent);
}


////////////////////////////////////////
//       OnNewgame
/*! user click on new game buttom
*/
void CClient_jpgDlg::OnNewgame() 
{
    if ( !m_bSplashDestroyed )
    {
		m_graEngine.DestroySplash(); 
        m_bSplashDestroyed = TRUE;
    }

    if ( m_eGameStaus == GAME_WAIT_FOR_NEWGAME)
    {
        if ( m_bNetGameInProgress )
        {
            m_bMazzoRecieved = FALSE;
            InviteToPlay(m_pOpponent, NULL);
        }
        else
        {
            startNewGame(m_eOpponent);
        }
    }
    else
    {
        if ( m_bNetGameInProgress )
        {
                            // not possible to start a new game if network game is in progress
            CString strMsg;
            strMsg.Format("Una partita in rete con %s è in corso, terminare la partita prima di iniziarne una nuova", m_strOppName);
            AfxMessageBox( strMsg );
        }
        else
        {
                                // game is already running, request confirm to the user
            int iRes = AfxMessageBox( "Vuoi cominciare una nuova partita?", MB_YESNO ); 
            if ( iRes == IDYES )
            {
                startNewGame(m_eOpponent);
            }
        }
    }
}


////////////////////////////////////////
//       OnOptions
/*! User click on options buttom
*/
void CClient_jpgDlg::OnOptions() 
{
	CGameOptions dlgOptions;

	// TO DO: settings

    if ( m_eGameStaus == GAME_WAIT_FOR_NEWGAME)
    {
        dlgOptions.m_bNetGame = FALSE;
    }
    else
    {
        dlgOptions.m_bNetGame = m_bNetGameInProgress;
    }
    
    CString strOldName = g_GameSettings.sPlayerName; 
    if ( dlgOptions.DoModal() == IDOK )
    {
        if (strOldName.Compare( g_GameSettings.sPlayerName ) )
        {
            updateTypeOfName(strOldName);
        }
    }
}


////////////////////////////////////////
//       OnContaPtPlayer
/*! User click on conta buttom
*/
void CClient_jpgDlg::OnContaPtPlayer() 
{
	CString cstrMsg;

    long lPoints;

    m_pBriscolada->GetPlayerScore( PLAYER_ME, &lPoints);

    if ( m_eGameStaus == GAME_WAIT_FOR_NEWGAME)
    {
        long lPointsCpu;
        m_pBriscolada->GetPlayerScore( PLAYER_OPPONENT, &lPointsCpu);
        cstrMsg.Format("Punteggio finale: CPU %d, PLAYER %d ", lPointsCpu, lPoints);

        AfxMessageBox( cstrMsg, MB_ICONINFORMATION); 
    }
    else
    {
        
        
        VCT_LONG vct_CardsTaken;
        m_pBriscolada->GetPlayerCardsTaken(PLAYER_ME, vct_CardsTaken);
        int iNumCardsTaken = vct_CardsTaken.size();
        if ( iNumCardsTaken > 0)
        {
            DlgContaYourPoints Dlg;
            Dlg.SetMazzo(vct_CardsTaken);
            Dlg.SetTotPointsTaken(lPoints);
            Dlg.DoModal(); 
        }
        else
        {
            AfxMessageBox( "Al momento non hai preso nessuna mano", MB_ICONINFORMATION); 
        }
        
        
    }

    
	
}


////////////////////////////////////////
//       OnWhatBriscola
/*! User click on Briscola buttom
*/
void CClient_jpgDlg::OnWhatBriscola() 
{
	CString cstrMsg;

    long lIndex;

    m_pBriscolada->GetCardInTavola( &lIndex);

    tagCARDSHOWSTATUS lStatus = *m_AXintavola.GetCardStatus();

    /*
    if (lStatus != CSW_ST_INVISIBLE)
        cstrMsg = "Problemi di vista? \nComunque ";
    */

    if (lIndex > 0 && lIndex <= 10 )
      cstrMsg += "La briscola è bastoni";
    else if (lIndex > 10 && lIndex <= 20 )
      cstrMsg += "La briscola è denari";
    else if (lIndex > 20 && lIndex <= 30 )
      cstrMsg += "La briscola è spade";
    else if (lIndex > 30 && lIndex <= 40 )
      cstrMsg += "La briscola è coppe";
    else
      cstrMsg += "La briscola è indefinita";

    

    AfxMessageBox( cstrMsg, MB_ICONINFORMATION); 
	
}

////////////////////////////////////////
//       OnLMouseClickMazzocop
/*! User click on mazzo
*/
void CClient_jpgDlg::OnLMouseClickMazzocop() 
{
    if (m_eGameStaus == HAND_TERMINATED)
    {
	    m_bHandIsTerm = true;
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////
//       MainLoop
/*! Main loop game status machine
*/
BOOL CClient_jpgDlg::MainLoop()
{
    switch (m_eGameStaus)
    {
        case NEW_GAME:
            loopNewGame();
            break;

        case NEW_SEGNO:
            loopNewSegno();
            break;

        case NEW_NET_GAME:
            loopNewNetGame();
            break;

        case NEW_NET_SEGNO:
            loopNewNetSegno();
            break;

        case SEGNO_TERMINATED:
            loopTerminateTheSegno();
            break;

        case GAME_TERMINATED:
            TerminateTheGame();
            break;

        case HAND_TERMINATED:
            loopHandTerminated();
            break;

        case WAITING_CPU_TOPLAY:
            CpuIsPlaying();
            break;

        case GAME_WAIT_FOR_NEWGAME:
        case NOT_READY_TO_PLAY:
            // do nothing, wait for status change
            break;

        case WAITINGPLAYER_2_TOPLAY:
            //remote player 2 have to play
            loopPlayer2HaveToPlay();
            break;

        case WAITINGPLAYER_TOPLAY:
            // a user must play, wait for mouse click
            break;

    }
    return true;
}


////////////////////////////////////////
//       loopPlayer2HaveToPlay
/*! Player remote have to play
*/
void  CClient_jpgDlg::loopPlayer2HaveToPlay()
{
    if ( m_lOppPlayed_nosync != -1)
    {
                            // player have already played
        OpponentPlay( m_lOppPlayed_nosync );
        m_lOppPlayed_nosync = -1;
    }
}


////////////////////////////////////////
//       loopHandTerminated
/*! main loop status hand is terminated
*/
void  CClient_jpgDlg::loopHandTerminated()
{
    
    if (stCounter >= g_GameSettings.lDelayTimer && m_bHandIsTerm)
    {
        
        HandIsTerminated();
        stCounter = 0;
    }
    else if (stCounter >= 14 && m_bInfoNotShown)
    {
        m_bInfoNotShown = false;
        stCounter = 3;
        AfxMessageBox( "Clicca sul mazzo per cominciare la nuova mano", MB_ICONINFORMATION);
    }
    stCounter++;

}


////////////////////////////////////////
//       loopNewGame
/*! main loop status new game
*/
void  CClient_jpgDlg::loopNewGame()
{
    TRACE("loopNewGame()\n");
    m_eGameStaus = NOT_READY_TO_PLAY;
    m_bNetGameInProgress = FALSE;

    m_pBriscolada->InitNewMatch();
    loopNewSegno();
}

////////////////////////////////////////
//       loopNewSegno
/*! main loop status new segno
*/
void  CClient_jpgDlg::loopNewSegno()
{
    TRACE("loopNewSegno()\n");
    m_eGameStaus = NOT_READY_TO_PLAY;

    if (m_PlayerBegin == PLAYER_OPPONENT)
    {
        m_PlayerBegin = PLAYER_ME;
    }
    else
    {
        m_PlayerBegin = PLAYER_OPPONENT;
    }

    InitTable(m_PlayerBegin);

}

////////////////////////////////////////
//       PlayACard
/*! A player has played a card
// \param long lIndex : card index
*/
void CClient_jpgDlg::PlayACard(long lIndex)
{
    m_bMazzoRecieved = FALSE;

                        // show the played card
    tagCARDSHOWSTATUS lStatusId = CSW_ST_DRAWNORMAL;
    if (m_bUseFirst)
    {
        m_AxFirstPlayed.SetCardIndex(lIndex); 
        m_AxFirstPlayed.SetCardStatus(&lStatusId);
        m_bUseFirst = false;
    }
    else
    {
        m_AxSecondPlayed.SetCardIndex(lIndex); 
        m_AxSecondPlayed.SetCardStatus(&lStatusId);
        m_bUseFirst = true;
    }

                        // retrive if the game status
    m_pBriscolada->GetStatus(&m_eGameStaus);
    
}


////////////////////////////////////////
//       InitTable
/*! Initialize a new game
*/
BOOL CClient_jpgDlg::InitTable(long lPlayerIx)
{
    ASSERT(m_pBriscolada != NULL);

    m_eGameStaus = NOT_READY_TO_PLAY;

                            // set game level (this should be done in a separate function)
    m_pBriscolada->SetLevel( BEGINNER );

                            // make a new game
    if ( g_GameSettings.bUnDecked )
    {
        m_pBriscolada->InitPlay(lPlayerIx, BRISC_NORMINDUE);
    }
    else
    {
        m_pBriscolada->InitPlay(lPlayerIx, BIRSC_SCOPERTA);
    }

    visualizeCards();

    return TRUE;
}

////////////////////////////////////////
//       visualizeCards
/*! visualize cards on hand
*/
void CClient_jpgDlg::visualizeCards()
{
    tagCARDSHOWSTATUS lNewStatus = CSW_ST_DRAWNORMAL;
    long lIndex = 0;

                            // Opponent
    if ( g_GameSettings.bUnDecked )
    {
                            // game is scoperta
        m_pBriscolada->GetCardInHand( PLAYER_OPPONENT, 0, &lIndex);
        ASSERT(lIndex >= 0);
        m_AxOpponent1.SetCardIndex(lIndex); // setIndex don't update the card
        m_AxOpponent1.SetCardStatus(&lNewStatus); 
        
        m_pBriscolada->GetCardInHand( PLAYER_OPPONENT, 1, &lIndex);
        ASSERT(lIndex >= 0);
        m_AxOpponent2.SetCardIndex(lIndex); 
        m_AxOpponent2.SetCardStatus(&lNewStatus); 
    
        m_pBriscolada->GetCardInHand( PLAYER_OPPONENT, 2, &lIndex);
        ASSERT(lIndex >= 0);
        m_AxOpponent3.SetCardIndex(lIndex); 
        m_AxOpponent3.SetCardStatus(&lNewStatus); 
    }
    else
    {
                            // show deck for the opponent
        m_AxOpponent1.SetCardIndex(DECK_INDEX);
        m_AxOpponent1.SetCardStatus(&lNewStatus); 
        m_AxOpponent2.SetCardIndex(DECK_INDEX);
        m_AxOpponent2.SetCardStatus(&lNewStatus); 
        m_AxOpponent3.SetCardIndex(DECK_INDEX);
        m_AxOpponent3.SetCardStatus(&lNewStatus); 
    }
    
                            // throw the card briscola
    long lIndexInTavola;
    m_pBriscolada->GetCardInTavola(&lIndexInTavola); 
    m_AXintavola.SetCardIndex(lIndexInTavola);
    tagCARDSHOWSTATUS lStatusId = CSW_ST_ROTATE90;
	m_AXintavola.SetCardStatus(&lStatusId);

                            // set player hand
    m_pBriscolada->GetCardInHand( PLAYER_ME, 0, &lIndex);
    ASSERT(lIndex >= 0);
    m_AxMyCard1.SetCardIndex(lIndex); // setIndex don't update the card
    m_AxMyCard1.SetCardStatus(&lNewStatus); 
    ::OutputDebugString("Set card 1\n");
    
    m_pBriscolada->GetCardInHand( PLAYER_ME, 1, &lIndex);
    ASSERT(lIndex >= 0);
    m_AxMyCard2.SetCardIndex(lIndex); 
    m_AxMyCard2.SetCardStatus(&lNewStatus); 
    
    m_pBriscolada->GetCardInHand( PLAYER_ME, 2, &lIndex);
    ASSERT(lIndex >= 0);
    m_AxMyCard3.SetCardIndex(lIndex); 
    m_AxMyCard3.SetCardStatus(&lNewStatus); 

                            // played cards
    lStatusId = CSW_ST_INVISIBLE;
    m_AxFirstPlayed.SetCardStatus(&lStatusId);
    m_AxSecondPlayed.SetCardStatus(&lStatusId);

                            // deck
    lNewStatus = CSW_ST_MAZZO;
    if ( g_GameSettings.bUnDecked )
    {
        bool bRes;
        lIndex = m_pBriscolada->GetIndexNextCard(&bRes);
        m_AxMazzoDeck.SetCardIndex(lIndex);
    }
    else
    {
        m_AxMazzoDeck.SetCardIndex(DECK_INDEX);
    }
    m_AxMazzoDeck.SetCardStatus(&lNewStatus);
    m_lNumCardOnDeck = NUM_DECK_CARD;
    m_AxMazzoDeck.SetNumCardOnDeck(m_lNumCardOnDeck); 
                            // destination of the user played card
    m_bUseFirst = true;

    m_pBriscolada->GetStatus(&m_eGameStaus);

                            // player deck
    tagCARDSHOWSTATUS lStatInv = CSW_ST_INVISIBLE;
    m_AxMyDeck.SetCardStatus(&lStatInv);

                            // cpu deck
    m_AxOpponentDeck.SetCardStatus(&lStatInv);
}

////////////////////////////////////////
//       CpuIsPlaying
/*! The cpu have to play
*/
void CClient_jpgDlg::CpuIsPlaying()
{
    m_eGameStaus = NOT_READY_TO_PLAY;

    bool bRes;
    long lPlayedCardIndex;
    long lPosHand;

                            //get the card
    bRes = m_pBriscolada->PlayACardDad(PLAYER_OPPONENT, &lPlayedCardIndex, &lPosHand);
    if (!bRes)
    {
        ShowErrorCondition();
    }

    ShowCpuPlay(lPosHand);

                            // show the card on table
    PlayACard(lPlayedCardIndex);

}

////////////////////////////////////////
//       OpponentPlay
/*! Opponent play a card
// \param long lPosHand : pos hand played
*/
void CClient_jpgDlg::OpponentPlay(long lPosHand)
{
    if (m_eGameStaus == WAITINGPLAYER_2_TOPLAY)
    {
        ShowCpuPlay(lPosHand);

        long lPlayedCardIndex;
        m_pBriscolada->GetCardInHand(PLAYER_OPPONENT, lPosHand, &lPlayedCardIndex); 

                                // show the card on table and update the status
        m_pBriscolada->CardIsPlayed( PLAYER_OPPONENT, lPosHand);

        PlayACard(lPlayedCardIndex);

    }
    else
    {
        ASSERT(m_lOppPlayed_nosync == -1 );
        m_lOppPlayed_nosync = lPosHand;
    }
}


////////////////////////////////////////
//       NewNameOpponent
/*! Opponent becomes a new name 
// \param LPCTSTR  lpstrName : new name
*/
void CClient_jpgDlg::NewNameOpponent(LPCTSTR  lpstrName, LPCTSTR lpstrOldName )
{
    POSITION pos;
	pos = m_ListCont.GetHeadPosition();
    int iCount = 0;
	while (pos)
	{
		CContact* pContact = m_ListCont.GetNext(pos);
        CString strScreenName = pContact->GetScreenName(); 
        if ( strScreenName.Compare(lpstrOldName) == 0 )
        {
            pContact->SetScreenName(const_cast<char*>(lpstrName)); 
            if ( pContact->pThread)
            {
                CString strNewTitle;
                strNewTitle.Format("Briscola_Net chat con: %s", pContact->GetScreenName());
                pContact->pThread->pConv->SetWindowText(strNewTitle); 
            }
            CString strMsgbx;
            strMsgbx.Format("Il contatto %s ha combiato nome in %s ",lpstrOldName, lpstrName ); 
            AfxMessageBox(strMsgbx);
            break;
        }
     	iCount++;
    }

    if ( m_pOpponent )
    {
        m_strOppName = lpstrName;
        m_lblNameOpp.SetWindowText( lpstrName ); 
        m_pOpponent->SetScreenName(const_cast<char*>(lpstrName)); 

    }
}

////////////////////////////////////////
//       OpponentAbortPlay
/*! The opponent has abort the segno
// \param LPCTSTR  lpstrMsg : name 
*/
void CClient_jpgDlg::OpponentAbortPlay(LPCTSTR  lpstrName )
{
    TRACE("OpponentAbortPlay  \n");
    CString strMsg;

    // set m_pBriscolada aborted
    BOOL bGameTerm = m_pBriscolada->PlayerAbortTheSegno(PLAYER_OPPONENT, m_bMazzoRecieved); 

    strMsg.Format("Opppps...%s ha abbandonato il segno: hai vinto tu la mano!", lpstrName); 
    AfxMessageBox(strMsg);

    
    if ( bGameTerm )
    {
        AfxMessageBox("Era il segno decisivo, congratulazioni hai vinto la partita!!!");
        m_eGameStaus = GAME_WAIT_FOR_NEWGAME;
    }
    else
    {
        m_pBriscolada->GetStatus( &m_eGameStaus ); 
    }

    m_bMazzoRecieved = FALSE;

}


////////////////////////////////////////
//       loopTerminateTheSegno
/*! Termiante the segno
*/
void CClient_jpgDlg::loopTerminateTheSegno()
{
    m_eGameStaus = NOT_READY_TO_PLAY;

    bool bIsDrawn;
    bool bRes;
    long lPlayerIx;
    
    bRes = m_pBriscolada->WhoWinTheGame(&lPlayerIx, &bIsDrawn);
    if (!bRes)
    {
        ShowErrorCondition();
    }

    long lPunt_play;
    long lPunt_cpu;

    m_pBriscolada->GetPlayerScore(PLAYER_OPPONENT, &lPunt_cpu); 
    m_pBriscolada->GetPlayerScore(PLAYER_ME, &lPunt_play); 

    char buff[1024];
    if (bIsDrawn)
    {
        sprintf_s(buff, "Pareggio %s: %d, %s %d", m_strOppName, lPunt_cpu, g_GameSettings.sPlayerName,  lPunt_play );
    }
    else if(lPlayerIx == PLAYER_ME)
    {
        if (g_GameSettings.lGuestId == 0)
        {

            sprintf_s(buff, "Bene hai vinto il segno! %s: %d, %s %d",  m_strOppName, lPunt_cpu, g_GameSettings.sPlayerName, lPunt_play );
        }
    }
    else
    {
        sprintf_s(buff, "Male hai perso il segno! %s: %d, %s %d", m_strOppName, lPunt_cpu, g_GameSettings.sPlayerName, lPunt_play );
    }   

    MessageBox(buff);



    if (m_bNetGameInProgress)
    {
        m_eGameStaus = NEW_NET_SEGNO;
    }
    else
    {
        m_eGameStaus = NEW_SEGNO;
    }
}

////////////////////////////////////////
//       TerminateTheGame
/*! The game is terminated
*/
void CClient_jpgDlg::TerminateTheGame()
{

    m_eGameStaus = NOT_READY_TO_PLAY;

    bool bIsDrawn;
    bool bRes;
    long lPlayerIx;
    
    bRes = m_pBriscolada->WhoWinTheGame(&lPlayerIx, &bIsDrawn);
    if (!bRes)
    {
        ShowErrorCondition();
    }

    long lPunt_play;
    long lPunt_cpu;

    m_pBriscolada->GetSegniScore(PLAYER_OPPONENT, &lPunt_cpu); 
    m_pBriscolada->GetSegniScore(PLAYER_ME, &lPunt_play); 

    char buff[1024];
    if (bIsDrawn)
    {
        // not possible
        ASSERT(0);
    }
    else if(lPlayerIx == PLAYER_ME)
    {
        if (g_GameSettings.lGuestId == 0)
        {

            sprintf_s(buff, "CONGRATULAZIONI hai vinto la partita! %s: %d, %s %d",  m_strOppName, lPunt_cpu, g_GameSettings.sPlayerName, lPunt_play );
        }
        else if (g_GameSettings.lGuestId == 1)
        {
            sprintf_s(buff, "Congratulazioni hai vinto un privè al Gattoazzuro!!!\n %s: %d, %s - Guzzatore %d", m_strOppName, lPunt_cpu, g_GameSettings.sPlayerName, lPunt_play );
        }
    }
    else
    {
        sprintf_s(buff, "Giocatori come te, li mangio a colazione %s: %d, %s %d", m_strOppName, lPunt_cpu, g_GameSettings.sPlayerName, lPunt_play );
    }   

    MessageBox(buff);


    m_eGameStaus = GAME_WAIT_FOR_NEWGAME;
}


////////////////////////////////////////
//       HandIsTerminated
/*! Hand is ternminated, show the cards and make new one
*/
void CClient_jpgDlg::HandIsTerminated()
{
  
    long lIndex;
    tagCARDSHOWSTATUS lStatusNormal = CSW_ST_DRAWNORMAL;
    tagCARDSHOWSTATUS lStatusEmpty = CSW_ST_EMPTY;

    m_eGameStaus = NOT_READY_TO_PLAY;

    if (!g_GameSettings.bAutoTerminate)
    {
                            // wait signal from user before go to the next hand
        m_bHandIsTerm = false;
    }
                            // make played cards invisible
    tagCARDSHOWSTATUS lStatusInv = CSW_ST_INVISIBLE;
    m_AxFirstPlayed.SetCardStatus(&lStatusInv);
    m_AxSecondPlayed.SetCardStatus(&lStatusInv);

                            // start a new hand
    bool bMazzoFull = m_pBriscolada->BeginNewHand();
    if (!bMazzoFull)
    {
                            // no more card on mazzo
        if (!g_GameSettings.bAutoTerminate)
        {
                            // make mazzo empty because the user click on it to terminate the hand
            m_AxMazzoDeck.SetCardStatus(&lStatusEmpty);
        }
        else
        {
                            // make mazzo invisible
            m_AxMazzoDeck.SetCardStatus(&lStatusInv);
        }
        m_AXintavola.SetCardStatus(&lStatusInv);
    }
    else
    {
                            // show the right number of card
        m_lNumCardOnDeck -= 2 ;
        if (m_lNumCardOnDeck > 0)
            m_AxMazzoDeck.SetNumCardOnDeck(m_lNumCardOnDeck); 
    }

    
                            // card on pos 1
    m_pBriscolada->GetCardInHand( PLAYER_ME, 0, &lIndex);
    if (lIndex == NOT_VALID_INDEX)
    {
        m_AxMyCard1.SetCardStatus(&lStatusEmpty); 
        TRACE("Set card 1\n");
    }
    else
    {
        m_AxMyCard1.SetCardIndex(lIndex); // setIndex don't update the card
        m_AxMyCard1.SetCardStatus(&lStatusNormal);
        TRACE("Set card 1\n");
    }
    m_pBriscolada->GetCardInHand( PLAYER_OPPONENT, 0, &lIndex);
    if (lIndex == NOT_VALID_INDEX)
    {
        m_AxOpponent1.SetCardStatus(&lStatusEmpty);
    }
    else
    {
        if ( g_GameSettings.bUnDecked )
        {
            m_AxOpponent1.SetCardIndex(lIndex);
        }
        m_AxOpponent1.SetCardStatus(&lStatusNormal);
    }
    
                            // card on pos 2
    m_pBriscolada->GetCardInHand( PLAYER_ME, 1, &lIndex);
    if (lIndex == NOT_VALID_INDEX)
    {
        m_AxMyCard2.SetCardStatus(&lStatusEmpty); 
    }
    else
    {
        m_AxMyCard2.SetCardIndex(lIndex); 
        m_AxMyCard2.SetCardStatus(&lStatusNormal);
        
    }
    m_pBriscolada->GetCardInHand( PLAYER_OPPONENT, 1, &lIndex);
    if (lIndex == NOT_VALID_INDEX)
    {
        m_AxOpponent2.SetCardStatus(&lStatusEmpty);
    }
    else
    {
        if ( g_GameSettings.bUnDecked )
        {
            m_AxOpponent2.SetCardIndex(lIndex);
        }
        m_AxOpponent2.SetCardStatus(&lStatusNormal);
    }
    
                            // card on pos 3
    m_pBriscolada->GetCardInHand( PLAYER_ME, 2, &lIndex);
    if (lIndex == NOT_VALID_INDEX)
    {
        m_AxMyCard3.SetCardStatus(&lStatusEmpty); 
    }
    else
    {
        m_AxMyCard3.SetCardIndex(lIndex); 
        m_AxMyCard3.SetCardStatus(&lStatusNormal);
    }
    m_pBriscolada->GetCardInHand( PLAYER_OPPONENT, 2, &lIndex);
    if (lIndex == NOT_VALID_INDEX)
    {
        m_AxOpponent3.SetCardStatus(&lStatusEmpty);
    }
    else
    {
        if ( g_GameSettings.bUnDecked )
        {
            m_AxOpponent3.SetCardIndex(lIndex);
        }
        m_AxOpponent3.SetCardStatus(&lStatusNormal);
    }
                            // deck
    if ( g_GameSettings.bUnDecked )
    {
        bool bRes;
        lIndex = m_pBriscolada->GetIndexNextCard(&bRes);
        if (bRes)
            m_AxMazzoDeck.SetCardIndex(lIndex);
    }

                            // get the status for the player that must play
    m_pBriscolada->GetStatus(&m_eGameStaus); 
    
    if (m_eGameStaus == WAITINGPLAYER_TOPLAY)
    {
                            // player take the hand
        tagCARDSHOWSTATUS lStatus;
        lStatus = *m_AxMyDeck.GetCardStatus();
        if ( lStatus == CSW_ST_INVISIBLE)
        {
            lStatus = CSW_ST_MAZZO;
            m_AxMyDeck.SetCardStatus(&lStatus);
            m_AxMyDeck.SetNumCardOnDeck(DECK_INDEX);
        }
        
        m_AxOpponentDeck.SetCardIndex(DECK_INDEX);
        m_AxMyDeck.SetCardIndex(DECK_RED_INDEX);

        long lNumCardTaken = m_AxMyDeck.GetNumCardOnDeck();
        lNumCardTaken += 2;
        m_AxMyDeck.SetNumCardOnDeck(lNumCardTaken);
        
    }
    else if (m_eGameStaus == WAITING_CPU_TOPLAY ||
             m_eGameStaus == WAITINGPLAYER_2_TOPLAY)
    {
                            // cpu take the hand
        tagCARDSHOWSTATUS lStatus;
        lStatus = *m_AxOpponentDeck.GetCardStatus();
        if ( lStatus == CSW_ST_INVISIBLE)
        {
            lStatus = CSW_ST_MAZZO;
            m_AxOpponentDeck.SetCardStatus(&lStatus);
            m_AxOpponentDeck.SetNumCardOnDeck(DECK_INDEX);
        }
        m_AxOpponentDeck.SetCardIndex(DECK_RED_INDEX);
        m_AxMyDeck.SetCardIndex(DECK_INDEX);

        long lNumCardTaken = m_AxOpponentDeck.GetNumCardOnDeck();
        lNumCardTaken += 2;
        m_AxOpponentDeck.SetNumCardOnDeck(lNumCardTaken);
    }
}

////////////////////////////////////////
//       updateTypeOfName
/*! Update the player name to all 
*/
void CClient_jpgDlg::updateTypeOfName(CString strOldName)
{
    POSITION pos;
	pos = m_ListCont.GetHeadPosition();
	while (pos)
	{
		CContact* pContact = m_ListCont.GetNext(pos);
     	CNetSocket* pSocket = pContact->GetSock();

        pSocket->SendString("NEW_NAME_PLAYER %s,%s", g_GameSettings.sPlayerName, strOldName );
        if ( pContact->pThread )
        {
            pContact->pThread->pConv->pMe->SetScreenName(const_cast<char*>((LPCTSTR)g_GameSettings.sPlayerName));   
        }

    }

    if (m_bSplashDestroyed)
    {
        m_lblNameMe.SetWindowText( g_GameSettings.sPlayerName );
        Invalidate(); 
    }

     
}


////////////////////////////////////////
//       ShowCpuPlay
/*! 
*/
void CClient_jpgDlg::ShowCpuPlay(long lIndex)
{
    tagCARDSHOWSTATUS lStatusId = CSW_ST_EMPTY;
    if (lIndex == 0)
    {
                                // current card is empty
        m_AxOpponent1.SetCardStatus(&lStatusId);
    }
    else if (lIndex == 1)
    {
        m_AxOpponent2.SetCardStatus(&lStatusId);
    }
    else if(lIndex == 2)
    {
        m_AxOpponent3.SetCardStatus(&lStatusId);
    }
    else
    {
        ASSERT(0);
    }
}

////////////////////////////////////////
//       ShowErrorCondition
/*! 
*/
void CClient_jpgDlg::ShowErrorCondition()
{
    MessageBox("Errore");
}



/////////////////////////////////////////////////////////////////////////////////////
////////////////////  ******** Network part ***************

////////////////////////////////////////
//       OnBtNetwork
/*! Click on network button
*/
void CClient_jpgDlg::OnBtNetwork() 
{
	NetGameStartDlg Dlg;

    Dlg.SetCallerDlg(this); 
    Dlg.m_bNetGame = m_bNetGameInProgress;

    Dlg.ImportConctactList( &m_ListCont ); 
    Dlg.SetPlayerName(g_GameSettings.sPlayerName); 

    Dlg.m_byIP_1 = g_GameSettings.lIpRemote_1;
    Dlg.m_byIP_2 = g_GameSettings.lIpRemote_2;
    Dlg.m_byIP_3 = g_GameSettings.lIpRemote_3;
    Dlg.m_byIP_4 = g_GameSettings.lIpRemote_4;

    m_bDlgNetListShow = TRUE;
    if (Dlg.DoModal() == IDOK)
    {
        
         g_GameSettings.lIpRemote_1 = Dlg.m_byIP_1 ;
         g_GameSettings.lIpRemote_2 = Dlg.m_byIP_2 ;
         g_GameSettings.lIpRemote_3 = Dlg.m_byIP_3 ;
         g_GameSettings.lIpRemote_4 = Dlg.m_byIP_4 ;
    }
    else
    {
                            // continue the game
    }
    Dlg.ExportConctactList( &m_ListCont );
    m_bDlgNetListShow = FALSE;
}


////////////////////////////////////////
//       NewConversation
/*! Start a new chat session
// \param CContact *With : contact chatter
// \param char *DefaultMsg : default message
*/
void CClient_jpgDlg::NewConversation(CContact* pWith, char* pDefaultMsg)
{
    // pDefaultMsg becomes unaviable before the thread start
    if (pWith->Flags & CContact::CFL_ACTIVE)
	{
		pWith->pThread->pConv->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		pWith->pThread->pConv->SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		return;
	}
	if (pWith->Flags & CContact::CFL_OFFLINE)
	{
		MessageBox("Non puoi mandare messaggi a utenti offline", "Non posso inviare il messaggio", MB_OK|MB_ICONSTOP);
		return;
	}
	CConversationThread *Thread = new CConversationThread(pWith, pDefaultMsg);
	Thread->m_bAutoDelete = FALSE;
	Thread->CreateThread();
    if ( pWith->pThread )
    {
        delete pWith->pThread;
        pWith->pThread = NULL;
    }
	pWith->pThread = Thread;
	pWith->Flags |= CContact::CFL_ACTIVE;
}


////////////////////////////////////////
//       ShowContactOnline
/*! Opponent from remote network is connected
// \param CContact *pContact : remote conctact
// \param bool bShowpopup : flag to show popup
*/
void CClient_jpgDlg::ShowContactOnline(CContact *pContact, bool bShowpopup)
{
    pContact->Flags |= CContact::CFL_ONLINE;
	pContact->Flags &= ~CContact::CFL_OFFLINE;
	if (bShowpopup)
	{
        /* popup at the moment disabled
		CSoundThread *SoundThread = new CSoundThread(1);
		SoundThread->CreateThread();
		CPopWndThread *PopThread = new CPopWndThread(Contact->GetTruncatedScreenName(20));
		PopThread->View = this;
		PopThread->Contact = Contact;
		PopThread->CreateThread();
        */
	}
	if (pContact->Flags & CContact::CFL_ACTIVE)
	{
		pContact->pThread->pConv->m_statusBar.SetWindowText("");
	}
	
}


////////////////////////////////////////
//       OnSendMessage
/*! Conversation dialogbox want sent a chat message 
// \param WPARAM wParam : 
// \param LPARAM lParam : 
*/
LRESULT CClient_jpgDlg::OnSendMessage(WPARAM wParam, LPARAM lParam)
{
	MESSAGE *Msg = (MESSAGE *)lParam;
    if (!Msg->pTo->GetSock() || Msg->pTo->Flags & CContact::CFL_OFFLINE)
	{
		Msg->pCallingDialog->AppendWindowTextF("Il messaggio seguente non può essere inviato:\r\n\"%s\"\r\nIl giocatore è offline.\r\n", Msg->strMessage);
		return 0L;
	}
	Msg->pTo->GetSock()->SendString("MESSAGE %s", Msg->strMessage );
	delete Msg;
	
    return 1L;
}


////////////////////////////////////////
//       OnDestroyThread
/*! Conversation dialogbox has terminated, destroy the thread
// \param WPARAM wParam : 
// \param LPARAM lParam : 
*/
LRESULT CClient_jpgDlg::OnDestroyThread(WPARAM wParam, LPARAM lParam)
{
    if (!m_bIamDestroy)
    {
	    CConversationThread *Thread = (CConversationThread *)lParam;
        Thread->pWith->Flags &= ~CContact::CFL_ACTIVE;
	    Thread->PostThreadMessage(WM_QUIT, 0, 0);
    }
	return 0L;
}


////////////////////////////////////////
//       OnTypeNotify
/*! We have to notify the contact about our typing activity
// \param WPARAM wParam : notification value (0 = not typing, 1 = typing)
// \param LPARAM lParam : pointer to contact
*/
LRESULT CClient_jpgDlg::OnTypeNotify(WPARAM wParam, LPARAM lParam)
{
    CContact* pContact = (CContact *)lParam;
	if (wParam)
    {
        pContact->GetSock()->SendString("TYPING");
    }
	else 
    {
        pContact->GetSock()->SendString("NOTTYPING");
    }
	return 0L;
}

    

////////////////////////////////////////
//       OnBlockThisContact
/*! 
// \param WPARAM wParam : 
// \param LPARAM lParam : 
*/
LRESULT CClient_jpgDlg::OnBlockThisContact(WPARAM wParam, LPARAM lParam)
{
    blockContact((CContact *)lParam, true);

	return 0L;
}


////////////////////////////////////////
//       blockContact
/*! block or unblock the contact sending offline
// \param CContact *Contact : 
// \param bool Block : 
*/
void CClient_jpgDlg::blockContact(CContact* pContact, bool bBlock)
{
	if (bBlock)
	{
        pContact->Flags |= CContact::CFL_BLOCKED;
	}
	else
    {
        pContact->Flags &= ~CContact::CFL_BLOCKED;
    }
	if ( pContact->GetSock() )
	{
		if (bBlock)
        {
			pContact->GetSock()->SendString("OFFLINE");
        }
		else
		{
            CContact* pMe = pContact->GetSock()->GetConctactMe();
            ASSERT(pMe);
			pContact->GetSock()->SendString("NAME %s", pMe->GetScreenName());
		}	
	}
}


////////////////////////////////////////
//       removeContact
/*! 
// \param CContact* pContact : 
*/
void CClient_jpgDlg::removeContact(CContact* pContact)
{
    POSITION pos = m_ListCont.Find(pContact);
    if ( pos )
    {
	    m_ListCont.RemoveAt( pos );
    }
}

////////////////////////////////////////
//       ShowContactOffline
/*! Contact is going offline
// \param CContact* pContact : 
*/
void CClient_jpgDlg::ShowContactOffline(CContact* pContact)
{
    if (pContact->Flags & CContact::CFL_ACTIVE && pContact->pThread)
	{
		pContact->pThread->PostThreadMessage(WM_QUIT, 0, 0);
        showMsgBoxUserOffLine(pContact);
	}
    // remote user can go offline without net dialogbox, 
    // in this case the  contact list must be updated
    if ( !m_bDlgNetListShow )
    {
        removeContact(pContact);
    }
    if ( m_bNetGameInProgress )
    {
        m_eGameStaus = GAME_WAIT_FOR_NEWGAME;
        CString strMsg;
        strMsg.Format("%s è ora offline, la partita è terminata\nPremi il pulsante [nuova partita] per iniziare una nuova partita contro la CPU",m_strOppName); 
        showMsgAsInfo(strMsg);

    }
    m_bNetGameInProgress = FALSE;
    m_eOpponent = CPU_LOCAL;

}

////////////////////////////////////////
//       showMsgBoxUserOffLine
/*! 
// \param CContact* pContact : 
*/
void CClient_jpgDlg::showMsgBoxUserOffLine(CContact* pContact)
{
    CString strMsg;
    CString strName = pContact->GetScreenName(); 
    strMsg.Format("%s non è più connesso  \nla chat con %s è  terminata", strName, strName);
    showMsgAsInfo(strMsg);
}


////////////////////////////////////////
//       showMsgAsInfo
/*! Show a message box
// \param CString strMsg : 
*/
void CClient_jpgDlg::showMsgAsInfo(CString strMsg)
{
    MessageBox(strMsg, "Informazione", MB_OK|MB_ICONINFORMATION);
}

////////////////////////////////////////
//       SocketContactClose
/*! Socket on contact is closed. Stop chat thread
// \param CContact* pContact : 
*/
void CClient_jpgDlg::SocketContactClose(CContact* pContact)
{
    ShowContactOffline(pContact);
}


////////////////////////////////////////
//       OnSockConnect
/*! 
// \param WPARAM wParam : 
// \param LPARAM lParam : 
*/
LRESULT CClient_jpgDlg::OnSockConnect(WPARAM wParam, LPARAM lParam)
{
	ClaimSock((SOCKET)wParam, (CContact *)lParam);
	return 0L;
}


////////////////////////////////////////
//       ClaimSock
/*! 
// \param SOCKET Sock : 
// \param CContact *Contact : 
*/
void CClient_jpgDlg::ClaimSock(SOCKET Sock, CContact *pContact)
{
	CNetSocket *pNewSock = new CNetSocket(pContact);
	pNewSock->Attach(Sock);
	pContact->SetSock(pNewSock);
	pNewSock->Init();
	pContact->Attempted = true;
}


////////////////////////////////////////
//       OnSockDestroy
/*! 
// \param WPARAM wParam : 
// \param LPARAM lParam : 
*/
LRESULT CClient_jpgDlg::OnSockDestroy(WPARAM wParam, LPARAM lParam)
{
	CNetSocket* pNewSock;
    
    pNewSock =  (CNetSocket*)lParam;

    delete pNewSock;

	return 0L;
}


////////////////////////////////////////
//       OnContactDestroy
/*! 
// \param WPARAM wParam : 
// \param LPARAM lParam : 
*/
LRESULT CClient_jpgDlg::OnContactDestroy(WPARAM wParam, LPARAM lParam)
{
    CContact* pContact = (CContact*)lParam;

    delete pContact;

    return 0L;
}


////////////////////////////////////////
//       InviteToPlay
/*! Send invite to play
// \param CContact* pWith : 
// \param LPCTSTR pDefaultMsg : 
*/
void CClient_jpgDlg::InviteToPlay(CContact* pWith, LPCTSTR pDefaultMsg)
{
    if ( pWith != NULL)
    {
        CString strValGame;
        if (g_GameSettings.bUnDecked )
        {
            strValGame = "scoperta";
        }
        else
        {
            strValGame = "normale";
        }
        if ( m_eGameStaus == GAME_WAIT_FOR_NEWGAME )
        {
            pWith->ePlayStatus = CContact::CON_WAITRESP_INVITE;
            pWith->GetSock()->SendString("PLAY_INVITE %s", strValGame);
        }
        else
        {
                            // a match is in progress
            if ( m_eOpponent == REMOTE )
            {
                AfxMessageBox("Una partita in rete è già in corso, prima bisogna abbandonare l'attuale");
            }
            else
            {
                int iRes = AfxMessageBox( "Partita in corso, vuoi cominciare una nuova partita in rete?", MB_YESNO ); 
                if ( iRes == IDYES )
                {
                    m_eGameStaus = GAME_WAIT_FOR_NEWGAME;
                    pWith->ePlayStatus = CContact::CON_WAITRESP_INVITE;
                    pWith->GetSock()->SendString("PLAY_INVITE %s", strValGame);
                }
            }
        }

    }
}

////////////////////////////////////////
//       BreakAGame
/*! 
*/
void CClient_jpgDlg::BreakAGame()
{
    m_eGameStaus = GAME_WAIT_FOR_NEWGAME;
}

////////////////////////////////////////
//       StartNetGame
/*! Begin a new game with remote opponent
// \param CContact* pWith : remote contact
*/
void CClient_jpgDlg::StartNetGame(CContact* pWith)
{
    TRACE("StartNetGame()\n");
    ASSERT ( m_eGameStaus == GAME_WAIT_FOR_NEWGAME);
    m_bNetGameInProgress = TRUE;

    m_pOpponent = pWith;

    m_pBriscolada->InitNewMatch();   
    CString strText;
                        // i am not a server, wait for cards from server

    startNewGame( REMOTE );
}


////////////////////////////////////////
//       startNewGame
/*! Set the status for a new remote segno
*/
void CClient_jpgDlg::startNewGame( eOpponentStatus eVal )
{
    TRACE("startNewGame()\n");
    CString strText;
    m_eGameStaus = NOT_READY_TO_PLAY;

    m_eOpponent = eVal;
    m_lblNameMe.SetWindowText(g_GameSettings.sPlayerName);
    
    if ( eVal == REMOTE)
    {
        m_pBriscolada->SetPlayerRemote( PLAYER_OPPONENT, PT_REMOTE);
        m_pBriscolada->SetNetGameType( REMOTE_NET_TYPE );
        if ( m_pOpponent )
        {
            m_lblNameOpp.SetWindowText(m_pOpponent->GetScreenName());
            m_strOppName = m_pOpponent->GetScreenName();
        }
        else
        {
            // m_pOpponent in network game have to be set
            ASSERT(0);
        }
        loopNewNetGame();        

    }
    else if ( eVal == CPU_LOCAL )
    {
        m_lblNameOpp.SetWindowText("CPU");
        m_strOppName = "CPU";
        m_pBriscolada->SetPlayerRemote( PLAYER_OPPONENT, PT_MACHINE);
        m_pBriscolada->SetNetGameType( CPU_TYPE );

        m_eGameStaus =  NEW_GAME;
    }
    else
    {
        ASSERT(0);
    }
}


////////////////////////////////////////
//       loopNewNetGame
/*! Start a new net match.
*/
void CClient_jpgDlg::loopNewNetGame()
{
    TRACE("loopNewNetGame()\n");
    
    m_pBriscolada->InitNewMatch();
    loopNewNetSegno();
}


////////////////////////////////////////
//       loopNewNetSegno
/*! new net segno
*/
void CClient_jpgDlg::loopNewNetSegno()
{
    TRACE("loopNewNetSegno()\n");
    m_eGameStaus = NOT_READY_TO_PLAY;
    m_bNetGameInProgress = TRUE;

    CString strText;
	                     // destroy the start up control
    if ( !m_bSplashDestroyed )
    {
        m_graEngine.DestroySplash(); 
        m_bSplashDestroyed = TRUE;
    }
    
    if ( m_bIamServer )
    {
        TRACE("i am mazziere\n");
                            // shuffle and distriuite the cards and change the status
        loopNewSegno();

                            // send who have to start
        sendWhoHaveToStart();
                            // send the mazzo to the opponent
        sendMazzoToRemote();
    }
    else
    {
                            // cards can already sent
        TRACE("i am client, wait for cards... \n");
        m_pBriscolada->GetStatus(&m_eGameStaus);        
    }


}


////////////////////////////////////////
//       sendWhoHaveToStart
/*! Send who have to start
*/
void CClient_jpgDlg::sendWhoHaveToStart()
{
    ASSERT(m_pOpponent);
    CString strBuff;

    long lIndex = m_pBriscolada->GetStartPlayerIndex();
                            // for remote we have to invert the index
    if ( lIndex == PLAYER_ME)
    {
        lIndex = PLAYER_OPPONENT;
    }
    else
    {
        lIndex = PLAYER_ME;
    }
    strBuff.Format("%d",lIndex);
    
    m_pOpponent->GetSock()->SendString("WHOHAVESTART %s",strBuff);
}

////////////////////////////////////////
//       sendMazzoToRemote
/*! Send the cards to the opponent
*/
void CClient_jpgDlg::sendMazzoToRemote()
{
    TRACE("sendMazzoToRemote");
    VCT_LONG vct_Temp = m_pBriscolada->GetStartMazzo();
    Utility::TraceContainer(vct_Temp, "Cards to send"); 

    ASSERT(m_pOpponent);
    CString strBuff;
    int  iSize = vct_Temp.size();
    char bufConv[512];
    char bufInt[32];

    ASSERT(iSize == 41 );
    int j = 0;
    bufConv[0] = '\0';
    for (int i = 0; i < iSize; i++)
    {
        itoa(vct_Temp[i], bufInt, 10);
        strcat_s(bufConv, bufInt);
        strcat_s(bufConv, ",");
    }
    
    strBuff += bufConv;
    TRACE("%s\n",strBuff);

    m_pOpponent->GetSock()->SendString("MAZZO %s",strBuff);
}


////////////////////////////////////////
//       InitPlayWithMazzo
/*! Start a play from a remote mazzo
// \param VCT_LONG &vct_Temp : 
*/
void CClient_jpgDlg::InitPlayWithMazzo(VCT_LONG &vct_Temp)
{
    m_eGameStaus = NOT_READY_TO_PLAY;
    TRACE("Receive a mazzo  \n");
    eGameType eTypeOfGame;
    if ( g_GameSettings.bUnDecked )
    {
        eTypeOfGame = BRISC_NORMINDUE;
    }
    else
    {
        eTypeOfGame = BIRSC_SCOPERTA;
    }
    m_pBriscolada->InitPlayWithMazzo(vct_Temp, eTypeOfGame);

    m_pBriscolada->GetStatus(&m_eGameStaus);

                            // visualization

    visualizeCards();

    m_bMazzoRecieved = TRUE;
}

////////////////////////////////////////
//       sendCardPlayed
/*! Send a played card to remote
// \param int iIndex : index played
*/
BOOL CClient_jpgDlg::sendCardPlayed(int iIndex)
{
    CString strBuff;
    strBuff.Format("%d",iIndex);
    
    m_pOpponent->GetSock()->SendString("CARD_PLAYED %s",strBuff);

    return TRUE;
}



////////////////////////////////////////
//       SetWhoFirstStart
/*! Remote set who startthe game
// \param int iIndex : player index that start
*/
void CClient_jpgDlg::SetWhoFirstStart(int iIndex)
{
    m_pBriscolada->SetFirstPlayer(iIndex);
}


///////////////////////////////////////////// **** TEST CODE **********************

#ifdef _TEST_SOCKET

void CClient_jpgDlg::OnBtTestcard3() 
{
	if (m_eGameStaus == WAITINGPLAYER_TOPLAY)
    {
                                // play the card on the third position in hand
        m_pBriscolada->CardIsPlayed( PLAYER_ME, 2); 
        m_pBriscolada->GetStatus(&m_eGameStaus);

    }
	
}

void CClient_jpgDlg::OnBtTestcard2() 
{
	if (m_eGameStaus == WAITINGPLAYER_TOPLAY)
    {
                                // play the card on the second position in hand
        m_pBriscolada->CardIsPlayed( PLAYER_ME, 1); 
        m_pBriscolada->GetStatus(&m_eGameStaus);

    }
	
}

void CClient_jpgDlg::OnBtTestcard1() 
{
	if (m_eGameStaus == WAITINGPLAYER_TOPLAY)
    {
                                // play the card on the first position in hand
        m_pBriscolada->CardIsPlayed( PLAYER_ME, 0); 
        m_pBriscolada->GetStatus(&m_eGameStaus);

    }
	
}
#endif
