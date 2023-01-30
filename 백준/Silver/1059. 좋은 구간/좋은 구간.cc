#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
ll gcd(ll a, ll b) { for (; b; a %= b, swap(a, b)); return a; }
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
#define INF 10987654321

int main(void)
{
   ios::sync_with_stdio(0);
   cin.tie(0), cout.tie(0);
   ll m; cin >> m;
   vector<ll> a(m);
   for (ll i = 0; i < m; i++) cin >> a[i];
   sort(a.begin(), a.end());
   ll n; cin >> n;
   for (ll i = 0; i < m; i++)
   {
      if (a[i] == n)
      {
         cout << 0;
         return 0;
      }
      else if (a[i] > n)
      {
         ll left, ans = 0;
         if (i == 0) left = 1;
         else left = a[i - 1] + 1;
         for (ll res = left; res <= n; res++)
         {
            ll tmp = max(res + 1, n);
            ans += max(0ll, a[i] - 1 - tmp + 1);
         }
         cout << ans;
         return 0;
      }
   }
}