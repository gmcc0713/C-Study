#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>

#define START_MEMORY 5

typedef struct DynamicArray
{
	int* pArray;//�迭 ������
	int MaxCount;//�ִ� �޸� ũ��
	int Count;//���� ������ ����
}DynamicArray;

void InitMemory(DynamicArray* dynamicArray)//�޸� �Ҵ�,�ʱⰪ ����
{
	dynamicArray->pArray = (int*)malloc(sizeof(int) * START_MEMORY);
	dynamicArray->MaxCount = START_MEMORY;
	dynamicArray->Count = 0;
}

void CreateMemory(DynamicArray* dynamicArray)//������ �߰��� ���� �ִ밪 ������ �迭�� ������ ���������Ϳ� �ű��
{
	//�����迭 : ������ 1.2�� ~ 1.5�� ����
	dynamicArray->MaxCount *= 1.5;
	int* NewArray = (int*)malloc(sizeof(int) * dynamicArray->MaxCount);

	for (int i = 0; i < dynamicArray->Count; i++)
		NewArray[i] = dynamicArray->pArray[i];

	free(dynamicArray->pArray);
	dynamicArray->pArray = NewArray;
}

void AddData(DynamicArray* dynamicArray)//������ �߰�
{
	if (dynamicArray->Count >= dynamicArray->MaxCount)
	{
		CreateMemory(dynamicArray);
		printf("\n�̻�Ϸ�\n");
	}
	dynamicArray->pArray[dynamicArray->Count++] = rand() % 100 + 1;
}

void PrintData(DynamicArray dynamicArray)//������ ���
{
	for (int i = 0; i < dynamicArray.Count; i++)
		printf("%4d", dynamicArray.pArray[i]);
	printf("\n");
}

void LeftMoveData(DynamicArray* dynamicArray, int i)//������ ������ ������ ������ �������̵�
{
	int max = dynamicArray->Count - 1;
	for (; i < max; i++)
	{
		dynamicArray->pArray[i] = dynamicArray->pArray[i + 1];
	}
}

void DeleteData(DynamicArray* dynamicArray, int Data)//������ ����,�޸𸮴� ���� �Ұ�
{

	for (int i = 0; i < dynamicArray->Count; i++)
	{
		if (dynamicArray->pArray[i] == Data)
		{
			LeftMoveData(dynamicArray, i);
			--dynamicArray->Count;
			break;
		}
	}
}

void main()
{
	srand(time(NULL));
	DynamicArray dynamicArray;
	InitMemory(&dynamicArray);

	for (int i = 0; i < 10; i++)
		AddData(&dynamicArray);

	PrintData(dynamicArray);

	DeleteData(&dynamicArray, 30);
	PrintData(dynamicArray);

	free(dynamicArray.pArray);
}
