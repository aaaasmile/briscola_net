// GameOptions.cpp : implementation file
//

#include "stdafx.h"
#include "Client_jpg.h"
#include "GameOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const LPCTSTR lpcstrVip1("Daniele Zanoni"); 
const LPCTSTR lpcstrVip11("San");

/////////////////////////////////////////////////////////////////////////////
// CGameOptions dialog


CGameOptions::CGameOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CGameOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGameOptions)
   	//}}AFX_DATA_INIT
    m_bNetGame = FALSE;
}


void CGameOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGameOptions)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGameOptions, CDialog)
	//{{AFX_MSG_MAP(CGameOptions)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameOptions message handlers



HBRUSH CGameOptions::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
                            // all controls have paint with the window background
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}

BOOL CGameOptions::OnInitDialog(void)
{
	return TRUE;
}
