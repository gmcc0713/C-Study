// 다이나믹 프로그래밍 분할 불가능 배낭 문제 (백준 - 평범한 배낭)
/*
문제 :
배낭 문제는 n개의 물건과 각 물건 i의 무게 wi와 가치 vi가 주어지고, 배낭의 용량이 C일 때,
배낭에 담을 수 있는 물건의 최대 가치를 찾는 문제이다.
단, 배낭에 담은 물건의 무게의 합이 C를 초과하지 말아야 하고, 각 물건은 1개씩만 있다고 가정한다.
*/
#include <iostream>
#include <algorithm>
using namespace std;

void main()
{
	int DP[101][1000001] = {0};// 물건의 갯수, 가방의 최대 크기
	int n;
	int wi[101];
	int vi[101];
	int c;
	cout << "물품의 갯수, 가방의 최대 무게입력 : ";
	cin >> n>> c;

	for (int i = 1; i <= n; i++)
	{
		cout << i  << "번쨰 물품( 무게 가치)입력 : ";
		cin >> wi[i]>> vi[i];
	}


	//dp[i][j] = 자기의 전번째 물건의 최대값(dp[i - 1][j]) 과 dp[i - 1][j - w[i]] + v[i](자신의 물건의 최대값) 중 더 큰수
	for (int i = 1; i <= n; i++)
	{

		for (int j = 1; j <= c; j++)
		{
			if (wi[i] <= j)
			{
 				DP[i][j] = max(DP[i - 1][j], DP[i - 1][j - wi[i]] + vi[i]);
			}
			else DP[i][j] = DP[i - 1][j];

		}
	}
	cout << DP[n][c];
}