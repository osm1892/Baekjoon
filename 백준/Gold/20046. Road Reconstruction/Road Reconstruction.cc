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

    int dy[4] = {-1, 0, 1, 0};
    int dx[4] = {0, 1, 0, -1};

    int n = 0, m = 0;
    cin >> n >> m;
    cin.ignore();

    vector<vector<int>> arr(n, vector<int>(m));
    vector<vector<int>> dists(n, vector<int>(m, 100000));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            cin.ignore();
        }
    }

    if (arr[0][0] == -1 || arr[n - 1][m - 1] == -1) {
        cout << -1 << endl;
        return 0;
    }

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    pq.emplace(arr[0][0], 0, 0);
    dists[0][0] = arr[0][0];

    while (!pq.empty()) {
        int dist = 0, y = 0, x = 0;
        tie(dist, y, x) = pq.top();
        pq.pop();

        if (y == n - 1 && x == m - 1) {
            cout << dist << endl;
            return 0;
        }

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d];
            int nx = x + dx[d];

            if (ny < 0 || n <= ny) {
                continue;
            }
            if (nx < 0 || m <= nx) {
                continue;
            }
            if (arr[ny][nx] == -1) {
                continue;
            }
            int cost = dists[y][x] + arr[ny][nx];
            if (dists[ny][nx] <= cost) {
                continue;
            }
            dists[ny][nx] = cost;
            pq.emplace(cost, ny, nx);
        }
    }

    cout << -1 << endl;
}