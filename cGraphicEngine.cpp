// cGraphicEngine.cpp

#include "StdAfx.h"
#include "cGraphicEngine.h"
#include "Resource.h"

// value from deck activex (mfc doesn't import them)
// category ID of Decks
// {B3C0DA05-7C56-40c9-9524-9E2F286B1B7D}
CATID CATID_Decks  = { 0xb3c0da05, 0x7c56, 0x40c9, { 0x95, 0x24, 0x9e, 0x2f, 0x28, 0x6b, 0x1b, 0x7d } };
// interface IAxJpgCard
/*
const IID IID_IAxJpgCard = {0x25763CCD,0x4C53,0x11D5,{0xA3,0x1D,0x00,0xA0,0xCC,0x77,0xE7,0x9C}};
const ID   IAxJpgCard
*/

#include <math.h>
#include "cBriscolaGame.h"


cGraphicEngine::cGraphicEngine()
{
	m_pWin = 0;
	m_lCardDimX = -1;
	m_lCardDimY = -1;
}


////////////////////////////////////////
//       checkCardsDecks
/*! Check all decks installed
*/
void cGraphicEngine::checkCardsDecks()
{
	ICatInformation* pci = 0;
	HRESULT hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 0, 
		CLSCTX_ALL, IID_ICatInformation, (void**)&pci);
	if (pci)
	{
		IEnumCLSID *pec = 0;
		CATID rgcid[1];
		rgcid[0] = CATID_Decks;

		hr = pci->EnumClassesOfCategories(1, rgcid, -1, 0, &pec);
		if (pec)
		{
			enum{MAX = 64};
			CLSID rgclsid[MAX];
			do
			{
				ULONG cActual = 0;
				hr = pec->Next(MAX, rgclsid, &cActual);
				if (SUCCEEDED(hr))
				{
					for (unsigned int i = 0; i < cActual; i++)
					{
						getTheNameOfDeck(rgclsid[i]);
					}
				}
			}
			while( hr == S_OK ); // don't use SUCCEEDED please!
			pec->Release();
		}
		pci->Release();
	}
}


////////////////////////////////////////
//       getTheNameOfDeck
/*! 
// \param CLSID clDeck : 
*/
void cGraphicEngine::getTheNameOfDeck(CLSID clDeck)
{
	IAxJpgCard* pICard = 0;
	HRESULT hr = CoCreateInstance(clDeck, 0, CLSCTX_ALL, IID_IAxJpgCard, (void**)&pICard );

	_bstr_t bstrName = pICard->GetDeckName();
	
	m_strNomeCarte = (char*)bstrName;
	
	pICard->get_SizeImageX(&m_lCardDimX);
	pICard->get_SizeImageY(&m_lCardDimY);

	pICard->Release();

    m_CLSIDDeck = clDeck;
	
	//myCard.CreateControl(clDeck, NULL, WS_VISIBLE, CRect (0, 0, 150, 300), m_pWin, 1100);
	

	//tmpCard.Create(NULL, WS_VISIBLE, CRect (0, 0, 150, 300), m_pWin, 1100); 
}


////////////////////////////////////////
//       Init
/*! Init game graphic engine
*/
BOOL cGraphicEngine::Init()
{
    showSplash();
    DestroySplash();
	checkCardsDecks();
	//createAllCards();

	return TRUE;
}


