#include <iostream>
#include "Bst.h"
using namespace std;

void main()
{
	Bst tree;
	tree.insert(12);
	tree.insert(10);
	tree.insert(20);
	tree.insert(8);
	tree.insert(11);
	tree.insert(15);
	tree.insert(28);
	tree.insert(4);
	tree.insert(2);

	cout << "���� ��ȸ : ";
	tree.inorder();
	cout << endl;

	tree.deleteValue(12);
	cout << "12�� ������ �� ���� ��ȸ : ";
	tree.inorder();
	cout << endl;

	if (tree.find(12))
	{
		cout << "12�� �ִ�."<<endl;
	}
	else
	{
		cout << "12�� ����" << endl;
	}
}