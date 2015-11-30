//axcardBriscola.cpp

#include "stdafx.h"
#include "axcardBriscola.h"

/////////////////////////////////////////////////////////////////////////////
// axcardBriscola

IMPLEMENT_DYNCREATE(axcardBriscola, CWnd)


//! create control and get interface
BOOL axcardBriscola::Create( REFCLSID clsid,LPCTSTR lpszWindowName, DWORD dwStyle,
		                     const RECT& rect,CWnd* pParentWnd, UINT nID)
{ 
    m_pIAxCards = 0;
    BOOL  bRes;
    bRes = CreateControl(clsid, lpszWindowName, dwStyle, rect, pParentWnd, nID); 

    LPUNKNOWN pIUnk = GetControlUnknown();

    if (pIUnk)
        pIUnk->QueryInterface(IID_IAxJpgCard, (void**)&m_pIAxCards);

    return bRes;
}

/////////////////////////////////////////////////////////////////////////////
// axcardBriscola properties

/////////////////////////////////////////////////////////////////////////////
// axcardBriscola operations

void axcardBriscola::SetBackColor(unsigned long newValue)
{
}

unsigned long axcardBriscola::GetBackColor()
{
    return 0;
}


////////////////////////////////////////
//       GetCardIndex
/*! 
*/
long axcardBriscola::GetCardIndex()
{
	ASSERT(m_pIAxCards);

    long nNewValue;
    m_pIAxCards->get_CardIndex(&nNewValue);
	
    return nNewValue;
}


////////////////////////////////////////
//       SetCardIndex
/*! 
// \param long nNewValue : 
*/
void axcardBriscola::SetCardIndex(long nNewValue)
{
     
    ASSERT(m_pIAxCards);

    m_pIAxCards->put_CardIndex(nNewValue);
}


////////////////////////////////////////
//       GetCardStatus
/*! 
*/
tagCARDSHOWSTATUS* axcardBriscola::GetCardStatus()
{
	ASSERT(m_pIAxCards);

    tagCARDSHOWSTATUS* pCardStatus;
	m_pIAxCards->get_CardStatus(pCardStatus);

	return pCardStatus;
}


////////////////////////////////////////
//       SetCardStatus
/*! 
// \param long* newValue : 
*/
void axcardBriscola::SetCardStatus(tagCARDSHOWSTATUS* newValue)
{
    ASSERT(m_pIAxCards);

	m_pIAxCards->put_CardStatus(newValue);
}


////////////////////////////////////////
//       GetNumCardOnDeck
/*! 
*/
long axcardBriscola::GetNumCardOnDeck()
{
	long result;
	ASSERT(m_pIAxCards);

    m_pIAxCards->get_NumCardOnDeck(&result);

	return result;
}

void axcardBriscola::SetNumCardOnDeck(int num)
{
	ASSERT(m_pIAxCards);
	m_pIAxCards->put_NumCardOnDeck(num);
}


////////////////////////////////////////
//       GetSizeImageX
/*! 
*/
long axcardBriscola::GetSizeImageX()
{
	long result;
	ASSERT(m_pIAxCards);
	
    m_pIAxCards->get_SizeImageX(&result);

    return result;
}



////////////////////////////////////////
//       GetSizeImageY
/*! 
*/
long axcardBriscola::GetSizeImageY()
{
	long result;
	ASSERT(m_pIAxCards);
	
    m_pIAxCards->get_SizeImageY(&result);

    return result;
}


////////////////////////////////////////
//       GetDeckName
/*! 
*/
CString axcardBriscola::GetDeckName()
{
	CString result;
    ASSERT(m_pIAxCards);
	
    
    _bstr_t bstrName = m_pIAxCards->GetDeckName();
	
	result = (char*)bstrName;

	return result;
}
