#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

int N, M; 
int answer;

int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

void BFS(vector<vector<int>>& vecMap)
{
	queue<pair<int, int>> q;

	for (int i = 0; i < vecMap.size(); i++)
	{
		for (int j = 0; j < vecMap[i].size(); j++)
		{
			if (vecMap[i][j] == 2)
			{
				q.emplace(i, j); // q.push(pair<int, int>(i, j));
			}
		}
	}

	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int next_x = x + dx[i];
			int next_y = y + dy[i];

			if (next_x > -1 && next_x < vecMap.size() && next_y > -1 && next_y < vecMap[x].size() && vecMap[next_x][next_y] == 0)
			{
				q.emplace(next_x, next_y);
				vecMap[next_x][next_y] = 2;
			}
		}
	}

	int cnt = 0;
	for (int i = 0; i < vecMap.size(); i++)
	{
		for (int j = 0; j < vecMap[i].size(); j++)
		{
			if (vecMap[i][j] == 0)
			{
				cnt++;
			}
		}
	}

	answer = max(answer, cnt);
}

void DFS(vector<vector<int>> vecMap, int x, int y, int cnt)
{
	vecMap[x][y] = 1;

	// 벽을 3개 다 세웠으면 BFS
	if (cnt == 0)
	{
		BFS(vecMap);
		return;
	}

	for (int i = 0; i < vecMap.size(); i++)
	{
		for (int j = 0; j < vecMap[i].size(); j++)
		{
			if (vecMap[i][j] == 0)
			{
				DFS(vecMap, i, j, cnt - 1);
			}
		}
	}
}

int main()
{
	cin >> N >> M;

	vector<vector<int>> vecMap(N, vector<int>(M));

	// 맵을 입력받음
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			int nTemp;
			cin >> nTemp;
			vecMap[i][j] = nTemp;
		}
	}

	// DFS로 벽을 세울수 있는 모든 경로 탐색
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (vecMap[i][j] == 0)
			{
				DFS(vecMap, i, j, 2);
			}
		}
	}

	cout << answer << '\n';

	return 0;
}