#pragma comment(lib,"ws2_32.lib")
#include "SocketAddress.h"
#include "UDPSocket.h"

int main()
{
	//WSAStartup()
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		std::cout << "WSAStartUp() error" << std::endl;
		return -1;
	}

	//UDPSocket ����
	SOCKET udpSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);	//���ϻ��� �Լ�(�������� ��� intger�� ����) IF_INET(IPv4), UDP���(SOCK_DGRAM,TCP��� SOCK_STREAM)
	if (udpSock == INVALID_SOCKET)
	{
		std::cout << "socket() error" << std::endl;
		return -1;
	}

	//SocketAddress ��ü ���� <- INADDR_ANY,8000��Ʈ
	SocketAddressPtr udpSockAddrPtr = make_shared<SocketAddress>(htonl(INADDR_ANY), 8000);

	//UDPSocket ��ü ����
	UDPSocketPtr udpSockPtr = make_shared<UDPSocket>(udpSock);
	//Bind
	if (udpSockPtr->Bind(*udpSockAddrPtr) < 0)		//Ŭ���̾�Ʈ�� ����ϱ����ؼ��� ������ Ŭ���̾�Ʈ�� �����ؾ� �Ǽ� Bind��
	{
		return -1;
	}

	//RecvFrom,SendTo
	char buf[80];
	int recvLen;
	SocketAddress raddr;		//ReceiveFrom���� �޾ƿ� ���� �ּ�

	while (true)
	{
		//UDO  ������ ����
		recvLen = udpSockPtr->ReceiveFrom(buf, 79, raddr);		//Ŭ���̾�Ʈ�κ��� ���� �޾ƿ´�(recvLen - �޾ƿ� �� ����, ������ - �޾ƿ´�)

		if (recvLen < 0)											// �����϶� - �޾ƿͼ� break�� �ݺ��� Ż��
			break;
		buf[recvLen] = '\0';										//�ι��ڷ� ������ ���ڿ� ����, �޾ƿ� ���� ���� ������°�� null�� �ִ´�.

		cout << "[" << raddr.ToString() << " : " << ntohs(raddr.GetPort()) << " ] " << buf << endl;		//�޾ƿ� ���� ���� �ܼ�â�� ���

		udpSockPtr->SendTo(buf, recvLen, raddr);														//�޾Ҵ� ���� �ٽ� Ŭ���̾�Ʈ���� ������.
	}


	return 0;
}