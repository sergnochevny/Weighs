// MassaK.cpp : Implementation of CWeighsApp and DLL registration.

#include "stdafx.h"
#include "Weighs.h"
#include "MassaK.h"
#include "Units.h"          // main symbols

#include <string.h>
#include <time.h>
/////////////////////////////////////////////////////////////////////////////
//

static unsigned char ProtocolsSupported [] = {0,1};

HANDLE hPortHandle;
DCB aDCB;

bool Silent, ProcessOEMCP;

BYTE ProtocolNo = 0x00, DevNo = 0x00, PortNo;
BYTE LblType = 0x00;
BYTE LblLength = 0x000;

BSTR Error_Str = NULL;

/*******************************************************************}
{                       Internal routines                           }
{*******************************************************************/

//==============================================================================
UINT STDMETHODCALLTYPE 
OemToTranslit(DWORD Src, DWORD Dest, DWORD Size)
{
	for(UINT i=0; i<Size && *(BYTE *)(Src + i) != 0x00; i++)
	{
		*(BYTE *)(Dest + i) = 
			* (BYTE *)(TranslCharOEM + *(BYTE *)(Src + i));
	}

  return ( i );
}

//==============================================================================
UINT STDMETHODCALLTYPE 
AnsiToTranslit(DWORD Src, DWORD Dest, DWORD Size)
{
	for(UINT i=0; i<Size && *(BYTE *)(Src + i) != 0x00; i++)
	{
		*(BYTE *)(Dest + i) = 
			*(BYTE *)(TranslCharANSI + *(BYTE *)(Src + i));
	}

  return ( i );
}

//==============================================================================
UINT STDMETHODCALLTYPE 
TranslitToAnsi(DWORD Src, DWORD Dest, DWORD Size)
{
	for(UINT i=0; i<Size && *(BYTE *)(Src + i) != 0x00; i++)
	{
		*(BYTE *)(Dest + i) = 
			*(BYTE *)(TranslCharBackANSI + *(BYTE *)(Src + i));
	}

  return ( i );
}

//==============================================================================
void STDMETHODCALLTYPE 
CopyString(char *Src, char *Dest, DWORD Size)
{
  
  if ( ProcessOEMCP )
    AnsiToTranslit( (DWORD) Src, (DWORD) Dest, Size);
  else 
    OemToTranslit( (DWORD) Src, (DWORD) Dest, Size);

}

//==============================================================================
BOOL STDMETHODCALLTYPE 
ReadFile_(
  HANDLE hFile,                
  LPVOID lpBuffer,             
  DWORD nNumberOfBytesToRead,  
  LPDWORD lpNumberOfBytesRead, 
  LPOVERLAPPED lpOverlapped)
{
  DWORD lpEvtMask;
 
  ::WaitCommEvent(hFile, &lpEvtMask, NULL);

  return ::ReadFile(hFile, lpBuffer, nNumberOfBytesToRead,
                     lpNumberOfBytesRead, lpOverlapped);
}

//_________________________Auxiliary routines________________________

//==============================================================================
DWORD STDMETHODCALLTYPE 
DecodeInt(DWORD *arg)
{
  DWORD ret = *arg & 0XFFFFFF;

  if (ret & 0x800000) 
    ret = ret ^ 0xFFFFFFFF;

  return ret;

}

//==============================================================================
void STDMETHODCALLTYPE 
ShowErrorMsg(DWORD ErrCode, DWORD WinErrCode)
{
  char MsgBuff[256];
  DWORD lpMsgBuff;
  
  int BuffLen=::LoadString(_Module.m_hInst, ErrCode, MsgBuff, 100);

  if ( (WinErrCode !=0) && BuffLen )
  {
    lpMsgBuff=((DWORD) MsgBuff)+BuffLen;

    *(WORD *)lpMsgBuff = 0x0D0A; lpMsgBuff = lpMsgBuff + 2;
    //   (BYTE) *lpMsgBuff=0X0; lpMsgBuff++;

    ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 
                   NULL, 
                   WinErrCode,
				           0, 
                   (LPSTR) lpMsgBuff, 
                   100, 
                   NULL);
  }

  ::MessageBox(0, (LPCTSTR) MsgBuff, NULL, MB_TASKMODAL | MB_OK | MB_ICONERROR);
}

//==============================================================================

void STDMETHODCALLTYPE 
GetErrorMsg(DWORD ErrCode, DWORD WinErrCode)
{

  char MsgBuff[256];
  DWORD lpMsgBuff;
  
  int BuffLen = ::LoadString(_Module.m_hInst, ErrCode, MsgBuff, 100);
  
  if ((WinErrCode !=0) && BuffLen)
  {
    lpMsgBuff=((DWORD) MsgBuff)+BuffLen;

    *(WORD *)lpMsgBuff = 0x0D0A; lpMsgBuff = lpMsgBuff + 2;
    //   (BYTE) *lpMsgBuff=0X0; lpMsgBuff++;

    ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 
                   NULL, 
                   WinErrCode,
				           0, 
                   (LPSTR) lpMsgBuff, 
                   100, 
                   NULL);
  }

  char *_Error_Str = (char *) alloca(strlen(MsgBuff)+1);
  ZeroMemory( _Error_Str, strlen(MsgBuff)+1 );
  memcpy(_Error_Str, MsgBuff, strlen(MsgBuff));

  Error_Str = A2BSTR( _Error_Str );
}

