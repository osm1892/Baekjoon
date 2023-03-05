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

    int dy[2] = {0, 1};
    int dx[2] = {1, 0};

    int n = 0, m = 0;
    cin >> n >> m;
    cin.ignore();

    vector<vector<int>> arr(n, vector<int>(m));

    for (auto &y: arr) {
        for (auto &x: y) {
            cin >> x;
            cin.ignore();
        }
    }

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            int prev = 0;
            if (y) {
                prev = arr[y - 1][x];
            }
            if (x) {
                prev = max(arr[y][x - 1], prev);
            }
            arr[y][x] += prev;
        }
    }

    cout << arr[n - 1][m - 1] << endl;
}