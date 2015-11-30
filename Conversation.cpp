// Conversation.cpp : implementation file
//

#include "stdafx.h"
//#include "Netmsg.h"
#include "Conversation.h"
#include "Contact.h"
//#include "ContactView.h"
//#include "FileSend.h"
//#include "ConvEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//The conversation dialog

CConversation::CConversation(CWnd* pParent, CContact *With, CString* pstrMsg)
: CDialog(CConversation::IDD, pParent)
{
    m_strDefaultMessage = *pstrMsg;
    pContact = With;
    BrushWhite.CreateSolidBrush(RGB(255, 255, 255));
    BrushBlue.CreateSolidBrush(RGB(0, 73, 181));

    CNetSocket* pSocketNet = With->GetSock(); 
    ASSERT(pSocketNet);
    pMe = pSocketNet->GetConctactMe();

    //{{AFX_DATA_INIT(CConversation)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    m_hIcon = AfxGetApp()->LoadIcon(IDR_CONVERSATION);

   
}

CConversation::~CConversation()
{
}


void CConversation::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CConversation)
    DDX_Control(pDX, IDC_SENDMSG, m_SendMsg);
    DDX_Control(pDX, IDC_CHAT, m_Chat);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConversation, CDialog)
//{{AFX_MSG_MAP(CConversation)
    ON_WM_SIZE()
    ON_WM_TIMER()
    ON_EN_CHANGE(IDC_SENDMSG, OnChangeSendmsg)
    ON_COMMAND(ID_IDRCONVERSATIONMENU_BLOCK, OnIdrconversationmenuBlock)
    ON_WM_CTLCOLOR()
    ON_COMMAND(ID_IDRCONVERSATIONMENU_CHANGEFONT, OnIdrconversationmenuChangefont)
    ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConversation message handlers

void CConversation::OnSize(UINT nType, int cx, int cy) 
{
    CDialog::OnSize(nType, cx, cy);
    CConvEdit *SendMsg = (CConvEdit *)GetDlgItem(IDC_SENDMSG);
    CConvEdit *Chat = (CConvEdit *)GetDlgItem(IDC_CHAT);
    
    if (!SendMsg || !Chat) 
        return;
    
    Chat->MoveWindow(6, 56, cx - 10, cy - 152);
    SendMsg->MoveWindow(6, cy - 90, cx - 73, 58);
    
    RECT rect;
    GetClientRect(&rect);
    if (!::IsWindow(cornerTopLeft.m_hWnd)) 
        return;
    
    cornerTopLeft.MoveWindow(0, 38, 16, 16);
    cornerBottomLeft.MoveWindow(0, rect.bottom - 34, 16, 16);
    cornerTopRight.MoveWindow(rect.right - 16, 38, 16, 16);
    cornerBottomRight.MoveWindow(rect.right - 16, rect.bottom - 34, 16, 16);
    sideLeft.MoveWindow(0, 38, 4, rect.bottom - 56);
    sideBottom.MoveWindow(4, rect.bottom - 96, rect.right - 8, 4);
    sideTop.MoveWindow(16, 38, rect.right - 16, 4);
    sideRight.MoveWindow(rect.right - 4, 54, 4, rect.bottom - 88);
    bsideBottom.MoveWindow(16, rect.bottom - 21, rect.right - 32, 3);
    //Send.MoveWindow(rect.right - 61, rect.bottom - 80, 52, 45);
    
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
    RedrawWindow();
}

static UINT auIDToolBar[] = {
        ID_IDRCONVERSATIONMENU_CHANGEFONT
};

static UINT auIDStatusBar[] = {
    ID_SEPARATOR
};