//==============================================================================
bool STDMETHODCALLTYPE 
ClosePort(void)
{
  bool Result = true;

  if ((hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle)
  {
    if (::CloseHandle(hPortHandle)) 
      hPortHandle = 0; 
    else 
      Result = false;
  }

  return ( Result );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
ConfigPort( CStage Stage )
{ 
  switch (Stage) 
  {
    case stc_Init:
      
      if ( ::GetCommState(hPortHandle, &aDCB) )
      {
        aDCB.BaudRate = CBR_9600;
        aDCB.ByteSize = 8;
        aDCB.StopBits = ONESTOPBIT;

        if (ProtocolNo) 
          aDCB.Parity = MARKPARITY;
        else 
          aDCB.Parity = NOPARITY;

        COMMTIMEOUTS aCommTimeouts;

        aCommTimeouts.ReadTotalTimeoutMultiplier = tcReadTotalTimeoutMultiplier;
        aCommTimeouts.ReadIntervalTimeout = tcReadIntervalTimeout;
        aCommTimeouts.ReadTotalTimeoutConstant = tcReadTotalTimeoutConstant;
        aCommTimeouts.WriteTotalTimeoutMultiplier = tcWriteTotalTimeoutMultiplier;
        aCommTimeouts.WriteTotalTimeoutConstant = tcWriteTotalTimeoutConstant;

        if ( !::SetCommTimeouts(hPortHandle, &aCommTimeouts) )
          return ( FALSE );

       }
       else 
        return ( FALSE );
      
      break;

    case stc_9bit:

      aDCB.Parity = MARKPARITY;
      break;

    case stc_8bit: 

      aDCB.Parity = SPACEPARITY;
      break;

  }

  return ::SetCommState(hPortHandle, &aDCB);
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
SynchronizeDevice( void ) 
{

  TCommBufferTiny InBuffer;
  DWORD BytesIn, BytesOut;

  BOOL Success = ::WriteFile(hPortHandle, &DevNo, 1, &BytesOut, NULL) &&
                ReadFile_(hPortHandle, InBuffer, 1, &BytesIn, NULL);

  return (Success & (BytesIn == 1) & ( (BYTE) InBuffer[0] == 0x77 ));

}

//==============================================================================
BOOL STDMETHODCALLTYPE 
SynchronizeDeviceNoWait( void ) 
{

  TCommBufferTiny InBuffer;
  DWORD BytesIn, BytesOut;

  BOOL Success = ::WriteFile(hPortHandle, &DevNo, 1, &BytesOut, NULL) &
                ::ReadFile(hPortHandle, InBuffer, 1, &BytesIn, NULL);

  return (Success & (BytesIn == 1) & ( (BYTE) InBuffer[0] == 0x77 ));

}

//==============================================================================
BOOL STDMETHODCALLTYPE 
WriteCommand( BYTE Code)
{

  TCommBufferTiny InBuffer;
  DWORD BytesIn, BytesOut;

  BOOL Success = ::WriteFile(hPortHandle, &Code, 1, &BytesOut, NULL) &
                ReadFile_(hPortHandle, InBuffer, 1, &BytesIn, NULL);

  return (Success & (BytesIn == 1) & ( (BYTE) InBuffer[0] == 0x01 ));

}

//==============================================================================
BOOL STDMETHODCALLTYPE 
WriteArticleCommand( WORD ArticleNo, BYTE Code)
{

  TCommBufferTiny InBuffer;
  DWORD BytesIn, BytesOut;

  BOOL Success = ::WriteFile(hPortHandle, &ArticleNo, 2, &BytesOut, NULL) &
                 ::WriteFile(hPortHandle, &Code, 1, &BytesOut, NULL) &
                 ReadFile_(hPortHandle, InBuffer, 1, &BytesIn, NULL);

  return (Success & (BytesIn == 1) & ( (BYTE) InBuffer[0] == 0x01 ));

}

//==============================================================================
BOOL STDMETHODCALLTYPE 
InitMDevice(DWORD aPortNo, bool aSilent, bool aProcessOEMCP)
{
 
  DWORD Result;
  
  Silent = aSilent;

  PortNo = (BYTE) (aPortNo & 0xFF);
  ProcessOEMCP = aProcessOEMCP;
  
  char szPort[ 15 ];
  wsprintf( szPort, "COM%d", aPortNo);

  HANDLE TempHandle = ::CreateFile( szPort, 
                GENERIC_READ | GENERIC_WRITE,
                0,                    // exclusive access
                NULL,                 // no security attrs
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL );

  if ( (TempHandle != INVALID_HANDLE_VALUE) && TempHandle )
  {

    hPortHandle = TempHandle;

    if ( ConfigPort(stc_Init) )
    {
      
      if ( SynchronizeDeviceNoWait() )
      {

        // get any early notifications
        ::SetCommMask( hPortHandle, EV_RXCHAR ) ;
        // setup device buffers
        ::SetupComm( hPortHandle, 256, 256) ;
        // purge any information in the buffer
        ::PurgeComm( hPortHandle, PURGE_TXABORT || PURGE_RXABORT ||
                                  PURGE_TXCLEAR || PURGE_RXCLEAR ) ;
        Result = erc_OK;

      } else {
        
        ClosePort();
        Result = erc_WrongDevice;
      }
    } else {
     
     ClosePort();
     Result = erc_PortConfigFail;

    }
  } else 
    Result = erc_PortOpenFail;

  return ( Result );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
ResetMDevice( void )
{
  BOOL Result;

  if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle )
  {
  
    if ( ClosePort() )
      Result = InitMDevice(PortNo, Silent, ProcessOEMCP);
    else 
      Result = erc_PortCloseFail;
  } 
  else 
    Result = erc_NoDevice;

  return ( Result );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
CloseMDevice( void )
{
  if ((hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle)
  {
    // disable event notification and wait for thread to halt
    ::SetCommMask(hPortHandle, 0 ) ;
    // drop DTR and RTS
    ::EscapeCommFunction(hPortHandle, CLRDTR || CLRRTS);
   // purge any outstanding reads/writes
    ::PurgeComm(hPortHandle, 
              PURGE_TXABORT || PURGE_RXABORT ||
              PURGE_TXCLEAR || PURGE_RXCLEAR ) ;
  }

  BOOL Result;

  if (ClosePort()) 
    Result = erc_OK;
  else
    Result = erc_PortCloseFail;

  return ( Result );
}


/*******************************************************************}
{                        Device routines                            }
{*******************************************************************/

//==============================================================================
DWORD STDMETHODCALLTYPE 
_SetLabelFormat( BYTE LabelType, BYTE LabelLength)
{

  TCommBufferTiny CommBuffer;
  DWORD BytesIn, Result;
  bool Success;

  if ( ( (int) LabelType >= 0) && ( (int) LabelType <= 4) && 
      (LabelLength % 10 == 0) && ( LabelLength >= SupportedLabelFormats[LabelType][0]) &&
      (LabelLength <= SupportedLabelFormats[LabelType][1]) )
  {

    CommBuffer[0] = LabelType; 
    CommBuffer[1] = LabelLength;
    LblType = LabelType;
    LblLength = LabelLength;

    if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle )
      if (ConfigPort(stc_9bit) )
        if ( SynchronizeDevice() )
          if ( ConfigPort(stc_8bit) )
            if ( WriteCommand(ccSetLabelFormat) )
            {
              Success = ::WriteFile(hPortHandle, CommBuffer, 2, &BytesIn, NULL) &&
                        ReadFile_(hPortHandle, CommBuffer, 1, &BytesIn, NULL);

              if ( Success && (BytesIn == 1) && ( (BYTE) CommBuffer[0] == 0x10) )
                Result = erc_OK;
              else Result = erc_UnknownError;

            } else Result = erc_DeviceNotReady;
          else Result = erc_PortConfigFail;
        else Result = erc_WrongDevice;
      else Result = erc_PortConfigFail;
    else Result = erc_NoDevice;

  } else Result = erc_WrongParams;

  return ( Result );
}

//==============================================================================
DWORD STDMETHODCALLTYPE 
_GetLabelFormat(BYTE *LabelType,
						    BYTE *LabelLength)
{

  TCommBufferTiny InBuffer;
  DWORD BytesIn, Result;
  BOOL Success;

  if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle )
    if (ConfigPort(stc_9bit) )
      if ( SynchronizeDevice() )
        if ( ConfigPort(stc_8bit) )
          if ( WriteCommand(ccGetLabelFormat) )
          {
            Success = ::ReadFile(hPortHandle, InBuffer, 3, &BytesIn, NULL);
            if ( Success && (BytesIn == 3) && ((BYTE) InBuffer[2] == 0x10) )
            {
              *LabelType = (BYTE) InBuffer[0];
              *LabelLength = (BYTE) InBuffer[1];
              Result = erc_OK;

            } else Result = erc_UnknownError;
          } else Result = erc_DeviceNotReady;
        else Result = erc_PortConfigFail;
      else Result = erc_WrongDevice;
    else Result = erc_PortConfigFail;
  else Result = erc_NoDevice;

  return ( Result );

}

//==============================================================================
DWORD STDMETHODCALLTYPE 
_SetLabelParams(
                BYTE NDepartWeight, 
                BYTE NDepartPiece, 
                BYTE BarCodeKind,
                BYTE SancPrnDate, 
                BYTE SancPrnPrice,
                char *PrimStrAdvertis, 
                char *SecondStrAdvertis)
{
  BYTE Byte_Tag = 0x01;

  TCommBufferBig WriteBuffer;
  TCommBufferTiny ReadBuffer;
  DWORD BytesIn;
  bool Success;

  DWORD Result;

  ZeroMemory(WriteBuffer, 120);
  ZeroMemory(ReadBuffer, 5);

  if ( SancPrnDate ) memcpy(&WriteBuffer[3], &Byte_Tag, 1);
  if ( SancPrnPrice ) memcpy(&WriteBuffer[4], &Byte_Tag, 1);

  if ( ((BOOL) (strlen(PrimStrAdvertis) || strlen(SecondStrAdvertis))) 
       && (BarCodeKind < 12) )
  {
    memcpy(&WriteBuffer[0], &NDepartWeight, 1);
    memcpy(&WriteBuffer[1], &NDepartPiece, 1);
    memcpy(&WriteBuffer[2], &BarCodeKind, 1);

    if ( (BOOL) strlen(PrimStrAdvertis) )
    {
      if ( strlen(PrimStrAdvertis) < 25) 
        CopyString(PrimStrAdvertis, &WriteBuffer[10], strlen(PrimStrAdvertis));
      else
        CopyString(PrimStrAdvertis, &WriteBuffer[10], 24);
    }

    if ( (BOOL) strlen(SecondStrAdvertis) )
    {
      if ( strlen(SecondStrAdvertis) < 25) 
        CopyString(SecondStrAdvertis, &WriteBuffer[34], strlen(SecondStrAdvertis));
      else
        CopyString(SecondStrAdvertis, &WriteBuffer[34], 24);
    }

    if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle )
      if (ConfigPort(stc_9bit) )
        if ( SynchronizeDevice() )
          if ( ConfigPort(stc_8bit) )
            if ( WriteCommand(ccSetLabelParams) )
            {
              Success = ::WriteFile(hPortHandle, WriteBuffer, 106, &BytesIn, NULL) &&
                        ReadFile_(hPortHandle, ReadBuffer, 1, &BytesIn, NULL);

              if ( Success && (BytesIn == 1) && ( (BYTE) ReadBuffer[0] == 0x10) )
                Result = erc_OK;
              else Result = erc_UnknownError;

            } else Result = erc_DeviceNotReady;
          else Result = erc_PortConfigFail;
        else Result = erc_WrongDevice;
      else Result = erc_PortConfigFail;
    else Result = erc_NoDevice;

  } else Result = erc_WrongParams;

  return ( Result );
}

//==============================================================================
DWORD STDMETHODCALLTYPE 
_GetLabelParams( OUT BYTE *NDepartWeight, 
                OUT BYTE *NDepartPiece, 
                OUT BYTE *BarCodeKind,
                OUT BYTE *SancPrnDate, 
                OUT BYTE *SancPrnPrice,
                OUT BSTR *PrimStrAdvertis, 
                OUT BSTR *SecondStrAdvertis)

{

  TCommBufferBig InBuffer;
  DWORD BytesIn, Result;
  BOOL Success;

  ZeroMemory(InBuffer, 110);

  if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle )
    if (ConfigPort(stc_9bit) )
      if ( SynchronizeDevice() )
        if ( ConfigPort(stc_8bit) )
          if ( WriteCommand(ccGetLabelParams) )
          {
            Success = ::ReadFile(hPortHandle, InBuffer, 107, &BytesIn, NULL);
            if ( Success && (BytesIn == 107) && ( (BYTE) InBuffer[106] == 0x10) )
            {
              *NDepartWeight = (BYTE) InBuffer[0];
              *NDepartPiece = (BYTE) InBuffer[1];
              *BarCodeKind = (BYTE) InBuffer[2];
              *SancPrnDate = (BYTE) InBuffer[3];
              *SancPrnPrice = (BYTE) InBuffer[4];

              char *I_PrimStrAdvertis = (char *) alloca(25);
              ZeroMemory(I_PrimStrAdvertis, 25);
              TranslitToAnsi( (DWORD) &InBuffer[10], (DWORD) I_PrimStrAdvertis, 24);
              *PrimStrAdvertis = A2WBSTR(I_PrimStrAdvertis);

              char *I_SecondStrAdvertis = (char *) alloca(25);
              ZeroMemory(I_SecondStrAdvertis, 25);
              TranslitToAnsi( (DWORD) &InBuffer[34], (DWORD) I_SecondStrAdvertis, 24);
              *SecondStrAdvertis = A2WBSTR(I_SecondStrAdvertis);

              Result = erc_OK;

            } else Result = erc_UnknownError;
          } else Result = erc_DeviceNotReady;
        else Result = erc_PortConfigFail;
      else Result = erc_WrongDevice;
    else Result = erc_PortConfigFail;
  else Result = erc_NoDevice;

  return ( Result );

}

//==============================================================================
DWORD STDMETHODCALLTYPE 
_SetArticleParams( WORD ArticleNo,
						      BYTE ArticleType, 
                  BYTE GroupCode,
						      DWORD ArticleCode,
                  DWORD Price,
						      WORD Tare, 
                  WORD ShelfLife,
                  char *NameBuff)
{

  TCommBufferBig CommBuffer;
  DWORD BytesIn, Result;
  bool Success;

  if ( ArticleNo && (ArticleNo < 1000) )
    if ( ((ArticleType == 0) || (ArticleType == 1)) && ((0 <= GroupCode) && (GroupCode <= 99)) &&
	      (ArticleCode < 999999) && (Price < 999999) &&
	      (Tare < 5000) && (ShelfLife < 999) )
      if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle ) {

	      ZeroMemory(CommBuffer, 100);
	      memcpy( CommBuffer, &ArticleType, 1);
	      memcpy( &CommBuffer[1], &GroupCode, 1);
	      memcpy( &CommBuffer[2], &ArticleCode, 3);
	      memcpy( &CommBuffer[5], &Price, 3);
	      memcpy( &CommBuffer[8], &Tare, 2);
	      memcpy( &CommBuffer[10], &ShelfLife, 2);
	      CopyString(NameBuff, &CommBuffer[13], strlen(NameBuff));

        if (ConfigPort(stc_9bit) )
          if ( SynchronizeDevice() )
            if ( ConfigPort(stc_8bit) )
              if ( WriteCommand(ccSetArticle) )
                if ( WriteArticleCommand(ArticleNo, scBasicParams) )
                {
		              Success = ::WriteFile(hPortHandle, CommBuffer, 61, &BytesIn, NULL) &&
                            ReadFile_(hPortHandle, CommBuffer, 1, &BytesIn, NULL);
                  if ( Success && (BytesIn == 1) && ( (BYTE) CommBuffer[0] == 0x10) )
                    Result = erc_OK;
                  else Result = erc_UnknownError;
                } else Result = erc_DeviceNotReady;
              else Result = erc_DeviceNotReady;
            else Result = erc_PortConfigFail;
          else Result = erc_WrongDevice;
        else Result = erc_PortConfigFail;
      } else Result = erc_NoDevice;
    else Result = erc_WrongParams;
  else Result = erc_WrongArticle;

  return ( Result );

}

