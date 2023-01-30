#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef unsigned long long ull;
typedef pair<double, double> pdd;
typedef vector<vector<ll>> vll;
int dx[6] = { 1, 1, 0, 0, 1, 1 };
int dy[6] = { -1, 1, -1, 1, -1, 1 };
ll gcd(ll a, ll b) { for (; b; a %= b, swap(a, b)); return a; }

int main(void)
{
   ios::sync_with_stdio(0);
   cin.tie(0), cout.tie(0);
   for (ll i = 0; i < 3; i++)
   {
      ll h1, m1, s1, h2, m2, s2;
      cin >> h1 >> m1 >> s1 >> h2 >> m2 >> s2;
      ll len = (h2 - h1) * 3600 + (m2 - m1) * 60 + (s2 - s1);
      cout << len / 3600 << ' '; len %= 3600;
      cout << len / 60 << ' '; len %= 60;
      cout << len << "\n";
   }
}