BOOL CConversation::OnInitDialog() 
{
    CenterWindow(GetDesktopWindow());
    CDialog::OnInitDialog();
    
    
    if (m_statusBar.Create(this))
    {
        m_statusBar.SetIndicators(auIDStatusBar, sizeof(auIDStatusBar) / sizeof(unsigned int));
        
        m_statusBar.SetPaneInfo(0, m_statusBar.GetItemID(0),
            SBPS_STRETCH, NULL );
    }
    
    if (m_toolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
        | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | TBSTYLE_TRANSPARENT))
    {
        SIZE sz, szbutton;
        sz.cx = 32;
        sz.cy = 32;
        szbutton.cy = 38;
        szbutton.cx = 39;
        m_toolBar.SetSizes(szbutton, sz);
        m_toolBar.GetToolBarCtrl().AddBitmap(1, IDB_CHANGEFONT);
        m_toolBar.SetButtons(auIDToolBar, sizeof(auIDToolBar) / sizeof(unsigned int));
    }
    CRect rcClientStart;
    CRect rcClientNow;
    GetClientRect(rcClientStart);
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST,
        0, reposQuery, rcClientNow);
    CPoint ptOffset(rcClientNow.left - rcClientStart.left,
        rcClientNow.top - rcClientStart.top);
    
    CRect  rcChild;
    CWnd* pwndChild = GetWindow(GW_CHILD);
    
    while (pwndChild)
    {
        pwndChild->GetWindowRect(rcChild);
        ScreenToClient(rcChild);
        rcChild.OffsetRect(ptOffset);
        pwndChild->MoveWindow(rcChild, FALSE);
        pwndChild = pwndChild->GetNextWindow();
    }
    
    CRect rcWindow;
    GetWindowRect(rcWindow);
    rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
    rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
    MoveWindow(rcWindow, FALSE);
    
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
    
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    
    m_statusBar.SetIcon(m_hIcon, FALSE);
    
    CString cstr;
    if (!m_strDefaultMessage.IsEmpty())
    {
        AppendWindowTextF("< %s >: %s\r\n", pContact->GetScreenName(), m_strDefaultMessage);
        FlashWindow(TRUE);
    }
    cstr.Format("Briscola_Net chat con: %s", pContact->GetScreenName());
    
    SetWindowText(cstr);
    RECT rect;
    GetClientRect(&rect);
    
    m_Chat.MoveWindow(6, 56, rect.right - 10, rect.bottom - 152);
    m_SendMsg.MoveWindow(5, rect.bottom - 90, rect.right - 73, 58);
    
    m_SendMsg.SetLimitText(500);
    
    CRect srect;
    srect.SetRectEmpty();
    
    cornerTopLeft.Create(NULL, WS_CHILD | SS_BITMAP, srect, this);
    cornerTopLeft.SetBitmap((HBITMAP)::LoadImage(AfxGetInstanceHandle(), (LPCSTR)IDB_TOPLEFT, IMAGE_BITMAP, 0, 0, 0));
    cornerTopLeft.ShowWindow(SW_SHOW);
    
    cornerBottomLeft.Create(NULL, WS_CHILD | SS_BITMAP, srect, this);
    cornerBottomLeft.SetBitmap((HBITMAP)::LoadImage(AfxGetInstanceHandle(), (LPCSTR)IDB_BOTTOMLEFT, IMAGE_BITMAP, 0, 0, 0));
    cornerBottomLeft.ShowWindow(SW_SHOW);
    
    cornerTopRight.Create(NULL, WS_CHILD | SS_BITMAP, srect, this);
    cornerTopRight.SetBitmap((HBITMAP)::LoadImage(AfxGetInstanceHandle(), (LPCSTR)IDB_TOPRIGHT, IMAGE_BITMAP, 0, 0, 0));
    cornerTopRight.ShowWindow(SW_SHOW);
    
    cornerBottomRight.Create(NULL, WS_CHILD | SS_BITMAP, srect, this);
    cornerBottomRight.SetBitmap((HBITMAP)::LoadImage(AfxGetInstanceHandle(), (LPCSTR)IDB_BOTTOMRIGHT, IMAGE_BITMAP, 0, 0, 0));
    cornerBottomRight.ShowWindow(SW_SHOW);
    
    
    sideLeft.Create(NULL, WS_CHILD, srect, this);
    sideLeft.ShowWindow(SW_SHOW);
    
    sideBottom.Create(NULL, WS_CHILD, srect, this);
    sideBottom.ShowWindow(SW_SHOW);
    
    bsideBottom.Create(NULL, WS_CHILD, srect, this);
    bsideBottom.ShowWindow(SW_SHOW);
    
    sideTop.Create(NULL, WS_CHILD, srect, this);
    sideTop.ShowWindow(SW_SHOW);
    
    sideRight.Create(NULL, WS_CHILD, srect, this);
    sideRight.ShowWindow(SW_SHOW);
    
    LOGFONT *lf;
    unsigned int sz = sizeof(LOGFONT);
    if (AfxGetApp()->GetProfileBinary("Settings", "Font", (LPBYTE *)&lf, &sz))
    {
        
    }
    else
    {
        lf = new LOGFONT;
        GetFont()->GetLogFont(lf);
        lf->lfHeight = 16;
        strcpy(lf->lfFaceName, "Tahoma");
        lf->lfWeight = FW_BOLD;
    }
    Font.CreateFontIndirect(lf);
    delete [] lf;
    m_Chat.SetFont(&Font);
    m_SendMsg.SetFont(&Font);
    
    RECT crect;
    GetClientRect(&crect);
    cornerTopLeft.MoveWindow(0, 38, 16, 16);
    cornerBottomLeft.MoveWindow(0, crect.bottom - 34, 16, 16);
    cornerTopRight.MoveWindow(crect.right - 16, 38, 16, 16);
    cornerBottomRight.MoveWindow(crect.right - 16, crect.bottom - 34, 16, 16);
    sideLeft.MoveWindow(0, 38, 4, rect.bottom - 56);
    sideBottom.MoveWindow(4, crect.bottom - 96, crect.right - 8, 4);
    sideTop.MoveWindow(16, 38, crect.right - 16, 4);
    sideRight.MoveWindow(crect.right - 4, 54, 4, crect.bottom - 88);
    bsideBottom.MoveWindow(16, crect.bottom - 21, crect.right - 32, 3);
    
    SetTimer(1, 1, 0);
    return TRUE;
}