//==============================================================================
DWORD STDMETHODCALLTYPE 
_SetArticleParamsD( WORD ArticleNo,
						      BYTE ArticleType, 
                  BYTE GroupCode,
						      DWORD ArticleCode,
                  DWORD Price,
						      WORD Tare, 
                  time_t ShelfLife,
                  char *NameBuff)
{

  TCommBufferBig CommBuffer;
  DWORD BytesIn, Result;
  bool Success;

  if ( ArticleNo && (ArticleNo < 1000) )
    if ( ((ArticleType == 0) || (ArticleType == 1)) && ((0 <= GroupCode) && (GroupCode <= 99)) &&
	      (ArticleCode < 999999) && (Price < 999999) &&
	      (Tare < 5000) && (ShelfLife < 999) )
      if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle ) {

	      ZeroMemory(CommBuffer, 100);
	      memcpy( CommBuffer, &ArticleType, 1);
	      memcpy( &CommBuffer[1], &GroupCode, 1);
	      memcpy( &CommBuffer[2], &ArticleCode, 3);
	      memcpy( &CommBuffer[5], &Price, 3);
	      memcpy( &CommBuffer[8], &Tare, 2);
	      if (ShelfLife)
        {
	        struct tm *t_ShelfLife = gmtime( & ShelfLife );
          BYTE Year = (BYTE) (t_ShelfLife->tm_year & 0X000000FF);
          BYTE Month = (BYTE) (t_ShelfLife->tm_mon & 0X000000FF);
          BYTE Day = (BYTE) (t_ShelfLife->tm_mday & 0X000000FF);
          while ( Year > 99 ) Year -= 100;
	        memcpy( &CommBuffer[10], &Year, 1);
	        memcpy( &CommBuffer[11], &Month, 1);
	        memcpy( &CommBuffer[12], &Day, 1);
	      }
 	      CopyString(NameBuff, &CommBuffer[13], strlen(NameBuff));

        if (ConfigPort(stc_9bit) )
          if ( SynchronizeDevice() )
            if ( ConfigPort(stc_8bit) )
              if ( WriteCommand(ccSetArticle) )
                if ( WriteArticleCommand(ArticleNo, scBasicParams) )
                {
		              Success = ::WriteFile(hPortHandle, CommBuffer, 61, &BytesIn, NULL) &&
                            ReadFile_(hPortHandle, CommBuffer, 1, &BytesIn, NULL);
                  if ( Success && (BytesIn == 1) && ( (BYTE) CommBuffer[0] == 0x10) )
                    Result = erc_OK;
                  else Result = erc_UnknownError;
                } else Result = erc_DeviceNotReady;
              else Result = erc_DeviceNotReady;
            else Result = erc_PortConfigFail;
          else Result = erc_WrongDevice;
        else Result = erc_PortConfigFail;
      } else Result = erc_NoDevice;
    else Result = erc_WrongParams;
  else Result = erc_WrongArticle;

  return ( Result );
}

