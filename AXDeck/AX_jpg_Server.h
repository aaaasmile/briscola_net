

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Nov 30 23:04:02 2015
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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __AX_jpg_Server_h__
#define __AX_jpg_Server_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAxJpgCard_FWD_DEFINED__
#define __IAxJpgCard_FWD_DEFINED__
typedef interface IAxJpgCard IAxJpgCard;

#endif 	/* __IAxJpgCard_FWD_DEFINED__ */


#ifndef ___IAxJpgCardEvents_FWD_DEFINED__
#define ___IAxJpgCardEvents_FWD_DEFINED__
typedef interface _IAxJpgCardEvents _IAxJpgCardEvents;

#endif 	/* ___IAxJpgCardEvents_FWD_DEFINED__ */


#ifndef ___IAxJpgCardEventsVtbl_FWD_DEFINED__
#define ___IAxJpgCardEventsVtbl_FWD_DEFINED__
typedef interface _IAxJpgCardEventsVtbl _IAxJpgCardEventsVtbl;

#endif 	/* ___IAxJpgCardEventsVtbl_FWD_DEFINED__ */


#ifndef __AxJpgCard_FWD_DEFINED__
#define __AxJpgCard_FWD_DEFINED__

#ifdef __cplusplus
typedef class AxJpgCard AxJpgCard;
#else
typedef struct AxJpgCard AxJpgCard;
#endif /* __cplusplus */

#endif 	/* __AxJpgCard_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __AX_JPG_SERVERLib_LIBRARY_DEFINED__
#define __AX_JPG_SERVERLib_LIBRARY_DEFINED__

/* library AX_JPG_SERVERLib */
/* [helpstring][version][uuid] */ 

typedef /* [public][v1_enum] */ 
enum tagCARDSHOWSTATUS
    {
        CSW_ST_DRAWFIRST	= 0,
        CSW_ST_ANIMATETOBLACK	= ( CSW_ST_DRAWFIRST + 1 ) ,
        CSW_ST_ROTATE90	= ( CSW_ST_ANIMATETOBLACK + 1 ) ,
        CSW_ST_RESTORE	= ( CSW_ST_ROTATE90 + 1 ) ,
        CSW_ST_DRAWNORMAL	= ( CSW_ST_RESTORE + 1 ) ,
        CSW_ST_EMPTY	= ( CSW_ST_DRAWNORMAL + 1 ) ,
        CSW_ST_INVISIBLE	= ( CSW_ST_EMPTY + 1 ) ,
        CSW_ST_MAZZO	= ( CSW_ST_INVISIBLE + 1 ) ,
        CSW_ST_SELECTED1	= ( CSW_ST_MAZZO + 1 ) ,
        CSW_ST_SELECTED2	= ( CSW_ST_SELECTED1 + 1 ) 
    } 	CARDSHOWSTATUS;

typedef CARDSHOWSTATUS *LP_CARDSHOWSTATUS;


EXTERN_C const IID LIBID_AX_JPG_SERVERLib;

#ifndef __IAxJpgCard_INTERFACE_DEFINED__
#define __IAxJpgCard_INTERFACE_DEFINED__

