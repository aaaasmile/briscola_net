#if !defined(AFX_CONVERSATIONTHREAD_H__77323743_01D2_4BA8_9E62_81CF992FD913__INCLUDED_)
#define AFX_CONVERSATIONTHREAD_H__77323743_01D2_4BA8_9E62_81CF992FD913__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConversationThread.h : header file
//

#include "Conversation.h"

/////////////////////////////////////////////////////////////////////////////
// CConversationThread thread

class CContact;

class CConversationThread : public CWinThread
{
	DECLARE_DYNCREATE(CConversationThread)

public:
    // constructor
	CConversationThread(CContact * = NULL, char * = NULL);
    // destructor
	virtual ~CConversationThread();

// Operations
public:

// Attributes
public:
    CContact        *pWith;
	CConversation   *pConv;
	CString         strDefaultMsg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConversationThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConversationThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVERSATIONTHREAD_H__77323743_01D2_4BA8_9E62_81CF992FD913__INCLUDED_)