//==============================================================================
DWORD STDMETHODCALLTYPE 
_GetArticleParams(WORD ArticleNo,
                 OUT BYTE *ArticleType, 
                 OUT BYTE *GroupCode,
                 OUT DWORD *ArticleCode, 
                 OUT DWORD *Price,
                 OUT WORD *Tare,
                 OUT DWORD *ShelfLife, 
                 OUT BSTR *NameBuff)
{

  TCommBufferBig InBuffer;
  DWORD BytesIn, Result;
  BOOL Success;

  ZeroMemory(InBuffer, 100);

  if ( ArticleNo && (ArticleNo < 1000) )
    if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle )
      if (ConfigPort(stc_9bit) )
        if ( SynchronizeDevice() )
          if ( ConfigPort(stc_8bit) )
            if ( WriteCommand(ccGetArticle) )
              if ( WriteArticleCommand(ArticleNo, scBasicParams) )
              {
		            Success = ::ReadFile(hPortHandle, InBuffer, 62, &BytesIn, NULL);
                if ( Success && (BytesIn == 62) && ( (BYTE) InBuffer[61] == 0x10) )
                {
                  *ArticleType = InBuffer[0];
                  *GroupCode = InBuffer[1];
                  *ArticleCode = DecodeInt( (DWORD *) &InBuffer[2]);
                  *Price = DecodeInt( (DWORD *) &InBuffer[5]);
                  memcpy( &InBuffer[8], Tare, 2);
                  *ShelfLife = 0x00000000;
                  memcpy( &InBuffer[10], ShelfLife, 3);

                  char *I_NameBuff = (char *) alloca(49);
                  ZeroMemory(I_NameBuff, 49);
                  TranslitToAnsi( (DWORD) &InBuffer[13], (DWORD) I_NameBuff, 48);
                  *NameBuff = A2BSTR(I_NameBuff);

                  Result = erc_OK;

                } else Result = erc_UnknownError;
              } else Result = erc_DeviceNotReady;
            else Result = erc_DeviceNotReady;
          else Result = erc_PortConfigFail;
        else Result = erc_WrongDevice;
      else Result = erc_PortConfigFail;
    else Result = erc_NoDevice;
  else Result = erc_WrongArticle;

  return ( Result );

}