/* interface IAxJpgCard */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAxJpgCard;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("25763CCD-4C53-11D5-A31D-00A0CC77E79C")
    IAxJpgCard : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CardIndex( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CardIndex( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CardStatus( 
            /* [retval][out] */ LP_CARDSHOWSTATUS pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CardStatus( 
            /* [in] */ LP_CARDSHOWSTATUS pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumCardOnDeck( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumCardOnDeck( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeckName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SizeImageY( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SizeImageY( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SizeImageX( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SizeImageX( 
            /* [in] */ long newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAxJpgCardVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAxJpgCard * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAxJpgCard * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAxJpgCard * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAxJpgCard * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAxJpgCard * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAxJpgCard * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAxJpgCard * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IAxJpgCard * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IAxJpgCard * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CardIndex )( 
            IAxJpgCard * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CardIndex )( 
            IAxJpgCard * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CardStatus )( 
            IAxJpgCard * This,
            /* [retval][out] */ LP_CARDSHOWSTATUS pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CardStatus )( 
            IAxJpgCard * This,
            /* [in] */ LP_CARDSHOWSTATUS pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumCardOnDeck )( 
            IAxJpgCard * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NumCardOnDeck )( 
            IAxJpgCard * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeckName )( 
            IAxJpgCard * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SizeImageY )( 
            IAxJpgCard * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SizeImageY )( 
            IAxJpgCard * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SizeImageX )( 
            IAxJpgCard * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SizeImageX )( 
            IAxJpgCard * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IAxJpgCardVtbl;

    interface IAxJpgCard
    {
        CONST_VTBL struct IAxJpgCardVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAxJpgCard_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAxJpgCard_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAxJpgCard_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAxJpgCard_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAxJpgCard_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAxJpgCard_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAxJpgCard_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAxJpgCard_put_BackColor(This,clr)	\
    ( (This)->lpVtbl -> put_BackColor(This,clr) ) 

#define IAxJpgCard_get_BackColor(This,pclr)	\
    ( (This)->lpVtbl -> get_BackColor(This,pclr) ) 

#define IAxJpgCard_get_CardIndex(This,pVal)	\
    ( (This)->lpVtbl -> get_CardIndex(This,pVal) ) 

#define IAxJpgCard_put_CardIndex(This,newVal)	\
    ( (This)->lpVtbl -> put_CardIndex(This,newVal) ) 

#define IAxJpgCard_get_CardStatus(This,pVal)	\
    ( (This)->lpVtbl -> get_CardStatus(This,pVal) ) 

#define IAxJpgCard_put_CardStatus(This,pVal)	\
    ( (This)->lpVtbl -> put_CardStatus(This,pVal) ) 

#define IAxJpgCard_get_NumCardOnDeck(This,pVal)	\
    ( (This)->lpVtbl -> get_NumCardOnDeck(This,pVal) ) 

#define IAxJpgCard_put_NumCardOnDeck(This,newVal)	\
    ( (This)->lpVtbl -> put_NumCardOnDeck(This,newVal) ) 

#define IAxJpgCard_get_DeckName(This,pVal)	\
    ( (This)->lpVtbl -> get_DeckName(This,pVal) ) 

#define IAxJpgCard_get_SizeImageY(This,pVal)	\
    ( (This)->lpVtbl -> get_SizeImageY(This,pVal) ) 

#define IAxJpgCard_put_SizeImageY(This,newVal)	\
    ( (This)->lpVtbl -> put_SizeImageY(This,newVal) ) 

#define IAxJpgCard_get_SizeImageX(This,pVal)	\
    ( (This)->lpVtbl -> get_SizeImageX(This,pVal) ) 

#define IAxJpgCard_put_SizeImageX(This,newVal)	\
    ( (This)->lpVtbl -> put_SizeImageX(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAxJpgCard_INTERFACE_DEFINED__ */


#ifndef ___IAxJpgCardEvents_DISPINTERFACE_DEFINED__
#define ___IAxJpgCardEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IAxJpgCardEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IAxJpgCardEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("25763CCF-4C53-11D5-A31D-00A0CC77E79C")
    _IAxJpgCardEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IAxJpgCardEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IAxJpgCardEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IAxJpgCardEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IAxJpgCardEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IAxJpgCardEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IAxJpgCardEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IAxJpgCardEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IAxJpgCardEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IAxJpgCardEventsVtbl;

    interface _IAxJpgCardEvents
    {
        CONST_VTBL struct _IAxJpgCardEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IAxJpgCardEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IAxJpgCardEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IAxJpgCardEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IAxJpgCardEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IAxJpgCardEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IAxJpgCardEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IAxJpgCardEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IAxJpgCardEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___IAxJpgCardEventsVtbl_INTERFACE_DEFINED__
#define ___IAxJpgCardEventsVtbl_INTERFACE_DEFINED__

/* interface _IAxJpgCardEventsVtbl */
/* [helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID__IAxJpgCardEventsVtbl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32FBD850-4F57-11d5-A3F9-0004760ECF99")
    _IAxJpgCardEventsVtbl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LMouseClick( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RMouseClick( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct _IAxJpgCardEventsVtblVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IAxJpgCardEventsVtbl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IAxJpgCardEventsVtbl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IAxJpgCardEventsVtbl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IAxJpgCardEventsVtbl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IAxJpgCardEventsVtbl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IAxJpgCardEventsVtbl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IAxJpgCardEventsVtbl * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LMouseClick )( 
            _IAxJpgCardEventsVtbl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RMouseClick )( 
            _IAxJpgCardEventsVtbl * This);
        
        END_INTERFACE
    } _IAxJpgCardEventsVtblVtbl;

    interface _IAxJpgCardEventsVtbl
    {
        CONST_VTBL struct _IAxJpgCardEventsVtblVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IAxJpgCardEventsVtbl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IAxJpgCardEventsVtbl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IAxJpgCardEventsVtbl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IAxJpgCardEventsVtbl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IAxJpgCardEventsVtbl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IAxJpgCardEventsVtbl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IAxJpgCardEventsVtbl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define _IAxJpgCardEventsVtbl_LMouseClick(This)	\
    ( (This)->lpVtbl -> LMouseClick(This) ) 

#define _IAxJpgCardEventsVtbl_RMouseClick(This)	\
    ( (This)->lpVtbl -> RMouseClick(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___IAxJpgCardEventsVtbl_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AxJpgCard;

#ifdef __cplusplus

class DECLSPEC_UUID("25763CCE-4C53-11D5-A31D-00A0CC77E79C")
AxJpgCard;
#endif
#endif /* __AX_JPG_SERVERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


