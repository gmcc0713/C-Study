#include "Bst.h"
node* Bst::find_impl(node* current, int value)
{
	if (!current)
	{
		std::cout << std::endl;
		return NULL;
	}

	if (current->data == value)
	{
		std::cout << value << "을(를) 찾았습니다" << std::endl;
		return current;
	}

	if (value < current->data)	//value값이 현재 노드 왼쪽에 있는 경우
	{
		std::cout << current->data << "에서 왼쪽으로 이동 : ";
		return find_impl(current->left, value);
	}
	std::cout << current->data << "에서 오른쪽으로 이동 : ";
	return find_impl(current->right, value);
}

void Bst::insert_impl(node* current, int value)
{
	if (value < current->data)
	{
		if (!current->left)
		{
			current->left = new node{ value, NULL,NULL };
		}
		else
		{
			insert_impl(current->left, value);
		}
	}
	else
	{
		if (!current->right)
		{
			current->right = new node{ value, NULL,NULL };
		}
		else
		{
			insert_impl(current->right, value);
		}
	}
}
void Bst::inorder_impl(node* start)
{
	if (!start)
		return;
	inorder_impl(start->left);
	cout << start->data << " ";
	inorder_impl(start->right);
}

void Bst::insert(int value)
{
	if (!root)
	{
		root = new node{ value,NULL,NULL };
	}
	else
	{
		insert_impl(root, value);
	}
}
node* Bst::find(int value)
{
	return find_impl(root, value);
}
void Bst::inorder()
{
	inorder_impl(root);
}
node* Bst::successor(node* start)
{
	auto current = start->right;
	while (current && current->left)
	{
		current = current->left;
	}
	return current;
}
void Bst::deleteValue(int value)
{
	root = delete_impl(root, value);
}
node* Bst::delete_impl(node* start, int value)
{
	if (!start)
	{
		return NULL;
	}

	if (value < start->data)
	{
		start->left = delete_impl(start->left,value);
	}
	else if (value > start->data)
	{
		start->right = delete_impl(start->right, value);
	}
	else
	{
		if (!start->left)		//자식노드가 전혀없거나 왼쪽만 있을때
		{
			auto tmp = start->right;
			delete start;
			return tmp;
		}

		if (!start->right)
		{
			auto tmp = start->left;
			delete start;
			return tmp;
		}

		//자식 노드가 둘다있을때
		auto succNode = successor(start);
		start->data = succNode->data;

		//오른쪽 서브트리에서 후속을 찾아서 삭제
		start->right = delete_impl(start->right, succNode->data);
	}
	return start;
}
