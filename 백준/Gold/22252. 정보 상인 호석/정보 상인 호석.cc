#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

/* [💭] [💡] [🎈] */

void Solve();

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	Solve();
	return 0;
}

void Solve()
{
	int Q = 0;
	cin >> Q;
	cin.ignore();
	
	unordered_map<string, priority_queue<int>> m;
	ll result = 0;
	
	while (Q--)
	{
		int query = 0, k = 0;
		string name;
		
		
		cin >> query >> name >> k;
		cin.ignore();
		
		if (query == 1)
		{
			for (int i = 0; i < k; i++)
			{
				int c = 0;
				cin >> c;
				cin.ignore();
				m[name].push(c);
			}
		} else
		{
			for (int i = 0; i < k; i++)
			{
				if (m[name].empty())
				{
					break;
				}
				result += m[name].top();
				m[name].pop();
			}
		}
	}
	
	cout << result << endl;
}