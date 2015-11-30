#if !defined(AFX_LISTENSOCKET_H__5F8EEDEB_E2D9_4220_BE04_15EDFC2F7795__INCLUDED_)
#define AFX_LISTENSOCKET_H__5F8EEDEB_E2D9_4220_BE04_15EDFC2F7795__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//


class NetGameStartDlg;

/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target

class CListenSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CListenSocket(NetGameStartDlg*);
	virtual ~CListenSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	NetGameStartDlg*  m_pDlgStartGame;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__5F8EEDEB_E2D9_4220_BE04_15EDFC2F7795__INCLUDED_)
