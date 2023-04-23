#pragma once
#include<iostream>

#include"MyQueue.h"


using namespace std;

void main()
{
	MyQueue myQueue(3);
	//myQueue.deQueue();//오류발생 : queue가 비어있다
	myQueue.enQueue(1);
	cout << myQueue << endl;
	myQueue.enQueue(2);
	cout << myQueue << endl;
	myQueue.enQueue(3);
	cout << myQueue << endl;
	//myQueue.enQueue(4);//오류발생 : queue가 꽉 찼다
	myQueue.deQueue();			

	/*cout<<"front : " << myQueue.Front() << endl;
	cout<<"rear : " << myQueue.Back() << endl;*/
	cout << myQueue << endl;
	return;
}