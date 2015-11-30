========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : Client_jpg
========================================================================


AppWizard has created this Client_jpg application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your Client_jpg application.

Client_jpg.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

Client_jpg.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CClient_jpgApp application class.

Client_jpg.cpp
    This is the main application source file that contains the application
    class CClient_jpgApp.

Client_jpg.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Visual C++.

Client_jpg.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

res\Client_jpg.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file Client_jpg.rc.

res\Client_jpg.rc2
    This file contains resources that are not edited by Microsoft 
	Visual C++.  You should place all resources not editable by
	the resource editor in this file.




/////////////////////////////////////////////////////////////////////////////

AppWizard creates one dialog class:

Client_jpgDlg.h, Client_jpgDlg.cpp - the dialog
    These files contain your CClient_jpgDlg class.  This class defines
    the behavior of your application's main dialog.  The dialog's
    template is in Client_jpg.rc, which can be edited in Microsoft
	Visual C++.


/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Client_jpg.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is 
in a language other than the operating system's current language, you
will need to copy the corresponding localized resources MFC42XXX.DLL
from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
For example, MFC42DEU.DLL contains resources translated to German.)  If you
don't do this, some of the UI elements of your application will remain in the
language of the operating system.

/////////////////////////////////////////////////////////////////////////////

//******************************************************************************
//Dialog that works with jpg images
//******************************************************************************

/////////////////////////////////////////////////////////////////////////////
//
// Dialog
//

IDD_CLIENT_JPG_DIALOG DIALOGEX 0, 0, 367, 387
STYLE DS_MODALFRAME | WS_MINIMIZEBOX | WS_POPUP | WS_VISIBLE | WS_CAPTION | 
    WS_SYSMENU
EXSTYLE WS_EX_APPWINDOW
CAPTION "Briscola_net"
FONT 8, "MS Sans Serif"
BEGIN
    DEFPUSHBUTTON   "Fine",IDOK,310,7,50,14
    CONTROL         "",IDC_MYCARD1,"{25763CCE-4C53-11D5-A31D-00A0CC77E79C}",
                    WS_TABSTOP,7,257,68,116
    CONTROL         "",IDC_MYCARD2,"{25763CCE-4C53-11D5-A31D-00A0CC77E79C}",
                    WS_TABSTOP,89,257,68,116
    CONTROL         "",IDC_MYCARD3,"{25763CCE-4C53-11D5-A31D-00A0CC77E79C}",
                    WS_TABSTOP,171,257,68,116
    CONTROL         "",IDC_OPPONENT1,"{25763CCE-4C53-11D5-A31D-00A0CC77E79C}",
                    WS_TABSTOP,7,7,48,80
    CONTROL         "",IDC_OPPONENT2,"{25763CCE-4C53-11D5-A31D-00A0CC77E79C}",
                    WS_TABSTOP,63,7,48,80
    CONTROL         "",IDC_OPPONENT3,"{25763CCE-4C53-11D5-A31D-00A0CC77E79C}",
                    WS_TABSTOP,118,7,48,80
    CONTROL         "",IDC_MAZZOCOP,"{25763CCE-4C53-11D5-A31D-00A0CC77E79C}",
                    WS_TABSTOP,7,107,68,123
    CONTROL         "",IDC_CARTAINTAVOLA,
                    "{25763CCE-4C53-11D5-A31D-00A0CC77E79C}",WS_TABSTOP,35,
                    139,111,57
    CONTROL         "",IDC_PLAYEDSECOND,
                    "{25763CCE-4C53-11D5-A31D-00A0CC77E79C}",WS_TABSTOP,200,
                    123,68,116
    CONTROL         "",IDC_PLAYEDFIRST,
                    "{25763CCE-4C53-11D5-A31D-00A0CC77E79C}",WS_TABSTOP,173,
                    102,68,116
    PUSHBUTTON      "Nuova Partita",IDC_NEWGAME,310,285,50,14
    PUSHBUTTON      "Conta",IDC_CONTA_PT_PLAYER,310,359,50,14
    PUSHBUTTON      "Briscola?",IDC_WHAT_BRISCOLA,310,332,50,14
    CONTROL         "",IDC_MYCARD_TAKEN,
                    "{25763CCE-4C53-11D5-A31D-00A0CC77E79C}",WS_TABSTOP,253,
                    317,31,56
    CONTROL         "",IDC_OPPONENT_TAKEN,
                    "{25763CCE-4C53-11D5-A31D-00A0CC77E79C}",WS_TABSTOP,253,
                    7,31,56
    PUSHBUTTON      "Rete...",IDC_BT_NETWORK,310,314,50,14
    LTEXT           "",IDC_HTMLINTRO,70,133,227,121
    LTEXT           "Scegli",IDC_STATUS,291,32,69,24
    LTEXT           "Static",IDC_ST_NAME_ME,247,285,51,8
    LTEXT           "Static",IDC_ST_NAME_OPP,172,7,71,8
    LTEXT           "tipo gioco",IDC_ST_TIPOGIOCO,291,59,69,9
    LTEXT           "tocca a te",IDC_ST_ACHITOCCA,291,77,69,9
