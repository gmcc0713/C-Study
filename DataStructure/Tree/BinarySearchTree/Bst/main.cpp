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

	cout << "중위 순회 : ";
	tree.inorder();
	cout << endl;

	tree.deleteValue(12);
	cout << "12를 삭제한 후 중위 순회 : ";
	tree.inorder();
	cout << endl;

	if (tree.find(12))
	{
		cout << "12가 있다."<<endl;
	}
	else
	{
		cout << "12가 없다" << endl;
	}
}