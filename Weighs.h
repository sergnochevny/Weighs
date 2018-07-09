

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Thu Apr 08 16:42:25 2004
 */
/* Compiler settings for F:\PROJECTS\PROJECTS_VC\Weighs\Weighs.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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


#ifndef __Weighs_h__
#define __Weighs_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IKeybParams_FWD_DEFINED__
#define __IKeybParams_FWD_DEFINED__
typedef interface IKeybParams IKeybParams;
#endif 	/* __IKeybParams_FWD_DEFINED__ */


#ifndef __KeybParams_FWD_DEFINED__
#define __KeybParams_FWD_DEFINED__

#ifdef __cplusplus
typedef class KeybParams KeybParams;
#else
typedef struct KeybParams KeybParams;
#endif /* __cplusplus */

#endif 	/* __KeybParams_FWD_DEFINED__ */


#ifndef __IMassaK_FWD_DEFINED__
#define __IMassaK_FWD_DEFINED__
typedef interface IMassaK IMassaK;
#endif 	/* __IMassaK_FWD_DEFINED__ */


#ifndef __MassaK_FWD_DEFINED__
#define __MassaK_FWD_DEFINED__

#ifdef __cplusplus
typedef class MassaK MassaK;
#else
typedef struct MassaK MassaK;
#endif /* __cplusplus */

#endif 	/* __MassaK_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __WEIGHS_LIBRARY_DEFINED__
#define __WEIGHS_LIBRARY_DEFINED__

/* library WEIGHS */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WEIGHS;

#ifndef __IKeybParams_INTERFACE_DEFINED__
#define __IKeybParams_INTERFACE_DEFINED__