END

/////////////////////////////////////////////////////////////////////////////
//
// Dialog Info
//

IDD_CLIENT_JPG_DIALOG DLGINIT
BEGIN
    IDC_MYCARD1, 0x376, 22, 0
0x0000, 0x0000, 0x0300, 0x0000, 0x0b3f, 0x0000, 0x132f, 0x0000, 0x0013, 
0x0000, 0x0000, 
    IDC_MYCARD2, 0x376, 22, 0
0x0000, 0x0000, 0x0300, 0x0000, 0x0b3f, 0x0000, 0x132f, 0x0000, 0x0013, 
0x0000, 0x0000, 
    IDC_MYCARD3, 0x376, 22, 0
0x0000, 0x0000, 0x0300, 0x0000, 0x0b3f, 0x0000, 0x132f, 0x0000, 0x0013, 
0x0000, 0x0000, 
    IDC_OPPONENT1, 0x376, 22, 0
0x0000, 0x0000, 0x0300, 0x0000, 0x07f0, 0x0000, 0x0d3b, 0x0000, 0x0013, 
0x0000, 0x0000, 
    IDC_OPPONENT2, 0x376, 22, 0
0x0000, 0x0000, 0x0300, 0x0000, 0x07f0, 0x0000, 0x0d3b, 0x0000, 0x0013, 
0x0000, 0x0000, 
    IDC_OPPONENT3, 0x376, 22, 0
0x0000, 0x0000, 0x0300, 0x0000, 0x07f0, 0x0000, 0x0d3b, 0x0000, 0x0013, 
0x0000, 0x0000, 
    IDC_MAZZOCOP, 0x376, 22, 0
0x0000, 0x0000, 0x0300, 0x0000, 0x0b3f, 0x0000, 0x1457, 0x0000, 0x0013, 
0x0000, 0x0000, 
    IDC_CARTAINTAVOLA, 0x376, 22, 0
0x0000, 0x0000, 0x0300, 0x0000, 0x125b, 0x0000, 0x096d, 0x0000, 0x0013, 
0x0000, 0x0000, 
    IDC_PLAYEDSECOND, 0x376, 22, 0
0x0000, 0x0000, 0x0300, 0x0000, 0x0b3f, 0x0000, 0x132f, 0x0000, 0x0013, 
0x0000, 0x0000, 
    IDC_PLAYEDFIRST, 0x376, 22, 0
0x0000, 0x0000, 0x0300, 0x0000, 0x0b3f, 0x0000, 0x132f, 0x0000, 0x0013, 
0x0000, 0x0000, 
    IDC_MYCARD_TAKEN, 0x376, 22, 0
0x0000, 0x0000, 0x0300, 0x0000, 0x0520, 0x0000, 0x0943, 0x0000, 0x0013, 
0x0000, 0x0000, 
    IDC_OPPONENT_TAKEN, 0x376, 22, 0
0x0000, 0x0000, 0x0300, 0x0000, 0x0520, 0x0000, 0x0943, 0x0000, 0x0013, 
0x0000, 0x0000, 
    0
END

//******************************************************************************
//Dialog without images (test simple)
//******************************************************************************
/////////////////////////////////////////////////////////////////////////////
//
// Dialog
//

IDD_CLIENT_JPG_DIALOG DIALOGEX 0, 0, 201, 235
STYLE DS_MODALFRAME | WS_MINIMIZEBOX | WS_POPUP | WS_VISIBLE | WS_CAPTION | 
    WS_SYSMENU
EXSTYLE WS_EX_APPWINDOW
CAPTION "socket test"
FONT 8, "MS Sans Serif"
BEGIN
    DEFPUSHBUTTON   "End",IDOK,125,125,50,14
    PUSHBUTTON      "New",IDC_NEWGAME,125,145,50,14
    PUSHBUTTON      "how",IDC_CONTA_PT_PLAYER,125,205,50,14
    PUSHBUTTON      "brisc",IDC_WHAT_BRISCOLA,125,185,50,14
    PUSHBUTTON      "Net...",IDC_BT_NETWORK,125,165,50,14
    LTEXT           "",IDC_HTMLINTRO,20,75,80,50
    LTEXT           "Scegli",IDC_STATUS,125,30,69,24
    LTEXT           "Static",IDC_ST_NAME_ME,25,190,51,8
    LTEXT           "Static",IDC_ST_NAME_OPP,130,5,71,8
    LTEXT           "tipo gioco",IDC_ST_TIPOGIOCO,125,65,69,9
    LTEXT           "tocca a te",IDC_ST_ACHITOCCA,125,100,69,9
    PUSHBUTTON      "1",IDC_BT_TESTCARD1,7,156,19,15
    PUSHBUTTON      "2",IDC_BT_TESTCARD2,30,156,19,15
    PUSHBUTTON      "3",IDC_BT_TESTCARD3,55,156,19,15
END