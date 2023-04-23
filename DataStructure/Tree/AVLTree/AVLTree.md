# AVLTree

## 특징
- 자체 균형 이진 편향트리
- 이진탐색트리의 경우 편향트리일때 효과가 없음
- 탐색의 과정은 이진 탐색트리와 동일
- 삽입은 차수가 2 이상이면 AVL트리를 재구성하도록 연산(연산 종류 총 4개 (LR,RL,LL,RR))

## 삽입
- 불균형 상태인지 확인후 아래의 삽인연산을 시행한다
#### LL
- 노드의 왼쪽 자식 노드의 왼쪽 자식 노드에 새로운 노드가 추가 되었을때
- 시계 방향으로 회전
```cpp
Node* LeftToLeft(Node* node)
{
	Node* tmp;
	tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	return tmp;
}
```
#### RR
- 노드의 오른쪽 자식 노드의 오른쪽 자식 노드에 새로운 노드가 추가 되었을때
- 반시계 방향으로 회전
```cpp
Node* RightToRight(Node* node)
{
	Node* tmp;
	tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;
	return tmp;
}
```
#### LR
LL로 교체후 LL연산을 한다
#### RL
RR로 교체후 RRL연산을 한다

## [구현](./AVLTreeDepthCheck.c)