//==============================================================================
DWORD STDMETHODCALLTYPE 
_GetArticleAddInform(WORD ArticleNo, 
                    BYTE StrNo,
                    BSTR *AddInf)
{

  TCommBufferTiny InBuffer;
  DWORD BytesIn, Result;
  BOOL Success;

  if ( ArticleNo && (ArticleNo < 1000) )
    if ( LblLength && ((LblLength % 10) == 0) && StrNo &&
        (StrNo <= SupportedAmountAddLine[LblType][((LblLength-30) / 10)]) )
      if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle ) {

	      ZeroMemory(InBuffer, 50);

        if (ConfigPort(stc_9bit) )
          if ( SynchronizeDevice() )
            if ( ConfigPort(stc_8bit) )
              if ( WriteCommand(ccGetArticleAddInf) )
                if ( WriteArticleCommand(ArticleNo, StrNo) )
                {
                  Success = ::ReadFile(hPortHandle, InBuffer, 49, &BytesIn, NULL);
                  if ( Success && (BytesIn == 49) && ((BYTE) InBuffer[48] == 0x10) )
                  {
                    char *I_AddInf = (char *) alloca(49);
                    ZeroMemory(I_AddInf, 49);
                    TranslitToAnsi( (DWORD) InBuffer, (DWORD) I_AddInf, 48);
                    *AddInf = A2BSTR(I_AddInf);

                    Result = erc_OK;
            
                  } else Result = erc_UnknownError;
                } else Result = erc_DeviceNotReady;
              else Result = erc_DeviceNotReady;
            else Result = erc_PortConfigFail;
          else Result = erc_WrongDevice;
        else Result = erc_PortConfigFail;
      } else Result = erc_NoDevice;
    else Result = erc_WrongParams;
  else Result = erc_WrongArticle;

  return ( Result );

}

//==============================================================================
DWORD STDMETHODCALLTYPE 
_SetArticleAddInformZero(WORD ArticleNo, 
                        BYTE StrNo)
{

  TCommBufferBig CommBuffer;
  DWORD BytesIn, Result;
  bool Success;

  if ( ArticleNo && (ArticleNo < 1000) )
    if ( LblLength && ((LblLength % 10) == 0) && StrNo &&
        (StrNo <= SupportedAmountAddLine[LblType][((LblLength-30) / 10)]) )
      if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle ) {

	      ZeroMemory(CommBuffer, 50);
        if (ConfigPort(stc_9bit) )
          if ( SynchronizeDevice() )
            if ( ConfigPort(stc_8bit) )
              if ( WriteCommand(ccSetArticleAddInf) )
                if ( WriteArticleCommand(ArticleNo, StrNo) )
                {
		              Success = ::WriteFile(hPortHandle, CommBuffer, 48, &BytesIn, NULL) &&
                            ReadFile_(hPortHandle, CommBuffer, 1, &BytesIn, NULL);
                  if ( Success && (BytesIn == 1) && ( (BYTE) CommBuffer[0] == 0x10) )
                    Result = erc_OK;
                  else Result = erc_UnknownError;
                } else Result = erc_DeviceNotReady;
              else Result = erc_DeviceNotReady;
            else Result = erc_PortConfigFail;
          else Result = erc_WrongDevice;
        else Result = erc_PortConfigFail;
      } else Result = erc_NoDevice;
    else Result = erc_WrongParams;
  else Result = erc_WrongArticle;

  return ( Result );

}

//==============================================================================
DWORD STDMETHODCALLTYPE 
_SetArticleAddInform(WORD ArticleNo, 
                    BYTE StrNo,
                    char *AddInf)
{

  TCommBufferBig CommBuffer;
  DWORD BytesIn, Result;
  bool Success;

  if ( ArticleNo && (ArticleNo < 1000) )
    if ( LblLength && ((LblLength % 10) == 0) && StrNo &&
        (StrNo <= SupportedAmountAddLine[LblType][((LblLength-30) / 10)]) )
      if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle ) {

	      ZeroMemory(CommBuffer, 50);
        CopyString(AddInf, (char *) CommBuffer, strlen(AddInf));

        if (ConfigPort(stc_9bit) )
          if ( SynchronizeDevice() )
            if ( ConfigPort(stc_8bit) )
              if ( WriteCommand(ccSetArticleAddInf) )
                if ( WriteArticleCommand(ArticleNo, StrNo) )
                {
		              Success = ::WriteFile(hPortHandle, CommBuffer, 48, &BytesIn, NULL) &&
                            ReadFile_(hPortHandle, CommBuffer, 1, &BytesIn, NULL);
                  if ( Success && (BytesIn == 1) && ( (BYTE) CommBuffer[0] == 0x10) )
                    Result = erc_OK;
                  else Result = erc_UnknownError;
                } else Result = erc_DeviceNotReady;
              else Result = erc_DeviceNotReady;
            else Result = erc_PortConfigFail;
          else Result = erc_WrongDevice;
        else Result = erc_PortConfigFail;
      } else Result = erc_NoDevice;
    else Result = erc_WrongParams;
  else Result = erc_WrongArticle;

  return ( Result );

}

//==============================================================================
DWORD STDMETHODCALLTYPE 
_SetKeybrdParams(void * Buff)
{
  TCommBufferBig WriteBuffer;
  TCommBufferTiny ReadBuffer;
  DWORD BytesIn, Result;
  bool Success;

  ZeroMemory(WriteBuffer, 127);
  memcpy(WriteBuffer, Buff, 126);

  if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle )
    if (ConfigPort(stc_9bit) )
      if ( SynchronizeDevice() )
        if ( ConfigPort(stc_8bit) )
          if ( WriteCommand(ccSetLabelParams) )
          {
            Success = ::WriteFile(hPortHandle, WriteBuffer, 126, &BytesIn, NULL) &&
                      ReadFile_(hPortHandle, ReadBuffer, 1, &BytesIn, NULL);

            if ( Success && (BytesIn == 1) && ( (BYTE) ReadBuffer[0] == 0x10) )
              Result = erc_OK;
            else Result = erc_UnknownError;

          } else Result = erc_DeviceNotReady;
        else Result = erc_PortConfigFail;
      else Result = erc_WrongDevice;
    else Result = erc_PortConfigFail;
  else Result = erc_NoDevice;

  return ( Result );
}

//==============================================================================
DWORD STDMETHODCALLTYPE 
_GetKeybrdParams(void * Buff)
{
  TCommBufferBig InBuffer;
  DWORD BytesIn, Result;
  BOOL Success;

  ZeroMemory(InBuffer, 128);

  if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle )
    if (ConfigPort(stc_9bit) )
      if ( SynchronizeDevice() )
        if ( ConfigPort(stc_8bit) )
          if ( WriteCommand(ccGetLabelParams) )
          {
            Success = ::ReadFile(hPortHandle, InBuffer, 127, &BytesIn, NULL);
            if ( Success && (BytesIn == 127) && ( (BYTE) InBuffer[126] == 0x10) )
            {
              memcpy(Buff, InBuffer, 126);

              Result = erc_OK;

            } else Result = erc_UnknownError;
          } else Result = erc_DeviceNotReady;
        else Result = erc_PortConfigFail;
      else Result = erc_WrongDevice;
    else Result = erc_PortConfigFail;
  else Result = erc_NoDevice;

  return ( Result );
}

