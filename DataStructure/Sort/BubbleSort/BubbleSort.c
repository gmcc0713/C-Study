#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<stdlib.h>

#define NUMSIZE 10
#define TRUE 1

void MakeRandomNum(int randomnum[]);
void Ascending(int randomnum[]);
void Descending(int randomnum[]);
void PrintMenu(int randomnum[]);
void Swap(int randomnum[], int i, int j);

void PrintMenu(int randomnum[])
{
	for (int i = 0; i < NUMSIZE; i++)
		printf("%d ", randomnum[i]);
	printf("\n1. 번호 생성\n");
	printf("2. 오름차순 정렬\n");
	printf("3. 내림차순 정렬\n");
	printf("4. 종료\n");
	printf("선택 : ");
}
void MakeRandomNum(int randomnum[])
{
	for (int i = 0; i < NUMSIZE; i++)
		randomnum[i] = rand() % 100 + 1;
}
void Swap(int randomnum[], int i, int j)
{
	int tmp;
	tmp = randomnum[j];
	randomnum[j] = randomnum[i];
	randomnum[i] = tmp;
}
void Ascending(int randomnum[])
{
	for (int i = 0; i < NUMSIZE; i++)
	{
		for (int j = 0; j < NUMSIZE-i-1; j++)
		{
			if (randomnum[j] > randomnum[j + 1])
				Swap(randomnum,j,j + 1);
		}
	}
}
void Descending(int randomnum[])
{
	for (int i = 0; i < NUMSIZE; i++)
	{
		for (int j = 0; j < NUMSIZE - i - 1; j++)
		{
			if (randomnum[j] < randomnum[j + 1])
				Swap(randomnum, j, j + 1);
		}
	}
}
void main()
{
	srand(time(NULL));
	int randomnum[NUMSIZE] = { 0 };
	int selectnum;
	while (TRUE)
	{
		system("cls");
		PrintMenu(randomnum);
		scanf("%d", &selectnum);
		switch (selectnum)
		{
		case 1:
			MakeRandomNum(randomnum);
			break;
		case 2:
			Ascending(randomnum);
			break;
		case 3:
			Descending(randomnum);
			break;
		case 4:
			return;
		}
	}
}