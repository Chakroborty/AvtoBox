#pragma hdrstop
#include "MSERIAL.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
//---------------------------------------------------------------------------
MSerial::MSerial()
{
	PORtN = L"COM5";
    DWORD BdRate = BaudRate_115200;
}
MSerial::~MSerial()
{

}

bool MSerial::Open(LPCTSTR port, DWORD BaudRate, BYTE ByteSize,
                                                   BYTE Parity, BYTE StopBits)
{
//	handle = CreateFile
//					(
//					 port,
//					 GENERIC_READ | GENERIC_WRITE,
//					 NULL,
//					 NULL,
//					 OPEN_EXISTING,
//					 FILE_FLAG_OVERLAPPED,      //разобраться
//					 NULL
//					);
	handle = CreateFile
					(
					 port,
					 GENERIC_READ | GENERIC_WRITE,
					 NULL,
					 NULL,
					 OPEN_EXISTING,
					 FILE_ATTRIBUTE_NORMAL,
					 NULL
					);






	if(handle == INVALID_HANDLE_VALUE) {return FALSE; }
    if(!SetupComm(handle, SizeBuffer, SizeBuffer)) {return FALSE; }
    if(!GetCommState(handle, &dcb)) {return FALSE; }

    dcb.BaudRate           = BaudRate;
    dcb.fBinary            = TRUE;
    dcb.fOutxCtsFlow       = FALSE;
    dcb.fOutxDsrFlow       = FALSE;
    dcb.fDtrControl        = DTR_CONTROL_HANDSHAKE;
    dcb.fDsrSensitivity    = FALSE;
    dcb.fNull              = FALSE;
    dcb.fRtsControl        = RTS_CONTROL_DISABLE;
    dcb.fAbortOnError      = FALSE;
	dcb.ByteSize           = ByteSize;
	dcb.Parity	           = Parity;
    dcb.StopBits           = StopBits;

    if(!SetCommState(handle, &dcb)){return FALSE; }
    if(!GetCommTimeouts(handle, &CommTimeOuts)) {return FALSE; }

    CommTimeOuts.ReadIntervalTimeout         = TimeoutInterval;
	CommTimeOuts.ReadTotalTimeoutMultiplier  = TimeoutChar;
    CommTimeOuts.ReadTotalTimeoutConstant    = TimeOutWait;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
    CommTimeOuts.WriteTotalTimeoutConstant   = 0;

    if(!SetCommTimeouts(handle, &CommTimeOuts)) {return FALSE; }

    ResetRB();
    ResetWB();
    return TRUE;
};
bool MSerial::OpenPP(BYTE ByteSize, BYTE Parity, BYTE StopBits)
{
//  handle = CreateFile
//                  (
//                   port,
//                   GENERIC_READ | GENERIC_WRITE,
//                   NULL,
//                   NULL,
//                   OPEN_EXISTING,
//                   FILE_FLAG_OVERLAPPED,      //разобраться
//                   NULL
//                  );
    handle = CreateFile
                    (
                     PORtN,
                     GENERIC_READ | GENERIC_WRITE,
                     NULL,
                     NULL,
                     OPEN_EXISTING,
                     FILE_ATTRIBUTE_NORMAL,
                     NULL
                    );






    if(handle == INVALID_HANDLE_VALUE) {return FALSE; }
    if(!SetupComm(handle, SizeBuffer, SizeBuffer)) {return FALSE; }
    if(!GetCommState(handle, &dcb)) {return FALSE; }

    dcb.BaudRate           = BdRate;
    dcb.fBinary            = TRUE;
    dcb.fOutxCtsFlow       = FALSE;
    dcb.fOutxDsrFlow       = FALSE;
    dcb.fDtrControl        = DTR_CONTROL_HANDSHAKE;
    dcb.fDsrSensitivity    = FALSE;
    dcb.fNull              = FALSE;
    dcb.fRtsControl        = RTS_CONTROL_DISABLE;
    dcb.fAbortOnError      = FALSE;
    dcb.ByteSize           = ByteSize;
    dcb.Parity             = Parity;
    dcb.StopBits           = StopBits;

    if(!SetCommState(handle, &dcb)){return FALSE; }
    if(!GetCommTimeouts(handle, &CommTimeOuts)) {return FALSE; }

    CommTimeOuts.ReadIntervalTimeout         = TimeoutInterval;
    CommTimeOuts.ReadTotalTimeoutMultiplier  = TimeoutChar;
    CommTimeOuts.ReadTotalTimeoutConstant    = TimeOutWait;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
    CommTimeOuts.WriteTotalTimeoutConstant   = 0;

    if(!SetCommTimeouts(handle, &CommTimeOuts)) {return FALSE; }

    ResetRB();
    ResetWB();
    return TRUE;
};

void MSerial::Close(void)
{
    CloseHandle(handle);
}

unsigned short MSerial::Read(BYTE *buffer, unsigned short numbytes)
{
    DWORD temp;
    ClearCommError(handle, &temp, &ComState);
    if (!temp)
    {
        boolean result=ReadFile(handle,buffer, numbytes, &temp, &Overlap);
        if(result)
        {
           return (unsigned short)temp;
        }
    }
    return 0;
}

unsigned short MSerial::Write(BYTE *buffer, unsigned short numbytes)
{
	DWORD temp;
	bool result;
    if(numbytes)
    {
		ClearCommError(handle, &temp, &ComState);
        if((numbytes + ComState.cbOutQue)>=SizeBuffer)
		  MessageBox(NULL, L"Невозможно поместить в выходной буфер ", L"", MB_OK);
		//result = WriteFile(handle, buffer, numbytes, &temp, &Overlap);
        result = WriteFile(handle, buffer, numbytes, &temp, NULL);
		if(result)
        {
           return (unsigned short)temp;
        }
    }
    return 0;
}

void MSerial::ResetRB(void)
{
	PurgeComm(handle, PURGE_RXCLEAR);
}

void MSerial::ResetWB(void)
{
    PurgeComm(handle, PURGE_TXCLEAR);
}

unsigned short MSerial::GetWBSize(void)
{
   DWORD temp;
   ClearCommError(handle, &temp, &ComState);
   return (unsigned short) ComState.cbOutQue;
}

unsigned short MSerial::GetRBSize(void)
{
   DWORD temp;
   ClearCommError(handle, &temp, &ComState);
   return (unsigned short) ComState.cbInQue;
}


//---------------------------------------------------------------------------
#pragma package(smart_init)
