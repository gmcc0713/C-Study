#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

#define TRUE 1
typedef struct Queue
{
	int data;
	struct Queue* link;
}Queue;

Queue* Dequeue(Queue* front);
Queue* Enqueue(Queue* rear);
void Release(Queue* front,Queue* rear);
void PrintMenu();
void PrintFrontRear(Queue* front, Queue* rear);

void PrintFrontRear(Queue* front, Queue* rear)
{
	printf("front : %d   rear : %d\n", front->data, rear->data);
	system("pause");
}
Queue* Dequeue(Queue* front)
{
	Queue* tmp = NULL;
	tmp = front->link;
	free(front);
	return tmp;
}
void PrintMenu()
{
	printf("====Queue System====\n");
	printf("1.  Enqueue\n");
	printf("2.  Dequeue\n");
	printf("3.  Exit\n");
	printf("====================\n");
	printf("입력 : ");
}
Queue* Enqueue(Queue* rear)
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	printf("데이터 입력 : ");
	scanf("%d", &queue->data);
	if (rear != NULL)
		rear->link = queue;
	rear = queue;
	rear->link = NULL;
	return rear;
}
void Release(Queue* front, Queue* rear)
{
	while (front != NULL)
	{
		PrintFrontRear(front, rear);
		front = Dequeue(front);
	}
}

void main()
{
	Queue* front = NULL;
	Queue* rear = NULL;
	int num;
	while (TRUE)
	{
		system("cls");
		PrintMenu();
		scanf("%d", &num);
		switch (num)
		{
		case 1:
			rear = Enqueue(rear);
			if (front == NULL)
				front = rear;
			PrintFrontRear(front, rear);
			break;
		case 2:
			if (front == NULL)
			{
				printf("삭제할 데이터가 없습니다.\n");
				system("pause");
			}
			else
			{
				PrintFrontRear(front, rear);
				front = Dequeue(front);
				if (front == NULL)
					rear->link = NULL;
			}
			break;
		case 3:
			Release(front,rear);
			return;
		}
	}
}