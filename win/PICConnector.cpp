// PICConnector.cpp: implementation of the PICConnector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LinActL12.h"
#include "PICConnector.h"
#include "mpusbapi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// This code works with the first PICDEM board connected.
// You can extend this code to open more boards as required.

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

char vid_pid[]= "vid_04d8&pid_fc5f";    // Default Demo Application Firmware
char out_pipe[]= "\\MCHP_EP1";
char in_pipe[]= "\\MCHP_EP1";

PICConnector::PICConnector(){
  myOutPipe = myInPipe = INVALID_HANDLE_VALUE;
  myOutPipe1 = myInPipe1 = INVALID_HANDLE_VALUE;
  myOutPipe2 = myInPipe2 = INVALID_HANDLE_VALUE;
  libHandle = NULL; // For LoadLibrary
  LoadDLL();
}

PICConnector::~PICConnector(){
	if (myOutPipe != INVALID_HANDLE_VALUE)	MPUSBClose(myOutPipe);
	if (myInPipe != INVALID_HANDLE_VALUE)	MPUSBClose(myInPipe);
		myOutPipe = myInPipe = INVALID_HANDLE_VALUE;

	if (myOutPipe1 != INVALID_HANDLE_VALUE)	MPUSBClose(myOutPipe1);
	if (myInPipe1 != INVALID_HANDLE_VALUE)	MPUSBClose(myInPipe1);
		myOutPipe1 = myInPipe1 = INVALID_HANDLE_VALUE;

	if (myOutPipe2 != INVALID_HANDLE_VALUE)	MPUSBClose(myOutPipe2);
	if (myInPipe2 != INVALID_HANDLE_VALUE)	MPUSBClose(myInPipe2);
		myOutPipe2 = myInPipe2 = INVALID_HANDLE_VALUE;

	// Always check to close the library too.
    if (libHandle != NULL) FreeLibrary(libHandle);
}

void PICConnector::Open1(){
   HANDLE tempPipe = INVALID_HANDLE_VALUE;
   DWORD count = MPUSBGetDeviceCount(vid_pid);
   if (count > 0) {
   myOutPipe = MPUSBOpen(0,vid_pid,out_pipe,MP_WRITE,0);
   myInPipe = MPUSBOpen(0,vid_pid,out_pipe,MP_READ,0);
   if(myOutPipe == INVALID_HANDLE_VALUE || myInPipe == INVALID_HANDLE_VALUE){
        AfxMessageBox("Failed to open data pipes.");        
    }//end if
   }
   else AfxMessageBox("No devices connected.");        
}

void PICConnector::Close1(){
    MPUSBClose(myOutPipe);
    MPUSBClose(myInPipe);
    myOutPipe = myInPipe = INVALID_HANDLE_VALUE;
}

void PICConnector::Open2(){
   HANDLE tempPipe = INVALID_HANDLE_VALUE;
   DWORD count = MPUSBGetDeviceCount(vid_pid);
   if (count > 0) {
   myOutPipe = MPUSBOpen(1,vid_pid,out_pipe,MP_WRITE,0);
   myInPipe = MPUSBOpen(1,vid_pid,out_pipe,MP_READ,0);
   if(myOutPipe == INVALID_HANDLE_VALUE || myInPipe == INVALID_HANDLE_VALUE){
        AfxMessageBox("Failed to open data pipes.");        
    }//end if
   }
   else AfxMessageBox("No devices connected.");        
}

void PICConnector::Close2(){
    MPUSBClose(myOutPipe);
    MPUSBClose(myInPipe);
    myOutPipe = myInPipe = INVALID_HANDLE_VALUE;
}
void PICConnector::Open3(){
   HANDLE tempPipe = INVALID_HANDLE_VALUE;
   DWORD count = MPUSBGetDeviceCount(vid_pid);
   if (count > 0) {
	myOutPipe1 = MPUSBOpen(0,vid_pid,out_pipe,MP_WRITE,0);	myOutPipe2 = MPUSBOpen(1,vid_pid,out_pipe,MP_WRITE,0);
	myInPipe1 = MPUSBOpen(0,vid_pid,out_pipe,MP_READ,0);	myInPipe2 = MPUSBOpen(1,vid_pid,out_pipe,MP_READ,0);
	if(myOutPipe1 == INVALID_HANDLE_VALUE || myInPipe1 == INVALID_HANDLE_VALUE ||
	   myOutPipe2 == INVALID_HANDLE_VALUE || myInPipe2 == INVALID_HANDLE_VALUE){
        AfxMessageBox("Failed to open data pipes.");        
    }//end if
   }
   else AfxMessageBox("No devices connected.");        
}

