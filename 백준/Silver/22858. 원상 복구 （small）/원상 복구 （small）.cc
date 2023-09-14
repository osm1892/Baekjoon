#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n = 0, k = 0;
    cin >> n >> k;

    vector<int> s(n);
    for (auto &i : s)
    {
        cin >> i;
    }
    vector<int> d(n);
    for (auto &i : d)
    {
        cin >> i;
        i -= 1;
    }

    for (int i = 0; i < k; i++)
    {
        vector<int> before(n);
        for (int j = 0; j < n; j++)
        {
            before[d[j]] = s[j];
        }
        s = before;
    }

    for (auto &i : s)
    {
        cout << i << ' ';
    }
}