/* interface IKeybParams */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IKeybParams;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7BBFA81D-9500-42F3-B600-95C3973E0759")
    IKeybParams : public IDispatch
    {
    public:
        virtual /* [hidden][restricted][propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pRet) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Id,
            /* [retval][out] */ short *pRet) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ long Id,
            /* [in] */ short Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ int *pRet) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetData( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetData( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IKeybParamsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IKeybParams * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IKeybParams * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IKeybParams * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IKeybParams * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IKeybParams * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IKeybParams * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IKeybParams * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [hidden][restricted][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IKeybParams * This,
            /* [retval][out] */ IUnknown **pRet);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IKeybParams * This,
            /* [in] */ long Id,
            /* [retval][out] */ short *pRet);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IKeybParams * This,
            /* [in] */ long Id,
            /* [in] */ short Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IKeybParams * This,
            /* [retval][out] */ int *pRet);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetData )( 
            IKeybParams * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetData )( 
            IKeybParams * This);
        
        END_INTERFACE
    } IKeybParamsVtbl;

    interface IKeybParams
    {
        CONST_VTBL struct IKeybParamsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IKeybParams_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IKeybParams_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IKeybParams_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IKeybParams_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IKeybParams_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IKeybParams_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IKeybParams_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IKeybParams_get__NewEnum(This,pRet)	\
    (This)->lpVtbl -> get__NewEnum(This,pRet)

#define IKeybParams_get_Item(This,Id,pRet)	\
    (This)->lpVtbl -> get_Item(This,Id,pRet)

#define IKeybParams_put_Item(This,Id,Value)	\
    (This)->lpVtbl -> put_Item(This,Id,Value)

#define IKeybParams_get_Count(This,pRet)	\
    (This)->lpVtbl -> get_Count(This,pRet)

#define IKeybParams_GetData(This)	\
    (This)->lpVtbl -> GetData(This)

#define IKeybParams_SetData(This)	\
    (This)->lpVtbl -> SetData(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][restricted][propget][id] */ HRESULT STDMETHODCALLTYPE IKeybParams_get__NewEnum_Proxy( 
    IKeybParams * This,
    /* [retval][out] */ IUnknown **pRet);


void __RPC_STUB IKeybParams_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IKeybParams_get_Item_Proxy( 
    IKeybParams * This,
    /* [in] */ long Id,
    /* [retval][out] */ short *pRet);


void __RPC_STUB IKeybParams_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IKeybParams_put_Item_Proxy( 
    IKeybParams * This,
    /* [in] */ long Id,
    /* [in] */ short Value);


void __RPC_STUB IKeybParams_put_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IKeybParams_get_Count_Proxy( 
    IKeybParams * This,
    /* [retval][out] */ int *pRet);


void __RPC_STUB IKeybParams_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IKeybParams_GetData_Proxy( 
    IKeybParams * This);


void __RPC_STUB IKeybParams_GetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IKeybParams_SetData_Proxy( 
    IKeybParams * This);


void __RPC_STUB IKeybParams_SetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IKeybParams_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_KeybParams;

#ifdef __cplusplus

class DECLSPEC_UUID("B164B866-B2B3-4FCD-BFF6-A56A091BD464")
KeybParams;
#endif

#ifndef __IMassaK_INTERFACE_DEFINED__
#define __IMassaK_INTERFACE_DEFINED__

/* interface IMassaK */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMassaK;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32BE97D0-FDEC-43F5-8AE1-40379DE148C9")
    IMassaK : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT __stdcall CreateCommunication( 
            /* [in] */ unsigned char PortNo) = 0;
        
        virtual /* [id] */ HRESULT __stdcall DestroyCommunication( void) = 0;
        
        virtual /* [id] */ HRESULT __stdcall SetLabel( 
            /* [in] */ unsigned char LabelType,
            /* [in] */ unsigned char LabelLength,
            /* [in] */ unsigned char NDepartWeight,
            /* [in] */ unsigned char NDepartPiece,
            /* [in] */ unsigned char BarCodeKind,
            /* [in] */ unsigned char SancPrnDate,
            /* [in] */ unsigned char SancPrnPrice,
            /* [in] */ BSTR PrimAdvStr,
            /* [in] */ BSTR SecAdvStr) = 0;
        
        virtual /* [id] */ HRESULT __stdcall GetLabelFormat( 
            /* [out] */ unsigned char *LabelType,
            /* [out] */ unsigned char *LabelLength) = 0;
        
        virtual /* [id] */ HRESULT __stdcall SetLabelParams( 
            /* [in] */ unsigned char NDepartWeight,
            /* [in] */ unsigned char NDepartPiece,
            /* [in] */ unsigned char BarCodeKind,
            /* [in] */ unsigned char SancPrnDate,
            /* [in] */ unsigned char SancPrnPrice,
            /* [in] */ BSTR PrimAdvStr,
            /* [in] */ BSTR SecAdvStr) = 0;
        
        virtual /* [id] */ HRESULT __stdcall GetLabelParams( 
            /* [out] */ unsigned char *NDepartWeight,
            /* [out] */ unsigned char *NDepartPiece,
            /* [out] */ unsigned char *BarCodeKind,
            /* [out] */ unsigned char *SancPrnDate,
            /* [out] */ unsigned char *SancPrnPrice,
            /* [out] */ BSTR *PrimAdvStr,
            /* [out] */ BSTR *SecAdvStr) = 0;
        
        virtual /* [id] */ HRESULT __stdcall SetArticle( 
            /* [in] */ short ArticleN,
            /* [in] */ unsigned char ArticleType,
            /* [in] */ unsigned char GroupCode,
            /* [in] */ long ArticleCode,
            /* [in] */ double Price,
            /* [in] */ short Tare,
            /* [in] */ short ShelfLife,
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [id] */ HRESULT __stdcall SetArticleD( 
            /* [in] */ short ArticleN,
            /* [in] */ unsigned char ArticleType,
            /* [in] */ unsigned char GroupCode,
            /* [in] */ long ArticleCode,
            /* [in] */ double Price,
            /* [in] */ short Tare,
            /* [in] */ DATE ShelfLife,
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [id] */ HRESULT __stdcall GetArticle( 
            /* [in] */ short ArticleN,
            /* [out] */ unsigned char *ArticleType,
            /* [out] */ unsigned char *GroupCode,
            /* [out] */ long *ArticleCode,
            /* [out] */ double *Price,
            /* [out] */ short *Tare,
            /* [out] */ long *ShelfLife,
            /* [out] */ BSTR *Name) = 0;
        
        virtual /* [id] */ HRESULT __stdcall SetArticle_AddInf( 
            /* [in] */ short ArticleN,
            /* [in] */ unsigned char StrNo,
            /* [in] */ BSTR AddInf) = 0;
        
        virtual /* [id] */ HRESULT __stdcall CleanArticle_AddInf( 
            /* [in] */ short ArticleN) = 0;
        
        virtual /* [id] */ HRESULT __stdcall GetArticle_AddInf( 
            /* [in] */ short ArticleN,
            /* [in] */ unsigned char StrNo,
            /* [out] */ BSTR *AddInf) = 0;
        
        virtual /* [id] */ HRESULT __stdcall SetKeybrdParams( 
            /* [in] */ VARIANT *KeybDat) = 0;
        
        virtual /* [id] */ HRESULT __stdcall GetKeybrdParams( 
            /* [out] */ VARIANT *KeybDat) = 0;
        
        virtual /* [id] */ HRESULT __stdcall GetWeight( 
            /* [retval][out] */ double *Value) = 0;
        
        virtual /* [id] */ HRESULT __stdcall GetTotalWeight( 
            /* [in] */ short ArticleN,
            /* [retval][out] */ double *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT __stdcall get_DevN( 
            /* [retval][out] */ unsigned char *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT __stdcall put_DevN( 
            /* [in] */ unsigned char Value) = 0;
        
        virtual /* [hidden][restricted][propget][id] */ HRESULT __stdcall get_ProtN( 
            /* [retval][out] */ unsigned char *Value) = 0;
        
        virtual /* [hidden][restricted][propput][id] */ HRESULT __stdcall put_ProtN( 
            /* [in] */ unsigned char Value) = 0;
        
        virtual /* [propget][id] */ HRESULT __stdcall get_LastError( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_KeybParams( 
            /* [retval][out] */ IKeybParams **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMassaKVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMassaK * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMassaK * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMassaK * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMassaK * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMassaK * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMassaK * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMassaK * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( __stdcall *CreateCommunication )( 
            IMassaK * This,
            /* [in] */ unsigned char PortNo);
        
        /* [id] */ HRESULT ( __stdcall *DestroyCommunication )( 
            IMassaK * This);
        
        /* [id] */ HRESULT ( __stdcall *SetLabel )( 
            IMassaK * This,
            /* [in] */ unsigned char LabelType,
            /* [in] */ unsigned char LabelLength,
            /* [in] */ unsigned char NDepartWeight,
            /* [in] */ unsigned char NDepartPiece,
            /* [in] */ unsigned char BarCodeKind,
            /* [in] */ unsigned char SancPrnDate,
            /* [in] */ unsigned char SancPrnPrice,
            /* [in] */ BSTR PrimAdvStr,
            /* [in] */ BSTR SecAdvStr);
        
        /* [id] */ HRESULT ( __stdcall *GetLabelFormat )( 
            IMassaK * This,
            /* [out] */ unsigned char *LabelType,
            /* [out] */ unsigned char *LabelLength);
        
        /* [id] */ HRESULT ( __stdcall *SetLabelParams )( 
            IMassaK * This,
            /* [in] */ unsigned char NDepartWeight,
            /* [in] */ unsigned char NDepartPiece,
            /* [in] */ unsigned char BarCodeKind,
            /* [in] */ unsigned char SancPrnDate,
            /* [in] */ unsigned char SancPrnPrice,
            /* [in] */ BSTR PrimAdvStr,
            /* [in] */ BSTR SecAdvStr);
        
        /* [id] */ HRESULT ( __stdcall *GetLabelParams )( 
            IMassaK * This,
            /* [out] */ unsigned char *NDepartWeight,
            /* [out] */ unsigned char *NDepartPiece,
            /* [out] */ unsigned char *BarCodeKind,
            /* [out] */ unsigned char *SancPrnDate,
            /* [out] */ unsigned char *SancPrnPrice,
            /* [out] */ BSTR *PrimAdvStr,
            /* [out] */ BSTR *SecAdvStr);
        
        /* [id] */ HRESULT ( __stdcall *SetArticle )( 
            IMassaK * This,
            /* [in] */ short ArticleN,
            /* [in] */ unsigned char ArticleType,
            /* [in] */ unsigned char GroupCode,
            /* [in] */ long ArticleCode,
            /* [in] */ double Price,
            /* [in] */ short Tare,
            /* [in] */ short ShelfLife,
            /* [in] */ BSTR Name);
        
        /* [id] */ HRESULT ( __stdcall *SetArticleD )( 
            IMassaK * This,
            /* [in] */ short ArticleN,
            /* [in] */ unsigned char ArticleType,
            /* [in] */ unsigned char GroupCode,
            /* [in] */ long ArticleCode,
            /* [in] */ double Price,
            /* [in] */ short Tare,
            /* [in] */ DATE ShelfLife,
            /* [in] */ BSTR Name);
        
        /* [id] */ HRESULT ( __stdcall *GetArticle )( 
            IMassaK * This,
            /* [in] */ short ArticleN,
            /* [out] */ unsigned char *ArticleType,
            /* [out] */ unsigned char *GroupCode,
            /* [out] */ long *ArticleCode,
            /* [out] */ double *Price,
            /* [out] */ short *Tare,
            /* [out] */ long *ShelfLife,
            /* [out] */ BSTR *Name);
        
        /* [id] */ HRESULT ( __stdcall *SetArticle_AddInf )( 
            IMassaK * This,
            /* [in] */ short ArticleN,
            /* [in] */ unsigned char StrNo,
            /* [in] */ BSTR AddInf);
        
        /* [id] */ HRESULT ( __stdcall *CleanArticle_AddInf )( 
            IMassaK * This,
            /* [in] */ short ArticleN);
        
        /* [id] */ HRESULT ( __stdcall *GetArticle_AddInf )( 
            IMassaK * This,
            /* [in] */ short ArticleN,
            /* [in] */ unsigned char StrNo,
            /* [out] */ BSTR *AddInf);
        
        /* [id] */ HRESULT ( __stdcall *SetKeybrdParams )( 
            IMassaK * This,
            /* [in] */ VARIANT *KeybDat);
        
        /* [id] */ HRESULT ( __stdcall *GetKeybrdParams )( 
            IMassaK * This,
            /* [out] */ VARIANT *KeybDat);
        
        /* [id] */ HRESULT ( __stdcall *GetWeight )( 
            IMassaK * This,
            /* [retval][out] */ double *Value);
        
        /* [id] */ HRESULT ( __stdcall *GetTotalWeight )( 
            IMassaK * This,
            /* [in] */ short ArticleN,
            /* [retval][out] */ double *Value);
        
        /* [propget][id] */ HRESULT ( __stdcall *get_DevN )( 
            IMassaK * This,
            /* [retval][out] */ unsigned char *Value);
        
        /* [propput][id] */ HRESULT ( __stdcall *put_DevN )( 
            IMassaK * This,
            /* [in] */ unsigned char Value);
        
        /* [hidden][restricted][propget][id] */ HRESULT ( __stdcall *get_ProtN )( 
            IMassaK * This,
            /* [retval][out] */ unsigned char *Value);
        
        /* [hidden][restricted][propput][id] */ HRESULT ( __stdcall *put_ProtN )( 
            IMassaK * This,
            /* [in] */ unsigned char Value);
        
        /* [propget][id] */ HRESULT ( __stdcall *get_LastError )( 
            IMassaK * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_KeybParams )( 
            IMassaK * This,
            /* [retval][out] */ IKeybParams **pVal);
        
        END_INTERFACE
    } IMassaKVtbl;

    interface IMassaK
    {
        CONST_VTBL struct IMassaKVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMassaK_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMassaK_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMassaK_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMassaK_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMassaK_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMassaK_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMassaK_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMassaK_CreateCommunication(This,PortNo)	\
    (This)->lpVtbl -> CreateCommunication(This,PortNo)

#define IMassaK_DestroyCommunication(This)	\
    (This)->lpVtbl -> DestroyCommunication(This)

#define IMassaK_SetLabel(This,LabelType,LabelLength,NDepartWeight,NDepartPiece,BarCodeKind,SancPrnDate,SancPrnPrice,PrimAdvStr,SecAdvStr)	\
    (This)->lpVtbl -> SetLabel(This,LabelType,LabelLength,NDepartWeight,NDepartPiece,BarCodeKind,SancPrnDate,SancPrnPrice,PrimAdvStr,SecAdvStr)

#define IMassaK_GetLabelFormat(This,LabelType,LabelLength)	\
    (This)->lpVtbl -> GetLabelFormat(This,LabelType,LabelLength)

#define IMassaK_SetLabelParams(This,NDepartWeight,NDepartPiece,BarCodeKind,SancPrnDate,SancPrnPrice,PrimAdvStr,SecAdvStr)	\
    (This)->lpVtbl -> SetLabelParams(This,NDepartWeight,NDepartPiece,BarCodeKind,SancPrnDate,SancPrnPrice,PrimAdvStr,SecAdvStr)

#define IMassaK_GetLabelParams(This,NDepartWeight,NDepartPiece,BarCodeKind,SancPrnDate,SancPrnPrice,PrimAdvStr,SecAdvStr)	\
    (This)->lpVtbl -> GetLabelParams(This,NDepartWeight,NDepartPiece,BarCodeKind,SancPrnDate,SancPrnPrice,PrimAdvStr,SecAdvStr)

#define IMassaK_SetArticle(This,ArticleN,ArticleType,GroupCode,ArticleCode,Price,Tare,ShelfLife,Name)	\
    (This)->lpVtbl -> SetArticle(This,ArticleN,ArticleType,GroupCode,ArticleCode,Price,Tare,ShelfLife,Name)

#define IMassaK_SetArticleD(This,ArticleN,ArticleType,GroupCode,ArticleCode,Price,Tare,ShelfLife,Name)	\
    (This)->lpVtbl -> SetArticleD(This,ArticleN,ArticleType,GroupCode,ArticleCode,Price,Tare,ShelfLife,Name)

#define IMassaK_GetArticle(This,ArticleN,ArticleType,GroupCode,ArticleCode,Price,Tare,ShelfLife,Name)	\
    (This)->lpVtbl -> GetArticle(This,ArticleN,ArticleType,GroupCode,ArticleCode,Price,Tare,ShelfLife,Name)

#define IMassaK_SetArticle_AddInf(This,ArticleN,StrNo,AddInf)	\
    (This)->lpVtbl -> SetArticle_AddInf(This,ArticleN,StrNo,AddInf)

#define IMassaK_CleanArticle_AddInf(This,ArticleN)	\
    (This)->lpVtbl -> CleanArticle_AddInf(This,ArticleN)

#define IMassaK_GetArticle_AddInf(This,ArticleN,StrNo,AddInf)	\
    (This)->lpVtbl -> GetArticle_AddInf(This,ArticleN,StrNo,AddInf)

#define IMassaK_SetKeybrdParams(This,KeybDat)	\
    (This)->lpVtbl -> SetKeybrdParams(This,KeybDat)

#define IMassaK_GetKeybrdParams(This,KeybDat)	\
    (This)->lpVtbl -> GetKeybrdParams(This,KeybDat)

#define IMassaK_GetWeight(This,Value)	\
    (This)->lpVtbl -> GetWeight(This,Value)

#define IMassaK_GetTotalWeight(This,ArticleN,Value)	\
    (This)->lpVtbl -> GetTotalWeight(This,ArticleN,Value)

#define IMassaK_get_DevN(This,Value)	\
    (This)->lpVtbl -> get_DevN(This,Value)

#define IMassaK_put_DevN(This,Value)	\
    (This)->lpVtbl -> put_DevN(This,Value)

#define IMassaK_get_ProtN(This,Value)	\
    (This)->lpVtbl -> get_ProtN(This,Value)

#define IMassaK_put_ProtN(This,Value)	\
    (This)->lpVtbl -> put_ProtN(This,Value)

#define IMassaK_get_LastError(This,Value)	\
    (This)->lpVtbl -> get_LastError(This,Value)

#define IMassaK_get_KeybParams(This,pVal)	\
    (This)->lpVtbl -> get_KeybParams(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT __stdcall IMassaK_CreateCommunication_Proxy( 
    IMassaK * This,
    /* [in] */ unsigned char PortNo);


void __RPC_STUB IMassaK_CreateCommunication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_DestroyCommunication_Proxy( 
    IMassaK * This);


void __RPC_STUB IMassaK_DestroyCommunication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_SetLabel_Proxy( 
    IMassaK * This,
    /* [in] */ unsigned char LabelType,
    /* [in] */ unsigned char LabelLength,
    /* [in] */ unsigned char NDepartWeight,
    /* [in] */ unsigned char NDepartPiece,
    /* [in] */ unsigned char BarCodeKind,
    /* [in] */ unsigned char SancPrnDate,
    /* [in] */ unsigned char SancPrnPrice,
    /* [in] */ BSTR PrimAdvStr,
    /* [in] */ BSTR SecAdvStr);


void __RPC_STUB IMassaK_SetLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_GetLabelFormat_Proxy( 
    IMassaK * This,
    /* [out] */ unsigned char *LabelType,
    /* [out] */ unsigned char *LabelLength);


void __RPC_STUB IMassaK_GetLabelFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_SetLabelParams_Proxy( 
    IMassaK * This,
    /* [in] */ unsigned char NDepartWeight,
    /* [in] */ unsigned char NDepartPiece,
    /* [in] */ unsigned char BarCodeKind,
    /* [in] */ unsigned char SancPrnDate,
    /* [in] */ unsigned char SancPrnPrice,
    /* [in] */ BSTR PrimAdvStr,
    /* [in] */ BSTR SecAdvStr);


void __RPC_STUB IMassaK_SetLabelParams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_GetLabelParams_Proxy( 
    IMassaK * This,
    /* [out] */ unsigned char *NDepartWeight,
    /* [out] */ unsigned char *NDepartPiece,
    /* [out] */ unsigned char *BarCodeKind,
    /* [out] */ unsigned char *SancPrnDate,
    /* [out] */ unsigned char *SancPrnPrice,
    /* [out] */ BSTR *PrimAdvStr,
    /* [out] */ BSTR *SecAdvStr);


void __RPC_STUB IMassaK_GetLabelParams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_SetArticle_Proxy( 
    IMassaK * This,
    /* [in] */ short ArticleN,
    /* [in] */ unsigned char ArticleType,
    /* [in] */ unsigned char GroupCode,
    /* [in] */ long ArticleCode,
    /* [in] */ double Price,
    /* [in] */ short Tare,
    /* [in] */ short ShelfLife,
    /* [in] */ BSTR Name);


void __RPC_STUB IMassaK_SetArticle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_SetArticleD_Proxy( 
    IMassaK * This,
    /* [in] */ short ArticleN,
    /* [in] */ unsigned char ArticleType,
    /* [in] */ unsigned char GroupCode,
    /* [in] */ long ArticleCode,
    /* [in] */ double Price,
    /* [in] */ short Tare,
    /* [in] */ DATE ShelfLife,
    /* [in] */ BSTR Name);


void __RPC_STUB IMassaK_SetArticleD_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_GetArticle_Proxy( 
    IMassaK * This,
    /* [in] */ short ArticleN,
    /* [out] */ unsigned char *ArticleType,
    /* [out] */ unsigned char *GroupCode,
    /* [out] */ long *ArticleCode,
    /* [out] */ double *Price,
    /* [out] */ short *Tare,
    /* [out] */ long *ShelfLife,
    /* [out] */ BSTR *Name);


void __RPC_STUB IMassaK_GetArticle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_SetArticle_AddInf_Proxy( 
    IMassaK * This,
    /* [in] */ short ArticleN,
    /* [in] */ unsigned char StrNo,
    /* [in] */ BSTR AddInf);


void __RPC_STUB IMassaK_SetArticle_AddInf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_CleanArticle_AddInf_Proxy( 
    IMassaK * This,
    /* [in] */ short ArticleN);


void __RPC_STUB IMassaK_CleanArticle_AddInf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_GetArticle_AddInf_Proxy( 
    IMassaK * This,
    /* [in] */ short ArticleN,
    /* [in] */ unsigned char StrNo,
    /* [out] */ BSTR *AddInf);


void __RPC_STUB IMassaK_GetArticle_AddInf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_SetKeybrdParams_Proxy( 
    IMassaK * This,
    /* [in] */ VARIANT *KeybDat);


void __RPC_STUB IMassaK_SetKeybrdParams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_GetKeybrdParams_Proxy( 
    IMassaK * This,
    /* [out] */ VARIANT *KeybDat);


void __RPC_STUB IMassaK_GetKeybrdParams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_GetWeight_Proxy( 
    IMassaK * This,
    /* [retval][out] */ double *Value);


void __RPC_STUB IMassaK_GetWeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT __stdcall IMassaK_GetTotalWeight_Proxy( 
    IMassaK * This,
    /* [in] */ short ArticleN,
    /* [retval][out] */ double *Value);


void __RPC_STUB IMassaK_GetTotalWeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT __stdcall IMassaK_get_DevN_Proxy( 
    IMassaK * This,
    /* [retval][out] */ unsigned char *Value);


void __RPC_STUB IMassaK_get_DevN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT __stdcall IMassaK_put_DevN_Proxy( 
    IMassaK * This,
    /* [in] */ unsigned char Value);


void __RPC_STUB IMassaK_put_DevN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][restricted][propget][id] */ HRESULT __stdcall IMassaK_get_ProtN_Proxy( 
    IMassaK * This,
    /* [retval][out] */ unsigned char *Value);


void __RPC_STUB IMassaK_get_ProtN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][restricted][propput][id] */ HRESULT __stdcall IMassaK_put_ProtN_Proxy( 
    IMassaK * This,
    /* [in] */ unsigned char Value);


void __RPC_STUB IMassaK_put_ProtN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT __stdcall IMassaK_get_LastError_Proxy( 
    IMassaK * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IMassaK_get_LastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IMassaK_get_KeybParams_Proxy( 
    IMassaK * This,
    /* [retval][out] */ IKeybParams **pVal);


void __RPC_STUB IMassaK_get_KeybParams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMassaK_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MassaK;

#ifdef __cplusplus

class DECLSPEC_UUID("C979F170-A46C-4DF7-A123-0A50E3CD506F")
MassaK;
#endif
#endif /* __WEIGHS_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


