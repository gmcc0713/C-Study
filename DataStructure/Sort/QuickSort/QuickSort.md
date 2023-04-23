
# 퀵 정렬
- 시간 복잡도 O(N*LogN)
## 방법
1. 리스트의 중간지점을 고른다 (피봇)
3. 제일 처음의 값을 LEFT 제일 마지막 값을 Right로 정한다
4. 만약 Left번째 값이 Pivot보다 크다면 Right번째 값과 피봇을 비교한다.
5. 이때 Right번째 값이 피봇보다 크다면 Right-=1을 하고 작다면 Left번쨰 값과 바꾼다.
6. 이과정을 반복하고 Right가 Left보다 작으면 피봇을 기준으로 왼쪽과 오른쪽으로 분할한다.
7. 이 과정을 각각의 부분집합에 반복한다


![QuickSort](https://user-images.githubusercontent.com/59678097/233827171-f0b15a5e-8c48-444a-9f6a-fd4c17f0078a.gif)

## [구현](./QuickSort.c)
