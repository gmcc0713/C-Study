#pragma comment (lib,"ws2_32.lib")
#include "SocketAddress.h"
#include "TCPSocket.h"


int main()
{
	//WSAStartup
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa)) {
		cout << "WSAStartup()" << endl;
		return -1;
	}

	//tcp 소켓 생성
	SOCKET tcpsock;
	if ((tcpsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) 
  {
		cout << "socket()" << endl;
		return -1;
	}

	//tcpsocket 객체 생성
	TCPSocketPtr tptr = make_shared<TCPSocket>(tcpsock);

	//SocketAddress 객체 생성 : 필요한 정보 입력(IP, Port)
	SocketAddressPtr tsa = make_shared<SocketAddress>(htonl(INADDR_ANY), 8000);

	//bind
	if (tptr->Bind(*tsa) != NO_ERROR)
		return -1;

	//listen, UDP와의 차이점
	if (tptr->Listen() < 0) //: default value is 32
		return -1;

	//accept : 클라이언트 접속 처리하여 새로운 전용 소켓 생성
	SocketAddress raddr;
	TCPSocketPtr newtptr = tptr->Accept(raddr);
	if (newtptr == nullptr)
		return -1;
	
	int recvlen;
	char buf[80];

	while (true) {
		//recv
		recvlen = newtptr->Receive(buf, 80);
		if (recvlen == 0) {
			cout << "connection close case" << endl;
			break;
		}
		if (recvlen < 0)
			break;
		buf[recvlen] = '\0';
		cout << "[" << raddr.ToString() << " : " << ntohs(raddr.GetPort()) 
			<< " ]   " << buf << endl;

		//send
		newtptr->Send(buf, recvlen);
	}


	return 0;
}

