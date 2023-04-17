### [간단한 UDP 서버](./SimpleUDP/SimpleUDP.md)
### [간단한 TCP 서버](./SimpleTCP/SimpleTCP.md)

## 블로킹과 논블로킹

- 지금까지 구현된 방식은 Blocking방식.
- 블로킹은 받은 데이터가 없을때 블로킹되어 데이터가 수신될때 까지 기다림.


### 멀티 스레딩
- 블로킹 가능성이 있는 함수를 별도의 스레드에서 구현하는 것.
![멀티스레딩 과정](https://user-images.githubusercontent.com/59678097/232429513-b234ce61-ab1d-4403-b693-a3a630e406be.jpg)
