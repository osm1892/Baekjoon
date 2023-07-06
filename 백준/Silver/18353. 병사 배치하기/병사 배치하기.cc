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

    vector<ll> powers(n);
    for (auto &i: powers) {
        cin >> i;
        cin.ignore();
    }

    reverse(powers.begin(), powers.end());

    vector<int> dp(n, 1);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (powers[j] >= powers[i]) {
                continue;
            }
            dp[i] = max(dp[j] + 1, dp[i]);
        }
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        result = max(result, dp[i]);
    }
    result = n - result;

    cout << result << endl;
}