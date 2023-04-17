#pragma once
#include "SocketAddress.h"
class UDPSocket
{
public:
	UDPSocket(SOCKET inSocket) : mSocket(inSocket) {}
	~UDPSocket();

	int Bind(const SocketAddress& inToAddress);
	int SendTo(const void* inToSend, int inLength, const SocketAddress& inToAddress);	//어디로 보내야 될지 결정해야 되므로 SocketAddress를 보낸다
	int ReceiveFrom(void* inToReceive, int inMaxLength, SocketAddress& outFromAddress); 

	/*
	int SendTo( const MemoryOutputStream& inMOS, const SocketAddress& inToAddress );
	int ReceiveFrom( MemoryInputStream& inMIS, SocketAddress& outFromAddress );
	*/

	//int SetNonBlockingMode(bool inShouldBeNonBlocking);

private:
	friend class SocketUtil;
	SOCKET mSocket;
	//UDPSocket(SOCKET inSocket) : mSocket(inSocket) {}
};

typedef shared_ptr< UDPSocket >	UDPSocketPtr;