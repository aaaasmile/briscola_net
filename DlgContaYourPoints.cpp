// DlgContaYourPoints.cpp : implementation file
//

#include "stdafx.h"
#include "client_jpg.h"
#include "DlgContaYourPoints.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgContaYourPoints dialog


DlgContaYourPoints::DlgContaYourPoints(CWnd* pParent /*=NULL*/)
	: CDialog(DlgContaYourPoints::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgContaYourPoints)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_iMazzoPos = 0;
    m_iNumCards  = 0;
    m_iTotPoints = 0;
}


void DlgContaYourPoints::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgContaYourPoints)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_BT_UPCONTA, m_btUpCard);
    DDX_Control(pDX, IDC_BT_DOWNCONTA, m_btDownCard);
    DDX_Control(pDX, IDC_ST_POINTS_CONTA, m_lblNumOfPoints);
    DDX_Control(pDX, IDC_ST_NUMCARD_CONTA, m_lblNuOfCards);
    DDX_Control(pDX, IDC_BT_UPCONTA_0, m_btDownFirst);
    DDX_Control(pDX, IDC_BT_DOWNCONTA_F, m_btUpEnd);
}


BEGIN_MESSAGE_MAP(DlgContaYourPoints, CDialog)
	//{{AFX_MSG_MAP(DlgContaYourPoints)
	ON_BN_CLICKED(IDC_BT_DOWNCONTA, OnBtDownconta)
	ON_BN_CLICKED(IDC_BT_UPCONTA, OnBtUpconta)
	ON_BN_CLICKED(IDC_BT_DOWNCONTA_F, OnBtDowncontaF)
	ON_BN_CLICKED(IDC_BT_UPCONTA_0, OnBtUpconta0)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgContaYourPoints message handlers

BOOL DlgContaYourPoints::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    //HBITMAP bmArrowUp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), (LPCTSTR)IDB_ARROW_UP, IMAGE_BITMAP, 0, 0, 0);
	
    //m_btUpCard.SetBitmap(bmArrowUp); 
    //m_btUpCard.SetIcon (AfxGetApp ()->LoadIcon (IDI_ARROW_UP));
    //m_btDownCard.SetIcon (AfxGetApp ()->LoadIcon (IDI_DOWN));

	// to do: create ax control
	//m_axCardPoints.Create(); 

    m_iNumCards = m_vct_MyCards.size();
    m_iMazzoPos = 0;

    CString strTxt;
    strTxt.Format("Punti totali: %d", m_iTotPoints);  
    m_lblNumOfPoints.SetWindowText(strTxt); 

    strTxt.Format("Carte prese: %d", m_iNumCards);  
    m_lblNuOfCards.SetWindowText(strTxt);

    showPos();
	
	return TRUE; 
}


////////////////////////////////////////
//       showPos
/*! Show cards on current position
*/
void DlgContaYourPoints::showPos()
{
    tagCARDSHOWSTATUS lStatusId = CSW_ST_EMPTY;
    int iIndexCard = 0;
    if (  m_iMazzoPos < m_iNumCards && m_iMazzoPos >= 0)
    {
        lStatusId = CSW_ST_DRAWNORMAL;
        iIndexCard = m_vct_MyCards[m_iMazzoPos];
    }
    else if ( m_iMazzoPos < 0)
    {
        m_iMazzoPos = -1;
    }
    else if ( m_iMazzoPos >= m_iNumCards)
    {
        m_iMazzoPos = m_iNumCards;
    }

    m_axCardPoints.SetCardIndex( iIndexCard );
    m_axCardPoints.SetCardStatus(&lStatusId);
}


////////////////////////////////////////
//       OnBtDownconta
/*! Previous card
*/
void DlgContaYourPoints::OnBtDownconta() 
{
    m_iMazzoPos++;
	showPos();
}


////////////////////////////////////////
//       OnBtUpconta
/*! Next card
*/
void DlgContaYourPoints::OnBtUpconta() 
{
	m_iMazzoPos--;
	showPos();
	
}

////////////////////////////////////////
//       OnBtDowncontaF
/*! Shows the last card 
*/
void DlgContaYourPoints::OnBtDowncontaF() 
{
	m_iMazzoPos = m_iNumCards - 1;
	showPos();
}


////////////////////////////////////////
//       OnBtUpconta0
/*! Shows the first card
*/
void DlgContaYourPoints::OnBtUpconta0() 
{
    m_iMazzoPos = 0;
	showPos();
}