////////////////////////////////////////
//       OnSend
/*! Send the message
*/
void CConversation::OnSend() 
{
    MESSAGE *pMsg = new MESSAGE;
    m_SendMsg.GetWindowText( pMsg->strMessage );
    
    if (pMsg->strMessage.IsEmpty())
    {
        m_SendMsg.SetFocus();
        return;
    }
    if (pContact->Flags & CContact::CFL_BLOCKED)
    {
        AppendWindowTextF("Il messaggio seguente non può essere inviato:\r\n\"%s\"\r\nIl giocatore è bloccato.\r\n", pMsg->strMessage );
        delete pMsg;
    }
    else
    {
        pMsg->pTo  = pContact;
        pMsg->pCallingDialog = this;
        ASSERT(pMe);
        AppendWindowTextF("< %s >: %s\r\n", pMe->GetScreenName(), pMsg->strMessage);
        pMsg->strMessage.Replace("\n", "<%10>");
        pMsg->strMessage.Replace("\r", "");
                            // inform client dialog to send the message
        ::SendMessage(pContact->pPlayApp->GetSafeHwnd(), WM_SENDTHISMESSAGE, 0, (LPARAM) pMsg);
    }
    m_SendMsg.SetFocus();
    m_SendMsg.SetWindowText("");
    OnChangeSendmsg();
}

void CConversation::AppendWindowTextF(char *fmt, ...)
{
    va_list args;
    CString cstr;
    va_start(args, fmt);
    char buf[1024];
    _vsnprintf(buf, sizeof(buf), fmt, args);
    cstr = buf;
    cstr.Replace("<%10>", "\r\n");
    int len = m_Chat.GetWindowTextLength();
    m_Chat.SetSel(len, len);
    m_Chat.ReplaceSel(cstr);
    len = m_Chat.GetWindowTextLength();
    m_Chat.SetCaretPos(m_Chat.PosFromChar(len));
}

void CConversation::OnTimer(UINT nIDEvent) 
{
    m_SendMsg.SetFocus();
    m_Chat.SetSel(m_Chat.GetWindowTextLength(), m_Chat.GetWindowTextLength());
    KillTimer(1);
    CDialog::OnTimer(nIDEvent);
}

void CConversation::OnChangeSendmsg() 
{
    static bool Sent = true;
    char buf[512];
    CConvEdit *SendMsg = (CConvEdit *)GetDlgItem(IDC_SENDMSG);
    SendMsg->GetWindowText(buf, sizeof(buf));
    if (!stricmp(buf, ""))
    {
        RedrawWindow();
        //Send.DeActivate();
    }
    else
    {
        //Send.Activate();
    }
    if (!Sent && !stricmp(buf, ""))
    {
        if (pContact->Flags & CContact::CFL_OFFLINE) return;
        Sent = true;
       //end of typing send
       ::SendMessage(pContact->pPlayApp->GetSafeHwnd(), WM_TYPENOTIFY, 0, (LPARAM) pContact);
    }
    else if (Sent && stricmp(buf, ""))
    {
        if (pContact->Flags & CContact::CFL_OFFLINE) return;
        Sent = false;
        // send typing
        ::SendMessage(pContact->pPlayApp->GetSafeHwnd(), WM_TYPENOTIFY, 1, (LPARAM) pContact);
    }
    
}

void CConversation::OnIdrconversationmenuBlock() 
{
    // conctact is going blocking
    ::SendMessage(pContact->pPlayApp->GetSafeHwnd(), WM_BLOCKTHISCONTACT, 0, (LPARAM) pContact); 	
}



////////////////////////////////////////
//       OnCtlColor
/*! Change the color of the edit border
// \param CDC* pDC : 
// \param CWnd* pWnd : 
// \param UINT nCtlColor : 
*/
HBRUSH CConversation::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    
    if (pWnd == this || pWnd == &m_Chat || pWnd == &m_SendMsg)
    {
        return (HBRUSH) BrushWhite;
    }
    else if (  pWnd == &sideLeft || pWnd == &sideRight 
        || pWnd == &sideTop || pWnd == &sideBottom
        || pWnd == &cornerTopLeft || pWnd == &cornerTopRight 
        || pWnd == &cornerBottomLeft ||
        pWnd == &cornerBottomRight || pWnd == &bsideBottom)
    {
        return (HBRUSH) BrushBlue;
    }
    return hbr;
}

void CConversation::OnIdrconversationmenuChangefont() 
{
    CHOOSEFONT cf;
    LOGFONT lf;
    Font.GetLogFont(&lf);
    cf.lStructSize = sizeof(CHOOSEFONT);
    cf.hwndOwner = GetSafeHwnd();
    cf.lpLogFont = &lf;
    cf.hInstance = AfxGetInstanceHandle();
    cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_BOTH;
    ChooseFont(&cf);
    Font.Detach();
    Font.CreateFontIndirect(&lf);
    AfxGetApp()->WriteProfileBinary("Settings", "Font", (LPBYTE)&lf, sizeof(LOGFONT));
    m_SendMsg.SetFont(&Font);
    m_Chat.SetFont(&Font);
}

void CConversation::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
    lpMMI->ptMinTrackSize.y = 220;
    lpMMI->ptMinTrackSize.x = 100;
    CDialog::OnGetMinMaxInfo(lpMMI);
}


