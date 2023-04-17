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
```cpp
#pragma comment(lib,"ws2_32.lib")
#include "RoboCatPCH.h"

int main(int argc, const char** argv)
{
	SocketUtil com;
	com.StaticInit(); //WSAStartup
	TCPSocketPtr listenSocket = com.CreateTCPSocket(INET); //socket 생성
	SocketAddressPtr sap = make_shared<SocketAddress>(INADDR_ANY, 8000);//sockaddr_in 셋팅
	if (listenSocket->Bind(*sap) != NO_ERROR)
		return -1;
	if (listenSocket->Listen() != NO_ERROR)
		return -1;

	vector<TCPSocketPtr> readBlockSockets; // original 소켓 저장
	vector<TCPSocketPtr> readableSockets;  // 수신 변화된 소켓 저장

	readBlockSockets.push_back(listenSocket);

	while (true) {
		if (!SocketUtil::Select(&readBlockSockets, &readableSockets, nullptr, nullptr, nullptr, nullptr))
			continue;

		for (const TCPSocketPtr& socket : readableSockets) {
			if (socket == listenSocket) {
				SocketAddressPtr newClientAddress = make_shared<SocketAddress>(); //client 정보 저장
				auto newSocket = listenSocket->Accept(*newClientAddress);
				readBlockSockets.push_back(newSocket);
			}
			else {
				char buf[80];
				int recvlen = socket->Receive(buf, 80);
				if (recvlen <= 0) {
					socket->~TCPSocket(); //closesocket
					readBlockSockets.erase(find(readBlockSockets.begin(),
						readBlockSockets.end(), socket));
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
//#endif

```