//==============================================================================
DWORD STDMETHODCALLTYPE 
_GetCurrentWeight(OUT DWORD *Weight)
{

  TCommBufferTiny InBuffer;
  DWORD BytesIn, Result;
  BOOL Success;
  int Countloop = 0;

  if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle )
    do 
    {
      if ( (BOOL) Countloop ) Sleep( 1000 );
     
      if (ConfigPort(stc_9bit) )
        if ( SynchronizeDevice() )
          if ( ConfigPort(stc_8bit) )
            if ( WriteCommand(ccGetCurrentWeight) )
            {
              Success = ::ReadFile(hPortHandle, InBuffer, 4, &BytesIn, NULL);
              if ( Success && (BytesIn == 4) && ((BYTE) InBuffer[3] == 0x10) )
              {
                *Weight = DecodeInt( (DWORD *) InBuffer);
                Result = erc_OK;
              } else Result = erc_UnknownError;
            } else Result = erc_DeviceNotReady;
          else Result = erc_PortConfigFail;
        else Result = erc_WrongDevice;
      else Result = erc_PortConfigFail;

      Countloop++;

    } while ( (Result != erc_OK) && (Countloop < 60) ) ;

  else Result = erc_NoDevice;

  return ( Result );

}

//==============================================================================
DWORD STDMETHODCALLTYPE 
_GetTotalWeight(WORD ArticleNo, 
               OUT DWORD *Weight)
{

  TCommBufferTiny InBuffer;
  DWORD BytesIn, Result;
  BOOL Success;

  if ( ArticleNo && (ArticleNo < 1000) )
    if ( (hPortHandle != INVALID_HANDLE_VALUE) && hPortHandle )
      if (ConfigPort(stc_9bit) )
        if ( SynchronizeDevice() )
          if ( ConfigPort(stc_8bit) )
            if ( WriteCommand(ccGetTotalWeight) )
              if ( WriteArticleCommand(ArticleNo, scTotals) )
              {
                Success = ::ReadFile(hPortHandle, InBuffer, 4, &BytesIn, NULL);
                if ( Success && (BytesIn == 4) && ((BYTE) InBuffer[3] == 0x10) )
                {
                  *Weight = DecodeInt( (DWORD *) InBuffer);
                  Result = erc_OK;
              
                } else Result = erc_UnknownError;
              } else Result = erc_DeviceNotReady;
            else Result = erc_DeviceNotReady;
          else Result = erc_PortConfigFail;
        else Result = erc_WrongDevice;
      else Result = erc_PortConfigFail;
    else Result = erc_NoDevice;
  else Result = erc_WrongArticle;

  return ( Result );

}

/*******************************************************************}
{                       External routines                           }
{*******************************************************************/

//==============================================================================
BOOL STDMETHODCALLTYPE 
CreateCommunication(BYTE aPortNo)
{
  BOOL Interm_Res = InitMDevice(aPortNo, true, true);

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! ((BOOL) Interm_Res) );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
DestroyCommunication(void)
{
  BOOL Interm_Res = CloseMDevice();

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! ((BOOL) Interm_Res) );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
SetLabel(BYTE LabelType,
	       BYTE LabelLength,
         BYTE NDepartWeight,
	       BYTE NDepartPiece,
	       BYTE BarCodeKind,
	       BYTE SancPrnDate,
	       BYTE SancPrnPrice,
         BSTR PrimAdvStr,
         BSTR SecAdvStr)
{
	USES_CONVERSION;

  char *I_PrimAdvStr = W2A(PrimAdvStr);
  char *I_SecAdvStr = W2A(SecAdvStr); 

  DWORD Interm_Res = _SetLabelFormat(LabelType, LabelLength);

  if ( ! Interm_Res )
    Interm_Res = _SetLabelParams(NDepartWeight, NDepartPiece, BarCodeKind,
                                 SancPrnDate, SancPrnPrice, 
                                 I_PrimAdvStr, I_SecAdvStr);
  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! ((BOOL) Interm_Res) );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
GetLabelFormat(BYTE *LabelType,
	             BYTE *LabelLength)
{
  DWORD Interm_Res = _GetLabelFormat(LabelType, LabelLength);

  LblType = *LabelType;
  LblLength = *LabelLength;

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! ((BOOL) Interm_Res) );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
SetLabelParams( BYTE NDepartWeight,
	              BYTE NDepartPiece,
	              BYTE BarCodeKind,
	              BYTE SancPrnDate,
	              BYTE SancPrnPrice,
                BSTR PrimAdvStr,
                BSTR SecAdvStr)
{
	USES_CONVERSION;

  char *I_PrimAdvStr = W2A(PrimAdvStr);
  char *I_SecAdvStr = W2A(SecAdvStr); 

  DWORD Interm_Res = _SetLabelParams(NDepartWeight, NDepartPiece, BarCodeKind,
                                     SancPrnDate, SancPrnPrice, 
                                     I_PrimAdvStr, I_SecAdvStr);
  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! ((BOOL) Interm_Res) );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
GetLabelParams( BYTE *NDepartWeight,
	              BYTE *NDepartPiece,
	              BYTE *BarCodeKind,
	              BYTE *SancPrnDate,
	              BYTE *SancPrnPrice,
                BSTR *PrimAdvStr,
                BSTR *SecAdvStr)
{
  DWORD Interm_Res = _GetLabelParams(NDepartWeight, NDepartPiece, BarCodeKind,
                                     SancPrnDate, SancPrnPrice, PrimAdvStr,
                                     SecAdvStr);
  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! ((BOOL) Interm_Res) );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
SetArticle(
      WORD ArticleN,
	    BYTE ArticleType,
	    BYTE GroupCode,
	    DWORD ArticleCode,
	    DWORD Price,
	    WORD Tare,
	    WORD ShelfLife,
	    BSTR Name)
{
	USES_CONVERSION;
  
  char *_Name = W2A(Name);
  char *I_Name;
  DWORD Interm_Res = erc_WrongParams;

  if ( ArticleN < 1000 ) 
  {
    I_Name = (char *) alloca(49);
    ZeroMemory(I_Name, 49);

    if (strlen( _Name ) > 48 ) 
	    strncpy(I_Name, _Name, 48);
    else 
      strcpy(I_Name, _Name);

    Interm_Res = _SetArticleParams(ArticleN, ArticleType, GroupCode,
									                 ArticleCode, Price,
									                 Tare, ShelfLife,
									                 I_Name);
  }

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! ((BOOL) Interm_Res) );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
SetArticleD(
      WORD ArticleN,
	    BYTE ArticleType,
	    BYTE GroupCode,
	    DWORD ArticleCode,
	    DWORD Price,
	    WORD Tare,
	    time_t ShelfLife,
	    BSTR Name)
{
	USES_CONVERSION;
  
  char *_Name = W2A(Name);
  char *I_Name;
  DWORD Interm_Res = erc_WrongParams;

  if ( ArticleN < 1000 ) 
  {
    I_Name = (char *) alloca(49);
    ZeroMemory(I_Name, 49);

    if (strlen( _Name ) > 48 ) 
	    strncpy(I_Name, _Name, 48);
    else 
      strcpy(I_Name, _Name);

    Interm_Res = _SetArticleParamsD(ArticleN, ArticleType, GroupCode,
									                 ArticleCode, Price,
									                 Tare, ShelfLife,
									                 I_Name);
  }

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! (BOOL) Interm_Res );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
GetArticle(WORD ArticleNo,
           OUT BYTE *ArticleType, 
           OUT BYTE *GroupCode,
           OUT DWORD *ArticleCode, 
           OUT DWORD *Price,
           OUT WORD *Tare,
           OUT DWORD *ShelfLife, 
           OUT BSTR *NameBuff)
{
  DWORD Interm_Res = _GetArticleParams(ArticleNo, ArticleType, GroupCode, ArticleCode, 
                                       Price, Tare, ShelfLife, NameBuff);
  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! ((BOOL) Interm_Res) );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
