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

    int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1,};
    int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    int n = 0, m = 0, k = 0;
    cin >> n >> m >> k;
    cin.ignore();

    vector<string> arr(n);
    map<string, int> steps;
    queue<pair<pair<int, int>, int>> que;

    for (auto &line: arr) {
        cin >> line;
        cin.ignore();
    }

    string dest;
    for (int i = 0; i < k; i++) {
        cin >> dest;
        cin.ignore();

        if (steps.contains(dest)) {
            cout << steps[dest] << endl;
            continue;
        }

        for (int y = 0; y < n; y++) {
            for (int x = 0; x < m; x++) {
                if (arr[y][x] == dest[0]) {
                    que.emplace(make_pair(y, x), 1);
                }
            }
        }

        while (!que.empty()) {
            auto cur = que.front();
            auto pos = cur.first;
            int depth = cur.second;
            que.pop();

            if (depth == dest.size()) {
                steps[dest] += 1;
                continue;
            }

            for (int dir = 0; dir < 8; dir++) {
                int ny = (pos.first + (n + dy[dir])) % n;
                int nx = (pos.second + (m + dx[dir])) % m;

                if (arr[ny][nx] == dest[depth]) {
                    que.emplace(make_pair(ny, nx), depth + 1);
                }
            }
        }

        cout << steps[dest] << endl;
    }
}