void PICConnector::Close3(){
    MPUSBClose(myOutPipe1);	MPUSBClose(myOutPipe2);
    MPUSBClose(myInPipe1);	MPUSBClose(myInPipe2);
    myOutPipe1 = myInPipe1 = INVALID_HANDLE_VALUE;
	myOutPipe2 = myInPipe2 = INVALID_HANDLE_VALUE;
}
void PICConnector::LoadDLL(){
    libHandle = NULL;
    libHandle = LoadLibrary("mpusbapi");
    if(libHandle == NULL){	printf("Error loading mpusbapi.dll\r\n");}
    else{MPUSBGetDLLVersion=(DWORD(*)(void))\
			GetProcAddress(libHandle,"_MPUSBGetDLLVersion");
		 MPUSBGetDeviceCount=(DWORD(*)(PCHAR))\
			GetProcAddress(libHandle,"_MPUSBGetDeviceCount");
         MPUSBOpen=(HANDLE(*)(DWORD,PCHAR,PCHAR,DWORD,DWORD))\
			GetProcAddress(libHandle,"_MPUSBOpen");
         MPUSBWrite=(DWORD(*)(HANDLE,PVOID,DWORD,PDWORD,DWORD))\
            GetProcAddress(libHandle,"_MPUSBWrite");
         MPUSBRead=(DWORD(*)(HANDLE,PVOID,DWORD,PDWORD,DWORD))\
            GetProcAddress(libHandle,"_MPUSBRead");
         MPUSBReadInt=(DWORD(*)(HANDLE,PVOID,DWORD,PDWORD,DWORD))\
            GetProcAddress(libHandle,"_MPUSBReadInt");
         MPUSBClose=(BOOL(*)(HANDLE))GetProcAddress(libHandle,"_MPUSBClose");
		 if((MPUSBGetDeviceCount == NULL) || (MPUSBOpen == NULL) ||
            (MPUSBWrite == NULL) || (MPUSBRead == NULL) ||
            (MPUSBClose == NULL) || (MPUSBGetDLLVersion == NULL) ||
            (MPUSBReadInt == NULL))
            AfxMessageBox("GetProcAddress Error\r\n");
    }//end if else
}

//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
//
// A typical application would send a command to the target device and expect
// a response.
// SendReceivePacket is a wrapper function that facilitates the
// send command / read response paradigm
//
// SendData - pointer to data to be sent
// SendLength - length of data to be sent
// ReceiveData - Points to the buffer that receives the data read from the call
// ReceiveLength - Points to the number of bytes read
// SendDelay - time-out value for MPUSBWrite operation in milliseconds
// ReceiveDelay - time-out value for MPUSBRead operation in milliseconds
//

DWORD PICConnector::SendReceivePacket(BYTE *SendData, DWORD SendLength, BYTE *ReceiveData,
                    DWORD *ReceiveLength, UINT SendDelay, UINT ReceiveDelay){
    DWORD SentDataLength;
    DWORD ExpectedReceiveLength = *ReceiveLength;

    if(myOutPipe != INVALID_HANDLE_VALUE && myInPipe != INVALID_HANDLE_VALUE){
        if(MPUSBWrite(myOutPipe,SendData,SendLength,&SentDataLength,SendDelay)){
            if(MPUSBRead(myInPipe,ReceiveData, ExpectedReceiveLength,
                        ReceiveLength,ReceiveDelay)){
                if(*ReceiveLength == ExpectedReceiveLength){
                    return 1;   // Success!
                }
                else if(*ReceiveLength < ExpectedReceiveLength){
                    return 2;   // Partially failed, incorrect receive length
                }
            }
            else
                CheckInvalidHandle();
        }
        else
            CheckInvalidHandle();
    }//end if

    return 0;  // Operation Failed
}//end SendReceivePacket

DWORD PICConnector::SendReceivePacketBoth(BYTE *SendData, DWORD SendLength, BYTE *ReceiveData,
                    DWORD *ReceiveLength, UINT SendDelay, UINT ReceiveDelay){
    DWORD SentDataLength;
    DWORD ExpectedReceiveLength = *ReceiveLength;
	MPUSBWrite(myOutPipe1,SendData,SendLength,&SentDataLength,SendDelay);
	MPUSBWrite(myOutPipe2,SendData,SendLength,&SentDataLength,SendDelay);
	MPUSBRead(myInPipe1,ReceiveData, ExpectedReceiveLength,ReceiveLength,ReceiveDelay);
	MPUSBRead(myInPipe2,ReceiveData, ExpectedReceiveLength,ReceiveLength,ReceiveDelay);
	/*
    if(myOutPipe1 != INVALID_HANDLE_VALUE && myInPipe1 != INVALID_HANDLE_VALUE){
        if(MPUSBWrite(myOutPipe1,SendData,SendLength,&SentDataLength,SendDelay)){
            if(MPUSBRead(myInPipe1,ReceiveData, ExpectedReceiveLength,ReceiveLength,ReceiveDelay)){
                if(*ReceiveLength == ExpectedReceiveLength){
                    return 1;   // Success!
                }
                else if(*ReceiveLength < ExpectedReceiveLength){
                    return 2;   // Partially failed, incorrect receive length
                }
            }
            else
                CheckInvalidHandle();
        }
        else
            CheckInvalidHandle();		
    }//end if

	if(myOutPipe2 != INVALID_HANDLE_VALUE && myInPipe2 != INVALID_HANDLE_VALUE){
        if(MPUSBWrite(myOutPipe2,SendData,SendLength,&SentDataLength,SendDelay)){
            if(MPUSBRead(myInPipe2,ReceiveData, ExpectedReceiveLength,ReceiveLength,ReceiveDelay)){
                if(*ReceiveLength == ExpectedReceiveLength){
                    return 1;   // Success!
                }
                else if(*ReceiveLength < ExpectedReceiveLength){
                    return 2;   // Partially failed, incorrect receive length
                }
            }
            else
                CheckInvalidHandle();
        }
        else
            CheckInvalidHandle();
    }//end if
	*/
    return 0;  // Operation Failed
}//end SendReceivePacket


//---------------------------------------------------------------------------

void PICConnector::CheckInvalidHandle(void){
    if(GetLastError() == ERROR_INVALID_HANDLE){
        // Most likely cause of the error is the board was disconnected.
        MPUSBClose(myOutPipe);
        MPUSBClose(myInPipe);
        myOutPipe = myInPipe = INVALID_HANDLE_VALUE;
    }//end if
    else
        printf("Error Code \r\n",GetLastError());
}//end CheckInvalidHandle

//---------------------------------------------------------------------------