SetArticle_AddInf(
      WORD ArticleN,
	    BYTE StrNo,
	    BSTR AddInf)
{
	USES_CONVERSION;

  char *_AddInf = W2A(AddInf);
  char *I_AddInf;
  DWORD Interm_Res = erc_WrongParams;

  if ( ArticleN < 1000 ) 
  {
    Interm_Res = erc_OK;

    I_AddInf = (char *) alloca(49);
    ZeroMemory(I_AddInf, 49);

    if (strlen( _AddInf ) > 48 ) 
	    strncpy(I_AddInf, _AddInf, 48);
    else 
      strcpy(I_AddInf, _AddInf);

    if ( !LblLength && !LblType )
      Interm_Res = _GetLabelFormat(&LblType, &LblLength);

    if ( !Interm_Res ) 
      Interm_Res = _SetArticleAddInform(ArticleN, StrNo, I_AddInf);
  }

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! (BOOL) Interm_Res );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
CleanArticle_AddInf(WORD ArticleN)
{
  BOOL Interm_Res = erc_WrongParams;

  if ( ArticleN < 1000 ) 
  {
    Interm_Res = erc_OK;

    if ( LblLength && ((LblLength % 10) == 0) ) 
    {
      if (  !LblLength && !LblType )
        Interm_Res = _GetLabelFormat(&LblType, &LblLength);

      if ( !Interm_Res )
        for ( int StrNo = 1; StrNo <= SupportedAmountAddLine[LblType][((LblLength-30)/10)]; StrNo++ )
          if ( ! (Interm_Res = (BOOL) _SetArticleAddInformZero(ArticleN,StrNo)) ) break;
    }
  }

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! (BOOL) Interm_Res );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
GetArticle_AddInf(WORD ArticleN,
	                BYTE StrNo,
	                BSTR *AddInf)
{
  DWORD Interm_Res = erc_WrongParams;

  if ( ArticleN < 1000 ) 
  {
    Interm_Res = erc_OK;

    if ( !LblLength && !LblType )
      Interm_Res = _GetLabelFormat(&LblType, &LblLength);

    if ( !Interm_Res ) 
      Interm_Res = _GetArticleAddInform(ArticleN, StrNo, AddInf);
  }

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! (BOOL) Interm_Res );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
SetKeybrdParams( VARIANT *KeybDat )
{
  DWORD Interm_Res = erc_WrongParams;
  
  if ( V_ISBYREF(KeybDat) &&  V_ISARRAY(KeybDat) && (V_VT(KeybDat)&VT_I2) )
    if ( (((SAFEARRAY* ) *V_ARRAYREF(KeybDat))->cbElements == 2) &&
        (((SAFEARRAY* ) *V_ARRAYREF(KeybDat))->cDims == 1) &&
        (((SAFEARRAY* ) *V_ARRAYREF(KeybDat))->rgsabound[0].cElements == 63) )
      Interm_Res = _SetKeybrdParams(((SAFEARRAY *) *V_ARRAYREF(KeybDat))->pvData);

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! ((BOOL) Interm_Res) );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
GetKeybrdParams( VARIANT *KeybDat )
{
  DWORD Interm_Res = erc_WrongParams;
  
  if ( V_ISBYREF(KeybDat) &&  V_ISARRAY(KeybDat) && (V_VT(KeybDat)&VT_I2) )
    if ( (((SAFEARRAY *) *V_ARRAYREF(KeybDat))->cbElements == 2) &&
        (((SAFEARRAY *) *V_ARRAYREF(KeybDat))->cDims == 1) &&
        (((SAFEARRAY *) *V_ARRAYREF(KeybDat))->rgsabound[0].cElements == 63))
      Interm_Res = _GetKeybrdParams(((SAFEARRAY *) *V_ARRAYREF(KeybDat))->pvData);

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! ((BOOL) Interm_Res) );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
GetWeight(DWORD *Weight)
{

  DWORD Interm_Res = _GetCurrentWeight(Weight);

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! (BOOL) Interm_Res );
}

//==============================================================================
BOOL STDMETHODCALLTYPE 
GetTotalWeight(WORD ArticleN, DWORD *Weight)
{
  DWORD Interm_Res = _GetTotalWeight(ArticleN, Weight);

  if ( Interm_Res != erc_OK )
  {
    if ( ((BYTE) Interm_Res & 1 ) == 1 )
      GetErrorMsg( (DWORD) Interm_Res, GetLastError() );
    else 
      GetErrorMsg( (DWORD) Interm_Res, 0);
  }

  return ( ! (BOOL) Interm_Res );
}


/*******************************************************************}
{                     Interface implementation                      }
{*******************************************************************/

MassaK::MassaK() {}

//==============================================================================
STDMETHODIMP MassaK::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMassaK,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}

  return S_FALSE;
}


//==============================================================================
STDMETHODIMP MassaK::CreateCommunication(unsigned char PortNo)
{
  
  if ( ::CreateCommunication(PortNo) ) return S_OK;

  return E_FAIL;
}

//==============================================================================

STDMETHODIMP MassaK::DestroyCommunication()
{
  
  if ( ::DestroyCommunication() ) return S_OK;

  return E_FAIL;
}


//==============================================================================
STDMETHODIMP MassaK::SetLabel(unsigned char LabelType, 
  										        unsigned char LabelLength, 
											        unsigned char NDepartWeight, 
											        unsigned char NDepartPiece, 
											        unsigned char BarCodeKind, 
											        unsigned char SancPrnDate, 
											        unsigned char SancPrnPrice, 
											        BSTR PrimAdvStr, 
											        BSTR SecAdvStr)
{
  if ( ::SetLabel(LabelType, LabelLength, NDepartWeight, NDepartPiece, 
									BarCodeKind, SancPrnDate, SancPrnPrice, PrimAdvStr, SecAdvStr) )
  {
    Sleep( 1000 );

    return S_OK;
  }

  return E_FAIL;
}

//==============================================================================
STDMETHODIMP MassaK::GetLabelFormat(unsigned char * LabelType, 
  										              unsigned char * LabelLength)
{
  if ( ::GetLabelFormat(LabelType, LabelLength) )
    return S_OK;
 
  return E_FAIL;
}

//==============================================================================
STDMETHODIMP MassaK::SetLabelParams( unsigned char NDepartWeight, 
											               unsigned char NDepartPiece, 
											               unsigned char BarCodeKind, 
											               unsigned char SancPrnDate, 
											               unsigned char SancPrnPrice, 
											               BSTR PrimAdvStr, 
											               BSTR SecAdvStr)
{
  if ( ::SetLabelParams(NDepartWeight, NDepartPiece, BarCodeKind, 
					             SancPrnDate, SancPrnPrice, PrimAdvStr, SecAdvStr) ) 
    return S_OK;

  return E_FAIL;
}

