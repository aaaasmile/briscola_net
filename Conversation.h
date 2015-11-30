#if !defined(AFX_CONVERSATION_H__AE694505_0FCE_4EC3_B10E_7E34B877AB77__INCLUDED_)
#define AFX_CONVERSATION_H__AE694505_0FCE_4EC3_B10E_7E34B877AB77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Conversation.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CConversation dialog

#include "ConvEdit.h"
//#include "CornerStatic.h"
//#include "SendButton.h"

class CContact;
class CConversationThread;
class CConversation;


struct MESSAGE
{
	CConversation*  pCallingDialog;
	CContact*       pTo;
	CString         strMessage;
};

//! class conversation
/**
// dialog to chat
*/
class CConversation : public CDialog
{
// Construction
public:
    // standard constructor
	CConversation(CWnd* pParent = NULL, CContact *With = NULL, CString* pstrMsg=NULL);   
    // destructor
    ~CConversation();

// Dialog Data
	//{{AFX_DATA(CConversation)
	enum { IDD = IDD_CONVERSATION_DIALOG };
	CConvEdit	m_SendMsg;
	CConvEdit	m_Chat;
	//}}AFX_DATA

//operation
public:	
	void        AppendWindowTextF(char *, ...);
	void        OnSend();

// attributes
public:
    CStatic sideLeft, sideRight, sideTop, sideBottom;
	CStatic cornerTopLeft, cornerTopRight, cornerBottomLeft, cornerBottomRight;
	CStatic bsideBottom;
    CContact*   pContact;
    CContact*   pMe;
    CString     m_strDefaultMessage;
    CToolBar    m_toolBar;
	CStatusBar  m_statusBar;
	CFont       Font;
	HICON       m_hIcon;
	CBrush      BrushWhite;
    CBrush      BrushBlue;
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConversation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConversation)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChangeSendmsg();
	afx_msg void OnIdrconversationmenuBlock();
	afx_msg void OnIdrconversationmenuSendfile();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnIdrconversationmenuChangefont();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVERSATION_H__AE694505_0FCE_4EC3_B10E_7E34B877AB77__INCLUDED_)
