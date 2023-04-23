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
void Ascending(int randomnum[])
{
	int tmp;
	for (int i = 1; i < NUMSIZE; i++)
	{
		tmp = randomnum[i];
		for (int j = i - 1; j >= 0;j--)
		{
			if (randomnum[j] > tmp)
			{
				randomnum[j+1] = randomnum[j];
				if (j == 0 || randomnum[j - 1] <= tmp)
				{
					randomnum[j] = tmp;
					break;
				}
			}
		}
	}
}
/*
for (int j = i - 1;; j--)
{
	if (randomnum[j] < tmp || j < 0)
	{
		randomnum[j + 1] = tmp;
		break;
	}
	randomnum[j + 1] = randomnum[j];
}
*/
void Descending(int randomnum[])
{
	int tmp;
	for (int i = 1; i < NUMSIZE; i++)
	{
		tmp = randomnum[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (randomnum[j] < tmp)
			{
				randomnum[j + 1] = randomnum[j];
				if (j == 0 || randomnum[j - 1] >= tmp)
				{
					randomnum[j] = tmp;
					break;
				}
			}
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