// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__04157D28_4F55_11D5_A3F9_0004760ECF99__INCLUDED_)
#define AFX_STDAFX_H__04157D28_4F55_11D5_A3F9_0004760ECF99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <afxcview.h>			// MFC support for Windows 95 Common Controls
#include <afxhtml.h>			// MFC support for Windows 95 Common Controls

#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions
#include <afxtempl.h>

// deck com stuff
#import "AX_jpg_Server.tlb" no_namespace named_guids
#include <comcat.h>



#define WM_SOCKCONNECT      WM_USER + 100
#define WM_SENDTHISMESSAGE  WM_USER + 101
#define WM_DESTROYME        WM_USER + 102
#define WM_BLOCKTHISCONTACT WM_USER + 103
#define WM_TYPENOTIFY       WM_USER + 104
#define WM_CANCELXFER       WM_USER + 105
#define WM_REQUESTXFER      WM_USER + 106
#define WM_KILLXFER         WM_USER + 107
#define WM_TRANSFERCOMPLETE WM_USER + 108
#define WM_REMOTENAMENEW    WM_USER + 109
#define WM_DESTROYSOCK      WM_USER + 110
#define WM_DESTROYCONTACT   WM_USER + 111

//add com ATL server support

//end com ATL server support

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__04157D28_4F55_11D5_A3F9_0004760ECF99__INCLUDED_)
