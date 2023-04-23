#include <iostream>
#include "MyQueue.h"

bool MyQueue::full()
{
	return front == (rear+1)%length;
}

bool MyQueue::empty()
{
	return rear == front;
}

void MyQueue::enQueue(int data)
{
	if (!full())
	{
		dataArray[rear] = data;
		rear = (rear + 1) % length;
		size++;
	}
	else
	{
		throw "Queue is full!!";
	}
}

int MyQueue::deQueue()
{
	if (!empty())
	{
		int retdata = dataArray[front];
		size--;
		front = (front + 1) % length;
		return retdata;
	}
	else
	{
		throw "Queue is empty!!";
	}

}

int MyQueue::Front()
{
	if (!empty())
		return dataArray[front];
	else
		throw "Queue is empty!!";
}

int MyQueue::Back()
{
	if (!empty())
		return dataArray[rear];
	else
		throw "Queue is empty!!";
}

ostream& operator << (ostream& os, const MyQueue& q)
{
	for (int i = 0; i < q.size; i++)
	{
		cout << q.dataArray[q.front+i]<< " ";
	}
	return os;
}