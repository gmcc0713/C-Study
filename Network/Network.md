### [간단한 UDP 서버](./SimpleUDP/SimpleUDP.md)
### [간단한 TCP 서버](./SimpleTCP/SimpleTCP.md)

## 블로킹과 논블로킹

- 지금까지 구현된 방식은 Blocking방식.
- 블로킹은 받은 데이터가 없을때 블로킹되어 데이터가 수신될때 까지 기다림.


### 멀티 스레딩
- 블로킹 가능성이 있는 함수를 별도의 스레드에서 구현하는 것.
- 과정
![멀티스레딩 과정](https://user-images.githubusercontent.com/59678097/232429929-33f1186a-3833-4ef9-9eee-35e02487518c.jpg)


### 논 블로킹
- 논블로킹을 사용하려면 논블로킹 모드로 지정해야한다
- 윈도우에서 논블로킹을 사용하려면 아래의 함수를 사용한다
```cpp
int ioctlsocket(SOCKET sock,long cmd, u_long* argp);
//sock - 논블로킹 모드로 두고 싶은 소켓
//cmd - 제어하고자하는 소켓 파라미터
//arpg - 파라미터에 설정하려는 값
```

### 논블로킹 세팅하기위한 함수
```cpp
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
```
### 논블로킹 소켓을 사용하는 게임루프
```cpp
void DoGameLoop()
{
  UDPSocketPtr mySock = SocketUtill::CreateUDPSocket(INET);
  mSock->SetNonBlockingMode(true);
  while(gIsGameRunning)
  {
    char data[1500];
    SocketAddress socketAddress;
  
    int bytesReceived = mySock->ReceiveFrom(data,sizeof(data),socketAddress);
    if(byteReceived>0)
      ProcessReceivedData(data,bytesReceived,socketAddress);
   DoGameFrame();
  }
}
```
-> 소켓을 논블로킹 모드로 두고 매프레임 새로운 데이터가 있는지 확인한다.

##Select()함수
- 논블로킹을 사용하면 폴링해야할 소켓 수가 늘어갈수록 효율이 떨어진다.
- -이에 대한 대안으로 Select()함수가 있다.
```cpp
int select(int nfds,fd_set* readfds, fd_set* writefds,fd_set* exceptfds, const timeval* timeout);
```
#### nfds -> 검사 대상이 되는 파일 수
#### readfds -> 소켓 컬랙션(읽을 준비가 되었는지 확인하고싶은 소켓을 여기 넣는다)
- readfds에 포함된 소켓으로 패킷이 도착하면 select함수는 최대한 빨리 블로킹 상태에서 빠져나와 호출스레드를 리턴
- 이벤트가 발생하기 전까지 블로킹 되어있다가 이벤트가 발생하는순가 블로킹이 해제된다.
#### writefds -> 쓰기용으로 체크하고 싶은 소켓을 담은 fd_set
- select()가 리턴한 뒤 writefds에 남아있는 소켓은 쓰기작업을 해도 호출 스레드가 블로킹에 걸리지 않는다
#### exceptfds -> 에러를 점검하고자 담은 소켓
#### timeout -> 최대 제한시간

## TCP에 Select() 적용
### 서버가 작동하는 과정
1. startup() : 네트워크 라이브러리 초기화
2. socket() : 서버 소켓 생성
3. bind() : 서버 소켓에 IP 주소와 포트 번호 지정
4. listen() : 클라이언트의 연결 요청 대기
5. select() : 읽기 가능한 소켓 검사, 찾고 난 뒤 read에서 실행
6. accept() : 클라이언트와 연결된 새로운 소켓 생성
7. read() / write() : 데이터 송수신
8. close() : 소켓 종료
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
