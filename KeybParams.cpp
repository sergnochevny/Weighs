// KeybParams.cpp : Implementation of CWeighsApp and DLL registration.

#include "stdafx.h"
#include "Weighs.h"
#include "KeybParams.h"

#include "Units.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// KeybParams

KeybParams::KeybParams() 
{
	for (int i = 0; i < 63; i++)
		m_Buff[i] = 0;
}

//==============================================================================
STDMETHODIMP KeybParams::get__NewEnum(IUnknown** pRet)
{
	if (pRet == NULL)
		return E_POINTER;
	*pRet = NULL;

	typedef CComObject<CComEnum<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT,_Copy<VARIANT> > > enumvar;

	HRESULT hRes = S_OK;
	enumvar* p = new enumvar;
	if (p == NULL)
		hRes = E_OUTOFMEMORY;
	else
	{
		hRes = p->FinalConstruct();
		if (hRes == S_OK)
		{
			hRes = p->Init(&m_Buff[0], &m_Buff[62], NULL, AtlFlagCopy);
			if (hRes == S_OK)
				hRes = p->QueryInterface(IID_IUnknown, (void**)pRet);
		}
	}
	if (hRes != S_OK)
		delete p;

	return hRes;
}

//==============================================================================
STDMETHODIMP KeybParams::get_Item(long Id, short* pRet)
{
	if (pRet == NULL)
		return E_POINTER;
	if ( (Id > 62) || (Id < 0) )
		*pRet = NULL;
 *pRet = V_UI2(&m_Buff[Id]);

  return S_OK;
}

//==============================================================================
STDMETHODIMP KeybParams::put_Item(long Id, short pValue)
{
	if ( (Id > 62) || (Id < 0) )
		return E_INVALIDARG;
  
  m_Buff[Id] = pValue;

  return S_OK;
}

//==============================================================================
STDMETHODIMP KeybParams::get_Count(int* pRet)
{
	if (pRet == NULL)
		return E_POINTER;
  *pRet = 63;

  return S_OK;
}

//==============================================================================
STDMETHODIMP KeybParams::GetData()
{
  short Buffer[63];

  ZeroMemory(Buffer, 126);

  DWORD Interm_Res = _GetKeybrdParams( Buffer );

  if ( ! ((BOOL) Interm_Res) ) 
  {
    for ( int i = 0; i < 63; i++ )
      m_Buff[i] = Buffer[i];

    return S_OK;
  }

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return E_FAIL;
}

//==============================================================================
STDMETHODIMP KeybParams::SetData()
{
  short Buffer[63];

  for ( int i = 0; i < 63; i++ )
    Buffer[i] = V_UI2(&m_Buff[i]);

  DWORD Interm_Res = _SetKeybrdParams( Buffer );

  if ( ! ((BOOL) Interm_Res) ) 
    return S_OK;

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return E_FAIL;
}