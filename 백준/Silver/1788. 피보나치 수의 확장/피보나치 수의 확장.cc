#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n = 0;
  const int zero = 1000000, mod = 1000000000;
  
  cin >> n;
  getchar();
  
  n += zero;
  
  vector<int> dp(2 * zero + 1);
  
  dp[zero] = 0;
  dp[zero + 1] = 1;
  dp[zero - 1] = 1;
  
  for (int i = zero + 2; i <= 2 * zero; i++)
  {
    dp[i] = (dp[i - 2] + dp[i - 1]) % mod;
  }
  for (int i = zero - 2; i >= 0; i--)
  {
    dp[i] = dp[i + 2] - dp[i + 1];
    
    if (dp[i] < 0)
    {
      dp[i] = -(-dp[i] % mod);
    }
    else
    {
      dp[i] %= mod;
    }
  }
  
  if (dp[n] < 0)
  {
    cout << -1 << endl;
  }
  else if (dp[n] == 0)
  {
    cout << 0 << endl;
  }
  else
  {
    cout << 1 << endl;
  }
  
  cout << abs(dp[n]) << endl;
}