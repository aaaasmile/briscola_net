// Client_jpg.h : main header file for the CLIENT_JPG application
//

#if !defined(AFX_CLIENT_JPG_H__04157D24_4F55_11D5_A3F9_0004760ECF99__INCLUDED_)
#define AFX_CLIENT_JPG_H__04157D24_4F55_11D5_A3F9_0004760ECF99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

enum
{
	DECK_PIACENTINA 
};

//! class game settings
/**
*/
class GAME_SETTINGS
{
public:
	//!player name
   CString sPlayerName;
   //! delayed animation timer
   long    lDelayTimer;
   //! hand terminate self
   BOOL    bAutoTerminate;
   //! level of the cpu
   long    lLevel;
   //! player guest identification
   long    lGuestId;
   //! flag for "scoperta" game option
   BOOL    bUnDecked;
   //! ip remote channel (4 long values)
   byte    lIpRemote_1;
   byte    lIpRemote_2;
   byte    lIpRemote_3;
   byte    lIpRemote_4;
   //! deck type
   long    lDeckType;
   
public:
   GAME_SETTINGS()
   {
        sPlayerName = "Anonimo";
        lDelayTimer = 3;
        bAutoTerminate = TRUE;
        lLevel = 1;
        lGuestId = 0;
		bUnDecked = FALSE;
        lIpRemote_1 = 127;
        lIpRemote_2 = 0;
        lIpRemote_3 = 0;
        lIpRemote_4 = 1;
		lDeckType = DECK_PIACENTINA;
   }
};


/////////////////////////////////////////////////////////////////////////////
// CClient_jpgApp:
// See Client_jpg.cpp for the implementation of this class
//

class CClient_jpgApp : public CWinApp
{
public:
	CClient_jpgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClient_jpgApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
	void     InitSettings();
	void	 SaveSettings();
// Implementation

	//{{AFX_MSG(CClient_jpgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT_JPG_H__04157D24_4F55_11D5_A3F9_0004760ECF99__INCLUDED_)
