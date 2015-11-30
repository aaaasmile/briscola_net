// Client_jpg.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Client_jpg.h"
#include "Client_jpgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

GAME_SETTINGS g_GameSettings;
/////////////////////////////////////////////////////////////////////////////
// CClient_jpgApp

BEGIN_MESSAGE_MAP(CClient_jpgApp, CWinApp)
	//{{AFX_MSG_MAP(CClient_jpgApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClient_jpgApp construction

CClient_jpgApp::CClient_jpgApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CClient_jpgApp object

CClient_jpgApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CClient_jpgApp initialization

BOOL CClient_jpgApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	CoInitialize(NULL);

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

    //SetDialogBkColor(RGB(0,0,0),RGB(0,255,0)); 
    //SetDialogBkColor(RGB(0,200,80),RGB(0,0,0)); 
    
    SetDialogBkColor(RGB(11,187,81),RGB(0,0,0)); 

    SetRegistryKey ( _T ( "Jango Soft Etc" ) ) ;

	InitSettings();

    CCommandLineInfo cmdInfo;
    ParseCommandLine (cmdInfo);

    CString strPlayerName;
    BOOL bNewName = FALSE;

    if (cmdInfo.m_strFileName.IsEmpty())
    {
        strPlayerName = _T("Nessuno");
    }
    else
    {
        strPlayerName = cmdInfo.m_strFileName;
        bNewName = TRUE;
    }

	CClient_jpgDlg dlg;
	m_pMainWnd = &dlg;
    if ( bNewName )
    {
                            // set the new player name from command line
        dlg.SetPlayerName(strPlayerName); 
    }
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	return FALSE;
}

////////////////////////////////////////
//       InitSettings
/*! Initialize settings from registry
*/
void CClient_jpgApp::InitSettings()
{
    CString sVersion ;
    CString sKeyPlayerName;
    CString skeyTimer;
    CString skeyAutoTer;
    CString skeyLevel;
    CString skeyUnDeck;
    CString skeyIpremote_1;
    CString skeyIpremote_2;
    CString skeyIpremote_3;
    CString skeyIpremote_4;

    sKeyPlayerName.LoadString( IDS_REG_PLAYERNAME );
    skeyTimer.LoadString   (IDS_REG_TIMER); 
    skeyAutoTer.LoadString (IDS_REG_AUTOTER);
    skeyLevel.LoadString (IDS_REG_LEVEL);
    skeyUnDeck.LoadString (IDS_REG_UNDECK);
    skeyIpremote_1.LoadString (IDS_REG_IPREM_1);
    skeyIpremote_2.LoadString (IDS_REG_IPREM_2);
    skeyIpremote_3.LoadString (IDS_REG_IPREM_3);
    skeyIpremote_4.LoadString (IDS_REG_IPREM_4);

    VERIFY ( sVersion.LoadString ( IDS_VERSIONREGKEY ) ) ;

    CWinApp* pApp = AfxGetApp();

    CString sTemp  = pApp->GetProfileString( sVersion , sKeyPlayerName) ;
    if (sTemp.IsEmpty() == FALSE)
    {
        g_GameSettings.sPlayerName = sTemp;
    }
    g_GameSettings.lDelayTimer  = pApp->GetProfileInt( sVersion , skeyTimer, g_GameSettings.lDelayTimer) ;
    g_GameSettings.bAutoTerminate = pApp->GetProfileInt( sVersion , skeyAutoTer, g_GameSettings.bAutoTerminate) ;
    g_GameSettings.lLevel  = pApp->GetProfileInt( sVersion , skeyLevel, g_GameSettings.lLevel ) ;
    g_GameSettings.bUnDecked = pApp->GetProfileInt( sVersion , skeyUnDeck, g_GameSettings.bUnDecked ) ;
    g_GameSettings.lIpRemote_1 = pApp->GetProfileInt( sVersion , skeyIpremote_1, g_GameSettings.lIpRemote_1  ) ;
    g_GameSettings.lIpRemote_2 = pApp->GetProfileInt( sVersion , skeyIpremote_2, g_GameSettings.lIpRemote_2  ) ;
    g_GameSettings.lIpRemote_3 = pApp->GetProfileInt( sVersion , skeyIpremote_3, g_GameSettings.lIpRemote_3  ) ;
    g_GameSettings.lIpRemote_4 = pApp->GetProfileInt( sVersion , skeyIpremote_4, g_GameSettings.lIpRemote_4  ) ;
}

////////////////////////////////////////
//       SaveSettings
/*! Save settings in the registry
*/
void CClient_jpgApp::SaveSettings()
{
    CString sVersion ;
    CString sKeyPlayerName;
    CString skeyTimer;
    CString skeyAutoTer;
    CString skeyLevel;
    CString skeyUnDeck;
    CString skeyIpremote_1;
    CString skeyIpremote_2;
    CString skeyIpremote_3;
    CString skeyIpremote_4;

    skeyIpremote_1.LoadString (IDS_REG_IPREM_1);
    skeyIpremote_2.LoadString (IDS_REG_IPREM_2);
    skeyIpremote_3.LoadString (IDS_REG_IPREM_3);
    skeyIpremote_4.LoadString (IDS_REG_IPREM_4);

    sKeyPlayerName.LoadString( IDS_REG_PLAYERNAME );
    skeyTimer.LoadString   (IDS_REG_TIMER); 
    skeyAutoTer.LoadString (IDS_REG_AUTOTER);
    skeyLevel.LoadString (IDS_REG_LEVEL);
    skeyUnDeck.LoadString (IDS_REG_UNDECK);

    VERIFY ( sVersion.LoadString ( IDS_VERSIONREGKEY ) ) ;

    CWinApp* pApp = AfxGetApp();

    pApp->WriteProfileString(sVersion, sKeyPlayerName, g_GameSettings.sPlayerName);
    pApp->WriteProfileInt(sVersion , skeyTimer, g_GameSettings.lDelayTimer);

    pApp->WriteProfileInt(sVersion , skeyAutoTer, g_GameSettings.bAutoTerminate );
    pApp->WriteProfileInt(sVersion , skeyLevel, g_GameSettings.lLevel);
    pApp->WriteProfileInt(sVersion , skeyUnDeck, g_GameSettings.bUnDecked );

    pApp->WriteProfileInt(sVersion , skeyIpremote_1, g_GameSettings.lIpRemote_1 );
    pApp->WriteProfileInt(sVersion , skeyIpremote_2, g_GameSettings.lIpRemote_2 );
    pApp->WriteProfileInt(sVersion , skeyIpremote_3, g_GameSettings.lIpRemote_3 );
    pApp->WriteProfileInt(sVersion , skeyIpremote_4, g_GameSettings.lIpRemote_4 );
}




////////////////////////////////////////
//       ExitInstance
/*! 
*/
int CClient_jpgApp::ExitInstance() 
{
	SaveSettings();
	return CWinApp::ExitInstance();
}
