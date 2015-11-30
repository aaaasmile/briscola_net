// InsertName_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "client_jpg.h"
#include "InsertName_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// InsertName_Dlg dialog


InsertName_Dlg::InsertName_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(InsertName_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(InsertName_Dlg)
	m_strPlayerName = _T("");
	//}}AFX_DATA_INIT
}


void InsertName_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InsertName_Dlg)
	DDX_Text(pDX, IDC_ED_NEWNAME_PLAYER, m_strPlayerName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InsertName_Dlg, CDialog)
	//{{AFX_MSG_MAP(InsertName_Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InsertName_Dlg message handlers
