#if !defined(AFX_GAMEOPTIONS_H__535356F3_59AE_11D5_A401_0004760ECF99__INCLUDED_)
#define AFX_GAMEOPTIONS_H__535356F3_59AE_11D5_A401_0004760ECF99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameOptions.h : header file
//

// forward declaration
class GAME_SETTINGS;

/////////////////////////////////////////////////////////////////////////////
// CGameOptions dialog

class CGameOptions : public CDialog
{
// Construction
public:
	CGameOptions(CWnd* pParent = NULL);   // standard constructor

   
// Dialog Data
	//{{AFX_DATA(CGameOptions)
	enum { IDD = IDD_OPTIONS };
	//}}AFX_DATA
	//! flag to regognize if a network game
    BOOL    m_bNetGame;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGameOptions)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
   
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEOPTIONS_H__535356F3_59AE_11D5_A401_0004760ECF99__INCLUDED_)
