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
	//dll Ȱ��ȭ

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		err_display("WSAStartup");
		return -1;
	}

	//���� ����-udp��

	SOCKET s_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s_sock == INVALID_SOCKET)
	{
		err_display("socket");
		return -1;
	}

	//������ IP/Port �޸𸮿� ����

	SOCKADDR_IN saddr;
	ZeroMemory(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(ServerPort);
	if (!inet_pton(AF_INET, ServerIP, &saddr.sin_addr))
	{
		err_display("inet_pton");
		return -1;
	}

	//���ڼ���
	char mesbuf[MAXBUFLEN];
	int sendlen;
	int recvlen;
	int fromlen = sizeof(saddr);

	while (true)
	{
		//keyboard ����
		if (fgets(mesbuf, MAXBUFLEN - 1, stdin) == NULL)
			break;

		//�۽�
		sendlen = strlen(mesbuf);
		sendto(s_sock, mesbuf, sendlen, 0, (SOCKADDR*)&saddr, sizeof(saddr));

		//����
		recvlen = recvfrom(s_sock, mesbuf, MAXBUFLEN - 1, 0, (SOCKADDR*)&saddr, &fromlen);
		//���� �Լ� ��������� ���� ó��
		if (recvlen == 0 || recvlen == SOCKET_ERROR)
		{
			err_display("recvfrom");
			break;
		}

		mesbuf[recvlen] = '\0';
		cout << "[server]  " << mesbuf << endl;
	}

	//���� ��ȯ
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