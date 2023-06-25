#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

/* [💭] [💡] [🎈] */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n = 0;
    cin >> n;
    cin.ignore();

    vector<vector<bool>> dp(n + 1, vector<bool>(2));

    dp[1][0] = true;

    if (n >= 2) {
        dp[2][1] = true;
    }

    for (int i = 3; i <= n; i++) {
        dp[i][0] = dp[i - 1][1] || dp[i - 3][1];
        dp[i][1] = dp[i - 1][0] || dp[i - 3][0];
    }

    if (dp[n][0]) {
        cout << "SK\n";
    } else {
        cout << "CY\n";
    }
}