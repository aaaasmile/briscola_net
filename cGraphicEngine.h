//cGraphicEngine.h

#ifndef __GRAPH_ENGINE_CARD_BRISC
#define __GRAPH_ENGINE_CARD_BRISC

#include "axcardBriscola.h"
#include "HtmlCtrl.h"

//! class 
class cGraphicEngine
{
public:
	cGraphicEngine();

	void SetParentWnd(CWnd* wndVal){m_pWin = wndVal;}
	BOOL Init();
	BOOL DestroySplash();

private:
	void	checkCardsDecks();
	void	getTheNameOfDeck(CLSID clDeck);
	BOOL	showSplash();
	BOOL    createAllCards();
    void    allcardsInvisible();

private:
	axcardBriscola tmpCard;
	CWnd myCard;

	//! Opponents cards
	axcardBriscola  m_vctAxOppCards[3];
	//! my cards
	axcardBriscola  m_vctAxMyCards[3];
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
	
	//! parent cwnd
	CWnd*				m_pWin;
	//! splash html control
	CMyHtmlCtrl         m_Splash;
	//! cards name
	CString				m_strNomeCarte;
	//! card original image width
	long                 m_lCardDimX;
	//! card original image height
	long                 m_lCardDimY;
    //! card deck clsid
    CLSID                m_CLSIDDeck;
};



#endif