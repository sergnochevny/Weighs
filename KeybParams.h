// KeybParams.h: Definition of the KeybParams class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYBPARAMS_H__B74AF011_00E6_43DD_A43A_D3C559FC6E99__INCLUDED_)
#define AFX_KEYBPARAMS_H__B74AF011_00E6_43DD_A43A_D3C559FC6E99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// KeybParams

class KeybParams : 
	public IDispatchImpl<IKeybParams, &IID_IKeybParams, &LIBID_WEIGHS>, 
	public CComObjectRoot,
	public CComCoClass<KeybParams,&CLSID_KeybParams>
{
public:
  KeybParams();

BEGIN_COM_MAP(KeybParams)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IKeybParams)
END_COM_MAP()
DECLARE_NOT_AGGREGATABLE(KeybParams) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_KeybParams)

// IKeybParams
public:
  STDMETHOD(get__NewEnum)(IUnknown** pRet);
  STDMETHOD(get_Item)(long Id, short* pRet);
  STDMETHOD(put_Item)(long Id, short Value);
  STDMETHOD(get_Count)(int* pRet);
  STDMETHOD(GetData)();
  STDMETHOD(SetData)();

private:
  CComVariant m_Buff[63];

};

#endif // !defined(AFX_KEYBPARAMS_H__B74AF011_00E6_43DD_A43A_D3C559FC6E99__INCLUDED_)
