#pragma once
#include<iostream>

#include"MyQueue.h"


using namespace std;

void main()
{
	MyQueue myQueue(3);
	//myQueue.deQueue();//�����߻� : queue�� ����ִ�
	myQueue.enQueue(1);
	cout << myQueue << endl;
	myQueue.enQueue(2);
	cout << myQueue << endl;
	myQueue.enQueue(3);
	cout << myQueue << endl;
	//myQueue.enQueue(4);//�����߻� : queue�� �� á��
	myQueue.deQueue();			

	/*cout<<"front : " << myQueue.Front() << endl;
	cout<<"rear : " << myQueue.Back() << endl;*/
	cout << myQueue << endl;
	return;
}