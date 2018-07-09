

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


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

MIDL_DEFINE_GUID(IID, LIBID_WEIGHS,0x56E8B452,0xB586,0x44B7,0x94,0x10,0x96,0x18,0x1D,0x25,0xBE,0xCB);


MIDL_DEFINE_GUID(IID, IID_IKeybParams,0x7BBFA81D,0x9500,0x42F3,0xB6,0x00,0x95,0xC3,0x97,0x3E,0x07,0x59);


MIDL_DEFINE_GUID(CLSID, CLSID_KeybParams,0xB164B866,0xB2B3,0x4FCD,0xBF,0xF6,0xA5,0x6A,0x09,0x1B,0xD4,0x64);


MIDL_DEFINE_GUID(IID, IID_IMassaK,0x32BE97D0,0xFDEC,0x43F5,0x8A,0xE1,0x40,0x37,0x9D,0xE1,0x48,0xC9);


MIDL_DEFINE_GUID(CLSID, CLSID_MassaK,0xC979F170,0xA46C,0x4DF7,0xA1,0x23,0x0A,0x50,0xE3,0xCD,0x50,0x6F);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/



/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Thu Apr 08 16:42:25 2004
 */
/* Compiler settings for F:\PROJECTS\PROJECTS_VC\Weighs\Weighs.idl:
    Oicf, W1, Zp8, env=Win64 (32b run,appending)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if defined(_M_IA64) || defined(_M_AMD64)


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

MIDL_DEFINE_GUID(IID, LIBID_WEIGHS,0x56E8B452,0xB586,0x44B7,0x94,0x10,0x96,0x18,0x1D,0x25,0xBE,0xCB);


MIDL_DEFINE_GUID(IID, IID_IKeybParams,0x7BBFA81D,0x9500,0x42F3,0xB6,0x00,0x95,0xC3,0x97,0x3E,0x07,0x59);


MIDL_DEFINE_GUID(CLSID, CLSID_KeybParams,0xB164B866,0xB2B3,0x4FCD,0xBF,0xF6,0xA5,0x6A,0x09,0x1B,0xD4,0x64);


MIDL_DEFINE_GUID(IID, IID_IMassaK,0x32BE97D0,0xFDEC,0x43F5,0x8A,0xE1,0x40,0x37,0x9D,0xE1,0x48,0xC9);


MIDL_DEFINE_GUID(CLSID, CLSID_MassaK,0xC979F170,0xA46C,0x4DF7,0xA1,0x23,0x0A,0x50,0xE3,0xCD,0x50,0x6F);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* defined(_M_IA64) || defined(_M_AMD64)*/

