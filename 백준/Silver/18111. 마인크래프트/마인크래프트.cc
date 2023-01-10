#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int n = 0, m = 0, b = 0;
	int resultHeight = 0, resultTime = 1 << 30;

	cin >> n >> m >> b;
	cin.ignore();

	vector<vector<int>> arr(n, vector<int>(m));

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			cin >> arr[y][x];
			cin.ignore();
		}
	}

	for (int height = 0; height <= 256; height++)
	{
		int curTime = 0;
		int block = b;

		for (int y = 0; y < n; y++)
		{
			for (int x = 0; x < m; x++)
			{
				if (height < arr[y][x])
				{
					curTime += (arr[y][x] - height) * 2;
					block += arr[y][x] - height;
				}
				else
				{
					curTime += height - arr[y][x];
					block -= height - arr[y][x];
				}
				
			}
		}

		if (block < 0)
		{
			continue;
		}

		if (curTime <= resultTime)
		{
			resultTime = curTime;
			resultHeight = height;
		}
	}

	cout << resultTime << ' ' << resultHeight << '\n';

	return 0;
}
