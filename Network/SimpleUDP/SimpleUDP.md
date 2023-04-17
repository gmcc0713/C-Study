## UDP 기초
#### 모든 네트워크 계층에서 발신지 주소와 목적지 주소가 필요하다.(전송계층패킷의 경우 발신지 포트, 목적지 포드도 필요함)
#### 이러한 정보를 저장하기 위한 구조체가 정의되어있다

```cpp
struct sockaddr
{
	uint16_t sa_family;	//주소의 종류 -> 소켓을 만들때 썼던 af파라미터와 일치
	char sadata[14];	//다양한 주소와 포트번호를 저장하는 장소
};

struct sockaddr_in
{
	short sin_family;		//주소의 종류 -> 소켓을 만들때 썼던 af파라미터와 일치
	uint16_t sin_port;		//포트 값
	struct in_addr sin_addr;	//4바이트의 주소
	char sin_zero[8];		
};

//소켓라이브러리마다 in_addr이 다르기 때문에 사용
struct in_addr
{
	union
	{
		struct
		{
			uint8_t s_b1,s_b2,s_b3,s_b4;
		}S_un_b;
		struct
		{
			uint16_t s_b1,s_b2,s_b3,s_b4;
		}S_un_w;
		uint32_t S_addr;
	}S_un;
};
```

#### 여러 바이트를 묶어서 쓸때 TCP/IP스택과 호스트 컴퓨터 바이트  순서체계가 다를수도 있다.
#### 따라서 서로 변환이 가능하도록 해야한다.

```cpp
//호스트 바이트 순서 --> 네트워크 바이트 순서
uint16_t htons(uint16_t hostshort);
uint32_t htonl(uint32_t hostlong);
```

#### 반대의 경우 네트워크 바이트 순서에서 호스트 바이트 순서로 바꿔야한다.
```cpp
//네트워크 바이트 순서 --> 호스트 바이트 순서
uint16_t htons(uint16_t hostshort);
uint32_t htonl(uint32_t hostlong);
```


### 자료형 안정성이 확보된 SocketAddress
```cpp
class SocketAddress
{
public:
	//4바이트의 주소와 포트번호를 저장하는 생성자
	SocketAddress(uint32_t inAddress, uint16_t inPort) 
	{
		GetAsSockAddrIn()->sin_family = AF_INET;
		GetIP4Ref() = htonl(inAddress);
		GetAsSockAddrIn()->sin_port = htons(inPort);
	}
	//socketaddr구조체를 받아 내부 mSockAddr에 복사하는 생성자
	SocketAddress(const sockaddr& inSockAddr)
	{
		memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
	}
	uint32_t				GetSize()			const { return sizeof(sockaddr);
private:
	sockaddr mSockAddr;
	sockaddr_in* GetAsSockAddrIn() { return reinterpret_cast<sockaddr_in*>(&mSockAddr); }
};
typedef shared_ptr< SocketAddress > SocketAddressPtr;
```

## UDP소켓 만들기 
### SendTo()함수
```cpp
int sendto(SOCKET sock, const char* buf,int len, int flags,const sockaddr* to, int tolen);
// SOCKET sock -> 데이터 그램을 보낼 소켓
// const char* buf -> 보낼 데이터의 시작주소
// int len -> 보낼 데이터 길이, int flags -> 데이터 전송을 제어하는 비트플래그
// const sockaddr* to -> 도착지 목적지를 가리키는 포인터
// int tolen -> socketaddr의 길이
```
### RecvFrom()함수
```cpp
int recvfrom(SOCKET sock, const char* buf,int len, int flags,const sockaddr* to, int tolen);
// SOCKET sock -> 데이터 그램을 보낼 소켓
// const char* buf -> 보낼 데이터의 시작주소
// int len -> 보낼 데이터 길이, int flags -> 데이터 전송을 제어하는 비트플래그
// const sockaddr* from -> 발신자를 가리키는 포인터
// int* fromlen -> socketaddr의 길이
```
### Bind()함수
```cpp
int Bind(const SocketAddress& inToAddress);
```
















서버
1. WSAStartUp() 하기
2. UDPSocket 생성
3. SocketAddress 객체 생성 <- INADDR_ANY,8000포트
4. UDPSocket 객체 생성
5. Bind() 하기
6. Recv(),Send() 하기
7. 받아온 내용 서버 콘솔창에 출력

```cpp

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
```
