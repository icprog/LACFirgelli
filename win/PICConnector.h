// PICConnector.h: interface for the PICConnector class.
#if !defined(AFX_PICCONNECTOR_H__518E24BC_B80D_4227_A2E5_F55660FCD5CB__INCLUDED_)
#define AFX_PICCONNECTOR_H__518E24BC_B80D_4227_A2E5_F55660FCD5CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PICConnector {
	HINSTANCE libHandle;
	HANDLE myOutPipe;
	HANDLE myInPipe;
	HANDLE myOutPipe1;
	HANDLE myInPipe1;
	HANDLE myOutPipe2;
	HANDLE myInPipe2;
public:
	void LoadDLL();
	void Close1();
	void Open1();
	void Close2();
	void Open2();
	void Open3();
	void Close3();
	PICConnector();
	DWORD SendReceivePacket(BYTE *SendData, DWORD SendLength, BYTE *ReceiveData,
                    DWORD *ReceiveLength, UINT SendDelay, UINT ReceiveDelay);
	DWORD SendReceivePacketBoth(BYTE *SendData, DWORD SendLength, BYTE *ReceiveData,
                    DWORD *ReceiveLength, UINT SendDelay, UINT ReceiveDelay);
	void CheckInvalidHandle(void);
	virtual ~PICConnector();
};

#endif // !defined(AFX_PICCONNECTOR_H__518E24BC_B80D_4227_A2E5_F55660FCD5CB__INCLUDED_)