////////////////////////////////////////
//       createAllCards
/*! 
*/
BOOL cGraphicEngine::createAllCards()
{
   
	CRect rctParent;
	m_pWin->GetClientRect(&rctParent);

	int iWidthParent = rctParent.right - rctParent.left;
	int iHeightParent = rctParent.bottom - rctParent.top;

	CWnd* pcwndBut = m_pWin->GetDlgItem(IDOK);
	CRect rctButton;
	pcwndBut->GetClientRect(&rctButton);

	int iWoffset = rctButton.right / 4;
	// remove space for buttons on the right side
	int iWidthToFill = iWidthParent - rctButton.right - iWoffset * 2;
	// remove space on the left side
	iWidthToFill = iWidthToFill - iWoffset;
	// remove space on top
	int iHeightToFill = iHeightParent - iWoffset;
	// remove space on buttom
	//iHeightToFill = iHeightToFill - iWoffset;
	// 1/3 height is reserved for my hand: check is the dimension fit, if not reduce with proportion
	int iHeightForMyHand = iHeightToFill / 3;
	int iWidthForMyHand = iWidthToFill - iWoffset;
	
	BOOL bWidthMyHandOk;
	BOOL bHeightMyHandOk;
	float dRatioWidthMyHand = 0.0;
	float dRatioHeightMyHand = 0.0;
	int iPrognoseWidthCard = m_lCardDimX;
	int iPrognoseHeightCard = m_lCardDimY;
	int iWidthPrognoseMyHand;
	int iHeightPrognoseMyHand;
    

	do 
	{
        int iReduceStepH = 5;
        int iReduceStepW = 5;
		
        // check prognose my hand dimensions 
		iWidthPrognoseMyHand = 3 * iPrognoseWidthCard + 3 * iWoffset;
		iHeightPrognoseMyHand = iPrognoseHeightCard;

		//check the width
		if (iWidthPrognoseMyHand < iWidthForMyHand)
		{
			bWidthMyHandOk = TRUE;
		}
		else
		{
			bWidthMyHandOk = FALSE;
		}
        dRatioWidthMyHand = (float)iWidthPrognoseMyHand / (float)iWidthForMyHand;

		// check the height
		if (iHeightPrognoseMyHand < iHeightForMyHand)
		{
			bHeightMyHandOk = TRUE;
		}
		else
		{
			bHeightMyHandOk = FALSE;
		}
        dRatioHeightMyHand = (float)iHeightPrognoseMyHand / (float)iHeightForMyHand;
		
        if (!bHeightMyHandOk || !bWidthMyHandOk)
		{
            float fSup;
            float fInf;
			// some dimension have to be reduced
			if ( dRatioHeightMyHand > dRatioWidthMyHand)
			{
				iPrognoseHeightCard -= iReduceStepH; 
                float fReduce = ((float)m_lCardDimX * iReduceStepH );
                fReduce = fReduce / m_lCardDimY; 
                fInf = floor(fReduce);
                fSup = ceil(fReduce);
                if ( fReduce - fInf > fSup -  fReduce)
                {
                    iReduceStepW = (int)fSup;
                }
                else
                {
                    iReduceStepW = (int)fInf;
                }
                iPrognoseWidthCard -= iReduceStepW;
			}
            else
            {
                iPrognoseWidthCard -= iReduceStepW;
                float fReduce = ((float)m_lCardDimY * iReduceStepW );
                fReduce = fReduce / m_lCardDimX;
                fInf = floor(fReduce);
                fSup = ceil(fReduce);
                if ( fReduce - fInf > fSup -  fReduce)
                {
                    iReduceStepH = (int)fSup;
                }
                else
                {
                    iReduceStepH = (int)fInf;
                }
                iPrognoseHeightCard -= iReduceStepH;
            }
		}
	}
	while (!bHeightMyHandOk || !bWidthMyHandOk);

    int iWoffsetH = 10;
    int iIDinitial = 1100;
    int iXtop = iWoffset; 
    int iYtop = iHeightForMyHand * 2 + iWoffsetH;

    // now we have the dimension for card in myhand, create the cards
    for (int i = 0; i < 3; i ++)
    {
        m_vctAxMyCards[i].Create(m_CLSIDDeck, NULL, WS_VISIBLE, 
            CRect (iXtop, iYtop, iXtop + iPrognoseWidthCard, iYtop + iPrognoseHeightCard), m_pWin, iIDinitial);

        iIDinitial++;
        iXtop = iXtop + iWoffset + iPrognoseWidthCard;
    }
    m_vctAxMyCards[0].SetCardIndex(1);
    m_vctAxMyCards[1].SetCardIndex(2);
    m_vctAxMyCards[2].SetCardIndex(3);

    // now we can draw opponent cards
    iXtop = iWoffset;
    iYtop = 0 + iWoffsetH;
    for (int i = 0; i < 3; i ++)
    {
        m_vctAxOppCards[i].CreateControl(m_CLSIDDeck, NULL, WS_VISIBLE, 
            CRect (iXtop, iYtop, iXtop + iPrognoseWidthCard, iYtop + iPrognoseHeightCard), m_pWin, iIDinitial);

        iIDinitial++;
        iXtop = iXtop + iWoffset + iPrognoseWidthCard;
    } 

    //deck 
    iXtop = (iWidthForMyHand / 2 - iPrognoseWidthCard );
    iYtop = iHeightForMyHand + iWoffsetH;
    m_AxMyDeck.CreateControl(m_CLSIDDeck, NULL, WS_VISIBLE, 
            CRect (iXtop, iYtop, iXtop + iPrognoseWidthCard, iYtop + iPrognoseHeightCard), m_pWin, iIDinitial);
    iIDinitial++;

    // in tavola
    iXtop =  (iWidthForMyHand / 2 - iPrognoseWidthCard ) + iPrognoseWidthCard / 3;
    iYtop = iHeightForMyHand + iWoffsetH + iPrognoseWidthCard / 2;
    m_AXintavola.CreateControl(m_CLSIDDeck, NULL, WS_VISIBLE, 
            CRect (iXtop, iYtop, iXtop + iPrognoseHeightCard, iYtop + iPrognoseWidthCard), m_pWin, iIDinitial);
    iIDinitial++;

    // carte giocate 1
    iXtop = (iWidthForMyHand / 2 - iPrognoseWidthCard ) + 3 * iPrognoseWidthCard - 20;
    iYtop = iHeightForMyHand + iWoffsetH - 10;
    m_AxFirstPlayed.CreateControl(m_CLSIDDeck, NULL, WS_VISIBLE, 
            CRect (iXtop, iYtop, iXtop + iPrognoseWidthCard, iYtop + iPrognoseHeightCard), m_pWin, iIDinitial);
    iIDinitial++;


    // carte giocate 2
    iXtop = (iWidthForMyHand / 2 - iPrognoseWidthCard ) + 3 * iPrognoseWidthCard + 30;
    iYtop = iHeightForMyHand + iWoffsetH + 10;
    m_AxSecondPlayed.CreateControl(m_CLSIDDeck, NULL, WS_VISIBLE, 
            CRect (iXtop, iYtop, iXtop + iPrognoseWidthCard, iYtop + iPrognoseHeightCard), m_pWin, iIDinitial);
    iIDinitial++;

	return TRUE;
}

