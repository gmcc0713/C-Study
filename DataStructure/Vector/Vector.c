#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>

#define START_MEMORY 5

typedef struct DynamicArray
{
	int* pArray;//배열 포인터
	int MaxCount;//최대 메모리 크기
	int Count;//현재 데이터 갯수
}DynamicArray;

void InitMemory(DynamicArray* dynamicArray)//메모리 할당,초기값 설정
{
	dynamicArray->pArray = (int*)malloc(sizeof(int) * START_MEMORY);
	dynamicArray->MaxCount = START_MEMORY;
	dynamicArray->Count = 0;
}

void CreateMemory(DynamicArray* dynamicArray)//데이터 추가를 위해 최대값 증가된 배열을 만든후 기존데이터에 옮기기
{
	//가변배열 : 기존의 1.2배 ~ 1.5배 증설
	dynamicArray->MaxCount *= 1.5;
	int* NewArray = (int*)malloc(sizeof(int) * dynamicArray->MaxCount);

	for (int i = 0; i < dynamicArray->Count; i++)
		NewArray[i] = dynamicArray->pArray[i];

	free(dynamicArray->pArray);
	dynamicArray->pArray = NewArray;
}

void AddData(DynamicArray* dynamicArray)//데이터 추가
{
	if (dynamicArray->Count >= dynamicArray->MaxCount)
	{
		CreateMemory(dynamicArray);
		printf("\n이사완료\n");
	}
	dynamicArray->pArray[dynamicArray->Count++] = rand() % 100 + 1;
}

void PrintData(DynamicArray dynamicArray)//데이터 출력
{
	for (int i = 0; i < dynamicArray.Count; i++)
		printf("%4d", dynamicArray.pArray[i]);
	printf("\n");
}

void LeftMoveData(DynamicArray* dynamicArray, int i)//삭제힐 데이터 삭제후 나머지 데이터이동
{
	int max = dynamicArray->Count - 1;
	for (; i < max; i++)
	{
		dynamicArray->pArray[i] = dynamicArray->pArray[i + 1];
	}
}

void DeleteData(DynamicArray* dynamicArray, int Data)//데이터 삭제,메모리는 삭제 불가
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
