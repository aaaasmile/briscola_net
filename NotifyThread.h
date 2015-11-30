#if !defined(AFX_NOTIFYTHREAD_H__628A80E3_6CF8_4D8A_8389_190341DAF810__INCLUDED_)
#define AFX_NOTIFYTHREAD_H__628A80E3_6CF8_4D8A_8389_190341DAF810__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// NotifyThread.h : header file
//

#include "Client_jpgDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CNotifyThread thread

class CContact;
class NetGameStartDlg;


class CNotifyThread : public CWinThread
{
	DECLARE_DYNCREATE(CNotifyThread)

public:
	CNotifyThread();
	virtual ~CNotifyThread();

public:
    LIST_CONTACT*      pList;
	NetGameStartDlg*   view;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotifyThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNotifyThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTIFYTHREAD_H__628A80E3_6CF8_4D8A_8389_190341DAF810__INCLUDED_)
