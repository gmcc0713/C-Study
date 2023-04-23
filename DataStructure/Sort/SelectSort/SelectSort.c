#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<stdlib.h>

#define NUMSIZE 10
#define TRUE 1

void PrintMenu(int randomnum[])
{
	for (int i = 0; i < NUMSIZE; i++)
		printf("%d ", randomnum[i]);
	printf("\n1. ��ȣ ����\n");
	printf("2. �������� ����\n");
	printf("2. �������� ����\n");
	printf("4. ����\n");
	printf("���� : ");
}
void Swap(int randomnum[],int i,int j)
{
	int tmp;
	tmp = randomnum[j];
	randomnum[j] = randomnum[i];
	randomnum[i] = tmp;
}
void MakeRandomNum(int randomnum[])
{
	for (int i = 0; i < NUMSIZE; i++)
		randomnum[i] = rand() % 100 + 1;
}
void Ascending(int randomnum[])
{
	for (int i = 0; i < NUMSIZE-1; i++)
	{
		for (int j = i + 1; j < NUMSIZE; j++)
		{
			if (randomnum[i] > randomnum[j])
				Swap(randomnum,i,j);
		}
	}
}
void Descending(int randomnum[])
{
	for (int i = 0; i < NUMSIZE-1; i++)
	{
		for (int j = i + 1; j < NUMSIZE; j++)
		{
			if (randomnum[i] < randomnum[j])
				Swap(randomnum,i,j);
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