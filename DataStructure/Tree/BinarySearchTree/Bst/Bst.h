#pragma once
#include <iostream>
using namespace std;
struct node
{
	int data;
	node* left;
	node* right;
};
class Bst
{
private:
private:
	node* root = nullptr;
	node* find_impl(node* current, int value);
	void insert_impl(node* current, int value);
	void inorder_impl(node* start);
	node* delete_impl(node* start, int value);
public:
	void deleteValue(int value);
	void insert(int value);
	node* find(int value);
	void inorder();
	node* successor(node* start);
};