//==============================================================================
STDMETHODIMP MassaK::GetLabelParams( unsigned char *NDepartWeight, 
											               unsigned char *NDepartPiece, 
											               unsigned char *BarCodeKind, 
											               unsigned char *SancPrnDate, 
											               unsigned char *SancPrnPrice, 
											               BSTR * PrimAdvStr, 
											               BSTR * SecAdvStr)
{
  if ( ::GetLabelParams(NDepartWeight, NDepartPiece, BarCodeKind, 
											             SancPrnDate, SancPrnPrice, PrimAdvStr, SecAdvStr) ) 
    return S_OK;

  return E_FAIL;
}

//==============================================================================
STDMETHODIMP MassaK::SetArticle(short ArticleN,
                                unsigned char ArticleType,
	                              unsigned char GroupCode,
	                              long ArticleCode,
	                              double Price,
	                              short Tare,
	                              short ShelfLife,
	                              BSTR Name)
{
  DWORD I_Price = (DWORD) (Price * 100);

  if ( ::SetArticle( ArticleN, ArticleType, GroupCode, ArticleCode,
	                              I_Price, Tare, ShelfLife, Name) ) 
    return S_OK;

  return S_FALSE;
}

//==============================================================================
STDMETHODIMP MassaK::GetArticle(short ArticleN,
									             unsigned char * ArticleType, 
									             unsigned char * GroupCode, 
									             long * ArticleCode, 
									             double * Price,
									             short * Tare,
									             long * ShelfLife,
									             BSTR * Name)
{
  DWORD I_Price;

  if ( ::GetArticle((WORD) ArticleN, ArticleType, GroupCode, (DWORD*) ArticleCode, 
										&I_Price, (WORD*) Tare, (DWORD*) ShelfLife, Name) ) 
  {
    *Price = (double) I_Price / 100;
    return S_OK;
  }

  return E_FAIL;
}

//==============================================================================
STDMETHODIMP MassaK::SetArticleD(short ArticleN,
                                  unsigned char ArticleType,
	                                unsigned char GroupCode,
	                                long ArticleCode,
	                                double Price,
	                                short Tare,
	                                DATE ShelfLife,
	                                BSTR Name)
{
  DWORD I_Price = (DWORD) (Price * 100);

  struct _SYSTEMTIME  lpSystemTime;  
  time_t I_ShelfLife;

  time( &I_ShelfLife );

  if ( VariantTimeToSystemTime(ShelfLife,&lpSystemTime) )
  {
     struct tm when;

     when = *localtime( &I_ShelfLife );
     when.tm_year = lpSystemTime.wYear - 1900;
     when.tm_mon = lpSystemTime.wMonth;
     when.tm_mday = lpSystemTime.wDay - 1;
     when.tm_sec = 0;
     when.tm_min = 0;
     when.tm_hour = 0;
     I_ShelfLife = mktime( &when );
  }

  if ( ::SetArticleD(ArticleN, ArticleType, GroupCode, ArticleCode,
	                            I_Price, Tare, I_ShelfLife, Name) ) 
    return S_OK;

  return S_FALSE;
}

//==============================================================================
STDMETHODIMP MassaK::SetArticle_AddInf( short ArticleN,
	                                      unsigned char StrNo,
                                        BSTR AddInf)
{
  if ( ::SetArticle_AddInf( ArticleN, StrNo, AddInf) ) 
    return S_OK;

  return S_FALSE;
}

//==============================================================================
STDMETHODIMP MassaK::GetArticle_AddInf( short ArticleN,
	                                      unsigned char StrNo,
                                        BSTR * AddInf)
{
  if ( ::GetArticle_AddInf(ArticleN, StrNo, AddInf))
    return S_OK;

  return E_FAIL;
}

//==============================================================================
STDMETHODIMP MassaK::CleanArticle_AddInf( short ArticleN)
{
  if ( ::CleanArticle_AddInf( ArticleN ) ) 
    return S_OK;

  return S_FALSE;
}

//==============================================================================
STDMETHODIMP MassaK::SetKeybrdParams( VARIANT * KeybDat)
{
  if ( ::SetKeybrdParams( KeybDat) ) 
    return S_OK;

  return E_FAIL;
}

//==============================================================================
STDMETHODIMP MassaK::GetKeybrdParams( VARIANT * KeybDat)
{
  if ( ::GetKeybrdParams( KeybDat) ) 
    return S_OK;

  return E_FAIL;
}

//==============================================================================
STDMETHODIMP MassaK::GetWeight(double * Value )
{
  DWORD I_Weight; 

  if ( ::GetWeight( &I_Weight ) )
  {
    *Value = (double) I_Weight / 1000;

    return S_OK;
  }

  return E_FAIL;
}

//==============================================================================
STDMETHODIMP MassaK::GetTotalWeight( short ArticleN,
                                    double * Value )
{
  DWORD I_Weight; 

  if ( ::GetTotalWeight( ArticleN, &I_Weight ) )
  {
    *Value = (double) I_Weight / 1000;

    return S_OK;
  }

  return E_FAIL;
}

//==============================================================================
STDMETHODIMP MassaK::get_DevN(unsigned char * Value)
{
  *Value = DevNo;

  return S_OK;
}

//==============================================================================
STDMETHODIMP MassaK::put_DevN(unsigned char Value)
{
  if (Value < 100) 
    DevNo = Value;

  return S_OK;
}

//==============================================================================
STDMETHODIMP MassaK::get_ProtN(unsigned char *Value)
{
  *Value = DevNo;

  return S_OK;
}

//==============================================================================
STDMETHODIMP MassaK::put_ProtN(unsigned char Value)
{
  if ( (Value == ProtocolsSupported[0]) ||
       (Value == ProtocolsSupported[1]) )
  {
    ProtocolNo = (BYTE) (Value & 0xFF);
    if ( ProtocolNo ) DevNo = Protocol1DeviceNo;

    return S_OK;
  }
  else       
    GetErrorMsg( (DWORD) erc_WrongProtocol, 0);

  return E_FAIL;
}

//==============================================================================
STDMETHODIMP MassaK::get_LastError(BSTR * Value)
{
  *Value = Error_Str;

  return S_OK;
}

STDMETHODIMP MassaK::get_KeybParams(IKeybParams **pVal)
{
	HRESULT			hr	= NULL;
	LPCLASSFACTORY	pcf	= NULL;

	hr = _Module.GetClassObject(CLSID_KeybParams, IID_IClassFactory, (void**)&pcf);
	
	if (SUCCEEDED(hr))
	{
		if	(NULL == pcf)
			return E_POINTER;
		
		hr = pcf->CreateInstance(NULL, IID_IKeybParams, (void**)pVal);

		pcf->Release();
		pcf = NULL;
	}

	return hr;

}
