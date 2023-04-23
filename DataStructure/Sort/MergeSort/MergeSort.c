#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<stdlib.h>

#define NUMSIZE 10
#define TRUE 1
#define DESC 1
#define ASC 2
void PrintMenu(int randomnum[])
{
	for (int i = 0; i < NUMSIZE; i++)
		printf("%d ", randomnum[i]);
	printf("\n1. 번호 생성\n");
	printf("2. 오름차순 정렬\n");
	printf("2. 내림차순 정렬\n");
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
void MergerArr(int randomnum[], int left, int right,int mid,int sorttype)
{
	int tmparr[NUMSIZE] = {0};
	int i=left,leftindex=left,rightindex=mid+1;
	while (TRUE)
	{
		if (leftindex <= mid && rightindex <= right)
		{
			if ((randomnum[leftindex] < randomnum[rightindex] && sorttype==ASC) || (randomnum[leftindex] > randomnum[rightindex] && sorttype == DESC))
				tmparr[i++] = randomnum[leftindex++];
			else
				tmparr[i++] = randomnum[rightindex++];
		}
		else if (leftindex <= mid)
			tmparr[i++] = randomnum[leftindex++];
		else if (rightindex <= right)
			tmparr[i++] = randomnum[rightindex++];
		else
		{
			for (int j = left; j <= right; j++)
				randomnum[j] = tmparr[j];
			break;
		}
	}
	
}
void DivideArr(int randomnum[],int left,int right,int sorttype)
{
	
	int mid = (left + right) / 2;
	if (left<right)
	{
		DivideArr(randomnum, left, mid,sorttype);
		DivideArr(randomnum, mid + 1, right,sorttype);
		MergerArr(randomnum, left, right,mid,sorttype);
	}

}
void Ascending(int randomnum[])
{
	DivideArr(randomnum, 0, NUMSIZE - 1,ASC);
}
void Descending(int randomnum[])
{
	DivideArr(randomnum, 0, NUMSIZE - 1,DESC);
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