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

    string data;
    cin >> data;
    cin.ignore();

    vector<pair<int, int>> dp(data.size() + 1);
    dp[0].second = 1;

    for (int i = 1; i <= data.size(); i++) {
        if (islower(data[i - 1])) {
            dp[i].first = min(dp[i - 1].first + 1, dp[i - 1].second + 2);
            dp[i].second = min(dp[i - 1].first + 3, dp[i - 1].second + 2);
        } else {
            dp[i].first = min(dp[i - 1].first + 2, dp[i - 1].second + 3);
            dp[i].second = min(dp[i - 1].first + 2, dp[i - 1].second + 1);
        }
    }

    cout << min(dp[data.size()].first, dp[data.size()].second) << endl;
}