# 이진 탐색 트리

## 특징
- 자신의 왼쪽 자식의 노드의 값은 자기자신보다 작아야한다.
- 자신의 오른쪽 자식의 노드의 값은 자기자신보다 커야한다.
- 중복이 없어야 한다.
- 자신의 자식 트리 또한 모두 이진 탐색 트리이다.

## 순회 방법
- 전위 순회, 후위 순회, 중위 순회 가 있다.
#### 전위순회
```cpp
cout << start->data << " ";
inorder_impl(start->left);
inorder_impl(start->right);
```
#### 중위순회
```cpp
inorder_impl(start->left);
cout << start->data << " ";
inorder_impl(start->right);
```
#### 후위순회
```cpp
inorder_impl(start->left);
inorder_impl(start->right);
cout << start->data << " ";
```

## 삽입
중복이 없을때 트리의 리프로 가서 삽입을 한다.
```cpp
TreeNode * insert_node(TreeNode * node, int key){
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (node == NULL) return new_node(key);

	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);
	// 변경된 루트 포인터를 반환한다. 
	return node;
}
```
## 삭제
- 차수가 0일떄 -> 지우려는 노드를 가리키는 부모의 노드의 포인터를 지운다
- 차수가 1일때 -> 삭제한 자식노드를 부모의 포인터에 옮긴다.
- 차수가 2일때 -> 삭제한후 자식노드중 왼쪽이면 가장 큰수, 오른쪽이면 가작 작은수를 넣는다
