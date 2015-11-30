// ConvEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ConvEdit.h"
#include "Conversation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//The edit boxes in the conversation dialogs

CConvEdit::CConvEdit()
{
	Brush.CreateSolidBrush(RGB(255, 255, 255));
	Font.CreateFont(15, 15, 0, 0, FW_BOLD, FALSE, FALSE,0,0,0,0,0,0, "Verdana");
}

CConvEdit::~CConvEdit()
{
}


BEGIN_MESSAGE_MAP(CConvEdit, CEdit)
	//{{AFX_MSG_MAP(CConvEdit)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_CHAR()
	ON_WM_SYSCHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvEdit message handlers


int CConvEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	DragAcceptFiles(TRUE);
	SetMargins(1, 1);
	SetFont(&Font);
	return 0;
}

HBRUSH CConvEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetBkColor(RGB(255, 255, 255));
	 //TODO: Return a non-NULL brush if the parent's handler should not be called
	return (HBRUSH) Brush;
}

void CConvEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == 13)
	{
		CConversation *Conv = (CConversation *)GetParent();
		Conv->OnSend();
	}
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CConvEdit::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	
	if (nChar == 115 && nFlags == 8223) //Alt+S
	{
		CConversation *Conv = (CConversation *)GetParent();
		Conv->OnSend();
	}
	CEdit::OnSysChar(nChar, nRepCnt, nFlags);
}
