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

	//UDPSocket 생성
	SOCKET udpSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);	//소켓생성 함수(리눅스의 경우 intger로 설정) IF_INET(IPv4), UDP사용(SOCK_DGRAM,TCP경우 SOCK_STREAM)
	if (udpSock == INVALID_SOCKET)
	{
		std::cout << "socket() error" << std::endl;
		return -1;
	}

	//SocketAddress 객체 생성 <- INADDR_ANY,8000포트
	SocketAddressPtr udpSockAddrPtr = make_shared<SocketAddress>(htonl(INADDR_ANY), 8000);

	//UDPSocket 객체 생성
	UDPSocketPtr udpSockPtr = make_shared<UDPSocket>(udpSock);
	//Bind
	if (udpSockPtr->Bind(*udpSockAddrPtr) < 0)		//클라이언트와 통신하기위해서는 서버와 클라이언트를 연결해야 되서 Bind함
	{
		return -1;
	}

	//RecvFrom,SendTo
	char buf[80];
	int recvLen;
	SocketAddress raddr;		//ReceiveFrom에서 받아올 소켓 주소

	while (true)
	{
		//UDO  데이터 수신
		recvLen = udpSockPtr->ReceiveFrom(buf, 79, raddr);		//클라이언트로부터 값을 받아온다(recvLen - 받아온 값 길이, 에러면 - 받아온다)

		if (recvLen < 0)											// 에러일때 - 받아와서 break로 반복문 탈출
			break;
		buf[recvLen] = '\0';										//널문자로 끝나는 문자열 생성, 받아온 값의 길이 다음번째에 null값 넣는다.

		cout << "[" << raddr.ToString() << " : " << ntohs(raddr.GetPort()) << " ] " << buf << endl;		//받아온 내용 서버 콘솔창에 출력

		udpSockPtr->SendTo(buf, recvLen, raddr);														//받았던 내용 다시 클라이언트에게 보낸다.
	}


	return 0;
}