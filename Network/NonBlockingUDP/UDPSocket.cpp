#include "UDPSocket.h"

int UDPSocket::Bind(const SocketAddress& inBindAddress)
{
	int error = bind(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());
	if (error != 0)
	{
		cout<<"UDPSocket::Bind"<<endl;
		return WSAGetLastError();
	}

	return NO_ERROR;
}

int UDPSocket::SendTo(const void* inToSend, int inLength, const SocketAddress& inToAddress)
{
	int byteSentCount = sendto(mSocket,
		static_cast<const char*>(inToSend),
		inLength,
		0, &inToAddress.mSockAddr, inToAddress.GetSize());
	if (byteSentCount <= 0)
	{
		//we'll return error as negative number to indicate less than requested amount of bytes sent...
		cout << "UDPSocket::SendTo"<<endl;
		return -WSAGetLastError();
	}
	else
	{
		return byteSentCount;
	}
}

int UDPSocket::ReceiveFrom(void* inToReceive, int inMaxLength, SocketAddress& outFromAddress)
{
	socklen_t fromLength = outFromAddress.GetSize();

	int readByteCount = recvfrom(mSocket,
		static_cast<char*>(inToReceive),
		inMaxLength,
		0, &outFromAddress.mSockAddr, &fromLength);
	if (readByteCount >= 0)
	{
		return readByteCount;
	}
	else
	{
		int error = WSAGetLastError();

		if (error == WSAEWOULDBLOCK)		//���ŷ���� ���� �߻�-ū�������ƴ�,��ŷ������ ���ֹ߻����� ������
		{
			return 0;
		}
		else if (error == WSAECONNRESET)	//������ ���������� ������ ��������
		{
			//this can happen if a client closed and we haven't DC'd yet.
			//this is the ICMP message being sent back saying the port on that computer is closed
			//LOG("Connection reset from %s", outFromAddress.ToString().c_str());

			return -WSAECONNRESET;
		}
		else
		{
			cout<<"UDPSocket::ReceiveFrom"<<endl;
			return -error;
		}
	}
}

UDPSocket::~UDPSocket()
{
#if _WIN32
	closesocket(mSocket);
#else
	close(mSocket);
#endif
}


int UDPSocket::SetNonBlockingMode(bool inShouldBeNonBlocking)
{
#if _WIN32
	u_long arg = inShouldBeNonBlocking ? 1 : 0;
	int result = ioctlsocket(mSocket, FIONBIO, &arg);
#else
	int flags = fcntl(mSocket, F_GETFL, 0);
	flags = inShouldBeNonBlocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
	int result = fcntl(mSocket, F_SETFL, flags);
#endif

	if (result != SOCKET_ERROR)
	{
		return NO_ERROR;
	}
	SocketUtil::ReportError("UDPSocket::SetNonBlockingMode");
	return SocketUtil::GetLastError();
}
