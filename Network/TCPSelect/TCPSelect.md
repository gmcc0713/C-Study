
```cpp
#pragma comment(lib,"ws2_32.lib")
#include "RoboCatPCH.h"

int main(int argc, const char** argv)
{
	SocketUtil com;					//SocketUtil사용을위한 객체생성
	com.StaticInit();				//소켓 유틸에서 startup함수 사용한다.

	TCPSocketPtr listenSocket = com.CreateTCPSocket(INET);			//TCP소켓 생성

	SocketAddressPtr sap = make_shared<SocketAddress>(INADDR_ANY, 8000);		//sockaddr_in 셋팅

	if (listenSocket->Bind(*sap) != NO_ERROR)		//Bind - 소켓에 주소를 할당하는 역할, 소켓이 사용할 IP 주소와 포트 번호를 할당
	{
		return -1;
	}

	if (listenSocket->Listen() != NO_ERROR)			//Listen
	{
		return -1;
	}

	vector<TCPSocketPtr> readBlockSockets;				// original 소켓 저장,in
	vector<TCPSocketPtr> readableSockets;				// 수신 변화된 소켓 저장,out

	readBlockSockets.push_back(listenSocket);		//리슨 소켓 추가

	while (true)
	{
		if (!SocketUtil::Select(&readBlockSockets,&readableSockets,nullptr, nullptr, nullptr, nullptr))		//Select(in,out)으로 입력 나머지는 nullptr
		{
			continue;	//에러가 발생하면 실행한번더 하기위한 continue;
		}


		//select에서 이벤트 발생한 소켓들 처리 -> 만약 리슨소켓이면 새로운 클라이언트 소켓 생성 아니면 read
		for (const TCPSocketPtr& socket : readableSockets)														//수신변화된 소켓에 범위기반 반복문
		{
			if (socket == listenSocket)				//이 소켓이 리슨 소켓일때
			{
				SocketAddressPtr newClientAddr = make_shared<SocketAddress>();//accept를 위한 클라이언트 정보를 저장하기위한 SocketAddressPtr객체
				auto newSocket = listenSocket->Accept(*newClientAddr);		//Accept - TCP 소켓 프로그래밍에서 클라이언트 연결을 수락하는 데 사용, 서버가 클라이언트의 연결을 받을떄까지 블락된다
				readBlockSockets.push_back(newSocket);				//새로운 클라이언트를 추가
			}
			else
			{
				char buf[80];
				int recvlen = socket->Receive(buf, 80);
				if (recvlen <= 0)				//에러가 났을때
				{
					socket->~TCPSocket();																		//closeSocket함수를 사용하기 위해 소켓의 소멸자를 호출한다
					readBlockSockets.erase(find(readBlockSockets.begin(), readBlockSockets.end(), socket));	//해당 소켓을 찾아서 지워라.
					SocketUtil::ReportError("connection close");
					continue;
				}
				buf[recvlen] = '\0';
				cout << "from client : " << buf << endl;
				socket->Send(buf, recvlen);
			}

		}//for
	}
	return 0;
}
```
