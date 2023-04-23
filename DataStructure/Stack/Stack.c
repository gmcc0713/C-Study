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
	printf("입력 : ");
}
Stack* Pop(Stack* top)
{
	Stack* tmp = NULL;
	if (top == NULL)
	{
		printf("더이상 삭제할 데이터가 없습니다.\n");
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
	printf("데이터 입력 : ");
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