////////////////////////////////////////
//       showSplash
/*! 
*/
BOOL cGraphicEngine::showSplash()
{
								// show spash screen
    VERIFY(m_Splash.CreateFromStatic(IDC_HTMLINTRO, m_pWin));
	m_Splash.LoadFromResource(_T("initial.htm"));

	return TRUE;

}

////////////////////////////////////////
//       DestroySplash
/*! 
*/
BOOL cGraphicEngine::DestroySplash()
{
	m_Splash.DestroyWindow();
	return TRUE;
}

////////////////////////////////////////
//       allcardsInvisible
/*! Set all cards controls Invisibile
*/
void cGraphicEngine::allcardsInvisible() 
{
    tagCARDSHOWSTATUS  lStatusId = CSW_ST_INVISIBLE;
   
    for (int i = 0; i < 3; i ++)
    {
        m_vctAxOppCards[i].SetCardStatus(&lStatusId);
        m_vctAxMyCards[i].SetCardStatus(&lStatusId);
    }
    
    m_AxMazzoDeck.SetCardStatus(&lStatusId);
    m_AxFirstPlayed.SetCardStatus(&lStatusId);
    m_AxSecondPlayed.SetCardStatus(&lStatusId);
    m_AXintavola.SetCardStatus(&lStatusId);
    m_AxMyDeck.SetCardStatus(&lStatusId);
    m_AxOpponentDeck.SetCardStatus(&lStatusId);

}

