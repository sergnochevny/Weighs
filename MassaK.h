// MassaK.h: Definition of the MassaK class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MASSAK_H__014328AC_3A1E_416A_9F0E_B6C79905A8E9__INCLUDED_)
#define AFX_MASSAK_H__014328AC_3A1E_416A_9F0E_B6C79905A8E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols
#include <stdlib.h>
#include <time.h>

/////////////////////////////////////////////////////////////////////////////
// MassaK

class MassaK : 
	public IDispatchImpl<IMassaK, &IID_IMassaK, &LIBID_WEIGHS>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<MassaK,&CLSID_MassaK>
{
public:
  MassaK();

BEGIN_COM_MAP(MassaK)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IMassaK)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(MassaK) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_MassaK)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMassaK
public:
	STDMETHOD(get_KeybParams)(/*[out, retval]*/ IKeybParams **pVal);

  STDMETHOD(CreateCommunication)(unsigned char PortNo);

  STDMETHOD(DestroyCommunication)();

  STDMETHOD(SetLabel)(unsigned char LabelType, 
  										unsigned char LabelLength, 
											unsigned char NDepartWeight, 
											unsigned char NDepartPiece, 
											unsigned char BarCodeKind, 
											unsigned char SancPrnDate, 
											unsigned char SancPrnPrice, 
											BSTR PrimAdvStr, 
											BSTR SecAdvStr);

  STDMETHOD(GetLabelFormat)(unsigned char * LabelType, 
  										      unsigned char * LabelLength);

  STDMETHOD(SetLabelParams)( unsigned char NDepartWeight, 
											       unsigned char NDepartPiece, 
											       unsigned char BarCodeKind, 
											       unsigned char SancPrnDate, 
											       unsigned char SancPrnPrice, 
											       BSTR PrimAdvStr, 
											       BSTR SecAdvStr);

  STDMETHOD(GetLabelParams)( unsigned char *NDepartWeight, 
											       unsigned char *NDepartPiece, 
											       unsigned char *BarCodeKind, 
											       unsigned char *SancPrnDate, 
											       unsigned char *SancPrnPrice, 
											       BSTR * PrimAdvStr, 
											       BSTR * SecAdvStr);

  STDMETHOD(SetArticle)( short ArticleN,
									       unsigned char ArticleType, 
									       unsigned char GroupCode, 
									       long ArticleCode, 
									       double Price,
									       short Tare,
									       short ShelfLife,
									       BSTR Name);

  STDMETHOD(SetArticleD)(short ArticleN,
									       unsigned char ArticleType, 
									       unsigned char GroupCode, 
									       long ArticleCode, 
									       double Price,
									       short Tare,
									       DATE ShelfLife,
									       BSTR Name);

  STDMETHOD(GetArticle)(short ArticleN,
									     unsigned char * ArticleType, 
									     unsigned char * GroupCode, 
									     long * ArticleCode, 
									     double * Price,
									     short * Tare,
									     long * ShelfLife,
									     BSTR * Name);

  STDMETHOD(SetArticle_AddInf)( short ArticleN,
	                              unsigned char StrNo,
                                BSTR AddInf);

  STDMETHOD(GetArticle_AddInf)( short ArticleN,
	                              unsigned char StrNo,
                                BSTR * AddInf);

  STDMETHOD(CleanArticle_AddInf)( short ArticleN);

  STDMETHOD(SetKeybrdParams)(VARIANT * KeybDat);

  STDMETHOD(GetKeybrdParams)(VARIANT * KeybDat);

  STDMETHOD(GetWeight)(double * Value);

  STDMETHOD(GetTotalWeight)(short ArticleN,
                            double * Value);

  STDMETHOD(get_DevN)(unsigned char * Value );

  STDMETHOD(put_DevN)(unsigned char Value );

  STDMETHOD(get_ProtN)(unsigned char * Value );

  STDMETHOD(put_ProtN)(unsigned char Value );

  STDMETHOD(get_LastError)(BSTR * Value );
};

#endif // !defined(AFX_MASSAK_H__014328AC_3A1E_416A_9F0E_B6C79905A8E9__INCLUDED_)
