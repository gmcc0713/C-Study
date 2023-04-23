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
		std::cout << value << "��(��) ã�ҽ��ϴ�" << std::endl;
		return current;
	}

	if (value < current->data)	//value���� ���� ��� ���ʿ� �ִ� ���
	{
		std::cout << current->data << "���� �������� �̵� : ";
		return find_impl(current->left, value);
	}
	std::cout << current->data << "���� ���������� �̵� : ";
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
		if (!start->left)		//�ڽĳ�尡 �������ų� ���ʸ� ������
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

		//�ڽ� ��尡 �Ѵ�������
		auto succNode = successor(start);
		start->data = succNode->data;

		//������ ����Ʈ������ �ļ��� ã�Ƽ� ����
		start->right = delete_impl(start->right, succNode->data);
	}
	return start;
}
