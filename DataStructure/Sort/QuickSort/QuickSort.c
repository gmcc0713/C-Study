#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<stdlib.h>

#define NUMSIZE 8
#define TRUE 1
#define DESC 1
#define ASC 2
void PrintMenu(int randomnum[]);
void Swap(int randomnum[], int i, int j);
void MakeRandomNum(int randomnum[]);
void Partition(int randomnum[], int left, int right, int sorttype);
void Ascending(int randomnum[]);
void Descending(int randomnum[]);

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
void Swap(int randomnum[], int i, int j)
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
void Partition(int randomnum[],int left,int right,int sorttype)
{
	int pivot = right;
	int low = left;
	int high = right - 1;
	if (left < right)
	{
		while (low <= high)
		{
			while ((randomnum[low] <= randomnum[pivot] && low < right&&sorttype == ASC)|| (randomnum[low] > randomnum[pivot] && low < right && sorttype == DESC))
				low++;
			while ((randomnum[high] >= randomnum[pivot] && high >= left&& sorttype == ASC)||(randomnum[high] < randomnum[pivot] && high >= left && sorttype == DESC))
				high--;
			if (low < high)
				Swap(randomnum, low, high);
			else
			{
				Swap(randomnum, low, pivot);
				break;
			}
		}
	}
	else
		return;
	Partition(randomnum,left,low-1, sorttype);
	Partition(randomnum, low + 1, right, sorttype);
}
void Ascending(int randomnum[])
{
	Partition(randomnum, 0, NUMSIZE - 1, ASC);
}
void Descending(int randomnum[])
{
	Partition(randomnum, 0, NUMSIZE - 1, DESC);
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