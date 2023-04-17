#pragma comment(lib,"ws2_32.lib")
#include <WS2tcpip.h>
#include <iostream>

using std::cout;
using std::endl;

void err_display(const char*);

int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		err_display("WSAStartup error");
		return -1;
	}

	SOCKET c_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (c_sock == INVALID_SOCKET)
	{
		err_display("socket error");
		return -1;
	}

	//����(server)�� IP + Port �����ϴ� ���� ����
	SOCKADDR_IN saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8000);
	if (!inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr))
	{
		err_display("inet_pton error");
		return -1;
	}

	//������ ���� 
	if (connect(c_sock, (SOCKADDR*)&saddr, sizeof(saddr)) == SOCKET_ERROR)
	{
		err_display("connect error");
		return -1;
	}
	const int MAXBUF = 80;
	char buf[MAXBUF];
	int recvlen;
	int sendlen;
	while (true)
	{
		if (fgets(buf, MAXBUF - 1, stdin) == NULL)
			break;

		//�۽�
		sendlen = (int)strlen(buf);
		send(c_sock, buf, sendlen - 1, 0);

		//����
		recvlen = recv(c_sock, buf, MAXBUF - 1, 0);

		if (recvlen == SOCKET_ERROR) {
			err_display("recv error");
			closesocket(c_sock);
			break;
		}

		if (recvlen == 0)
		{
			cout << "normal close connection case" << endl;
			closesocket(c_sock);
			break;
		}

		buf[recvlen] = '\0'; //�������� �� ���� �����Ͽ� ���ڿ��� ��ȯ��Ŵ
		cout << "from server : " << buf << endl;
	}

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