#include <stdio.h>
#include <stdlib.h>
#include<Windows.h>

#define TRUE 1
typedef struct Stack
{
	int data;
	struct Stack* link;
}Stack;

Stack* Pop(Stack* top);
Stack* Push(Stack* top);
void PrintMenu();
void Release(Stack* top);

void PrintMenu()
{
	printf("====Stack System====\n");
	printf("1. push\n");
	printf("2. pop\n");
	printf("3. exit\n");
	printf("===================\n");
	printf("�Է� : ");
}
Stack* Pop(Stack* top)
{
	Stack* tmp = NULL;
	if (top == NULL)
	{
		printf("���̻� ������ �����Ͱ� �����ϴ�.\n");
		return top;
	}
	else
	{
		printf("pop : %d\n", top->data);
		tmp = top->link;
		free(top);
		return tmp;
	}
		
}
void Release(Stack* top)
{
	while(top!=NULL)
		top = Pop(top);
}
Stack* Push(Stack* top)
{
	Stack* stack = NULL;
	stack = (Stack*)malloc(sizeof(Stack));
	printf("������ �Է� : ");
	scanf("%d", &stack->data);
	stack->link = top;
	top = stack;
	return top;
}
void main()
{
	Stack* top=NULL;
	int num;
	while (TRUE)
	{
		system("cls");
		PrintMenu();
		scanf("%d", &num);
		switch (num)
		{
		case 1:
			top = Push(top);
			break;
		case 2:
			top = Pop(top);
			system("pause");
			break;
		case 3:
			Release(top);
			return;
		}
	}
}