// AX_jpg_Server.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f AX_jpg_Serverps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "AX_jpg_Server.h"

#include "AX_jpg_Server_i.c"
#include "AxJpgCard.h"
#include "JpgLoader.h"


LPPICTURE g_ImageHandle[CS_MAXINDEX];

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_AxJpgCard, CAxJpgCard)
END_OBJECT_MAP()

static void LoadAllImages(HINSTANCE hInstance)
{
    cJpgLoader cLoader;

    cLoader.LoadImageFromResource(IDR_JPG00, &g_ImageHandle[0], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG01, &g_ImageHandle[1], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG02, &g_ImageHandle[2], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG03, &g_ImageHandle[3], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG04, &g_ImageHandle[4], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG05, &g_ImageHandle[5], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG06, &g_ImageHandle[6], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG07, &g_ImageHandle[7], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG08, &g_ImageHandle[8], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG09, &g_ImageHandle[9], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG10, &g_ImageHandle[10], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG11, &g_ImageHandle[11], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG12, &g_ImageHandle[12], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG13, &g_ImageHandle[13], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG14, &g_ImageHandle[14], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG15, &g_ImageHandle[15], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG16, &g_ImageHandle[16], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG17, &g_ImageHandle[17], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG18, &g_ImageHandle[18], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG19, &g_ImageHandle[19], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG20, &g_ImageHandle[20], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG21, &g_ImageHandle[21], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG22, &g_ImageHandle[22], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG23, &g_ImageHandle[23], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG24, &g_ImageHandle[24], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG25, &g_ImageHandle[25], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG26, &g_ImageHandle[26], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG27, &g_ImageHandle[27], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG28, &g_ImageHandle[28], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG29, &g_ImageHandle[29], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG30, &g_ImageHandle[30], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG31, &g_ImageHandle[31], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG32, &g_ImageHandle[32], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG33, &g_ImageHandle[33], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG34, &g_ImageHandle[34], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG35, &g_ImageHandle[35], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG36, &g_ImageHandle[36], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG37, &g_ImageHandle[37], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG38, &g_ImageHandle[38], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG39, &g_ImageHandle[39], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG40, &g_ImageHandle[40], hInstance);
    cLoader.LoadImageFromResource(IDR_JPG41, &g_ImageHandle[41], hInstance);

    
    //cLoader.LoadPictureFile("G:\\Projects\\AXcards\\AX_jpg_Server\\res\\1_bastoni_300.jpg", &g_ImageHandle[0]);
    
}

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_AX_JPG_SERVERLib);
        DisableThreadLibraryCalls(hInstance);
        LoadAllImages(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}


