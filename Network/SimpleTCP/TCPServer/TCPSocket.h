#pragma once
#include "SocketAddress.h"
class TCPSocket
{
public:
	TCPSocket(SOCKET inSocket) : mSocket(inSocket) {} 
	~TCPSocket();
	int								Connect(const SocketAddress& inAddress);
	int								Bind(const SocketAddress& inToAddress);
	int								Listen(int inBackLog = 32);
	shared_ptr< TCPSocket >			Accept(SocketAddress& inFromAddress);
	int32_t							Send(const void* inData, size_t inLen);
	int32_t							Receive(void* inBuffer, size_t inLen);
private:
	/*friend class SocketUtil;*/
	
	SOCKET		mSocket;
};
typedef shared_ptr< TCPSocket > TCPSocketPtr;