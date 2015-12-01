

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Dec 01 16:09:38 2015
 */
/* Compiler settings for AX_jpg_Server.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_AX_JPG_SERVERLib,0x25763CC1,0x4C53,0x11D5,0xA3,0x1D,0x00,0xA0,0xCC,0x77,0xE7,0x9C);


MIDL_DEFINE_GUID(IID, IID_IAxJpgCard,0x25763CCD,0x4C53,0x11D5,0xA3,0x1D,0x00,0xA0,0xCC,0x77,0xE7,0x9C);


MIDL_DEFINE_GUID(IID, DIID__IAxJpgCardEvents,0x25763CCF,0x4C53,0x11D5,0xA3,0x1D,0x00,0xA0,0xCC,0x77,0xE7,0x9C);


MIDL_DEFINE_GUID(IID, IID__IAxJpgCardEventsVtbl,0x32FBD850,0x4F57,0x11d5,0xA3,0xF9,0x00,0x04,0x76,0x0E,0xCF,0x99);


MIDL_DEFINE_GUID(CLSID, CLSID_AxJpgCard,0x25763CCE,0x4C53,0x11D5,0xA3,0x1D,0x00,0xA0,0xCC,0x77,0xE7,0x9C);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



