#pragma comment(lib,"ws2_32.lib")
#include <WS2tcpip.h>
#include <iostream>

#define ServerPort 8000
#define ServerIP "127.0.0.1"
#define MAXBUFLEN 80
#define MAXIPLEN 20

using std::cout;
using std::endl;
void err_display(const char*);
int main()
{
	//dll 활성화

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		err_display("WSAStartup");
		return -1;
	}

	//소켓 생성-udp용

	SOCKET s_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s_sock == INVALID_SOCKET)
	{
		err_display("socket");
		return -1;
	}

	//서버의 IP/Port 메모리에 저장

	SOCKADDR_IN saddr;
	ZeroMemory(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(ServerPort);
	if (!inet_pton(AF_INET, ServerIP, &saddr.sin_addr))
	{
		err_display("inet_pton");
		return -1;
	}

	//에코서비스
	char mesbuf[MAXBUFLEN];
	int sendlen;
	int recvlen;
	int fromlen = sizeof(saddr);

	while (true)
	{
		//keyboard 수신
		if (fgets(mesbuf, MAXBUFLEN - 1, stdin) == NULL)
			break;

		//송신
		sendlen = strlen(mesbuf);
		sendto(s_sock, mesbuf, sendlen, 0, (SOCKADDR*)&saddr, sizeof(saddr));

		//수신
		recvlen = recvfrom(s_sock, mesbuf, MAXBUFLEN - 1, 0, (SOCKADDR*)&saddr, &fromlen);
		//수신 함수 결과값으로 에러 처리
		if (recvlen == 0 || recvlen == SOCKET_ERROR)
		{
			err_display("recvfrom");
			break;
		}

		mesbuf[recvlen] = '\0';
		cout << "[server]  " << mesbuf << endl;
	}

	//소켓 반환
	closesocket(s_sock);
	WSACleanup();
	return 0;
}

void err_display(const char* mes)
{
	char* buf = NULL;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&buf, 0, NULL);
	cout << mes << " : " << buf << endl;
	LocalFree(buf);
}