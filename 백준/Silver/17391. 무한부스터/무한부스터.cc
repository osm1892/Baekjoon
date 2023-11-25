#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n = 0, m = 0;
    cin >> n >> m;
    cin.ignore();

    vector<vector<int>> arr(n, vector<int>(m));
    vector<vector<int>> visit(n, vector<int>(m, -1));

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            cin >> arr[y][x];
            cin.ignore();
        }
    }

    deque<tuple<int, int, int>> queue;

    queue.emplace_back(0, 0, 0);

    while (!queue.empty()) {
        int y = 0, x = 0, depth = 0;
        tie(y, x, depth) = queue.front();
        queue.pop_front();

        if (y == n - 1 && x == m - 1) {
            cout << depth << "\n";
            break;
        }

        int booster = arr[y][x];

        for (int i = 1; i <= booster; i++) {
            if (y + i >= n) {
                break;
            }
            if (visit[y + i][x] != -1) {
                continue;
            }
            queue.emplace_back(y + i, x, depth + 1);
            visit[y + i][x] = depth + 1;
        }
        for (int i = 1; i <= booster; i++) {
            if (x + i >= m) {
                break;
            }
            if (visit[y][x + i] != -1) {
                continue;
            }
            queue.emplace_back(y, x + i, depth + 1);
            visit[y][x + i] = depth + 1;
        }
    }
}