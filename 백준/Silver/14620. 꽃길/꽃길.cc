#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

/* [💭] [💡] [🎈] */

class DFS {
private:
    int dy[4] = {-1, 0, 1, 0};
    int dx[4] = {0, 1, 0, -1};

    int n;
    vector<vector<int>> arr;
    vector<vector<int>> visit;
    int result = 1e9;

public:
    DFS(int n, vector<vector<int>> &arr) {
        this->n = n;
        this->arr = arr;
        visit = vector<vector<int>>(n, vector<int>(n));
    }

    int search() {
        for (int i = 1; i < n - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                visit[i][j]++;
                int totalPrice = arr[i][j];
                for (int d = 0; d < 4; d++) {
                    visit[i + dy[d]][j + dx[d]]++;
                    totalPrice += arr[i + dy[d]][j + dx[d]];
                }
                recursive(totalPrice, 1);
                visit[i][j]--;
                for (int d = 0; d < 4; d++) {
                    visit[i + dy[d]][j + dx[d]]--;
                }
            }
        }

        return result;
    }

    void recursive(int price, int depth) {
        if (depth == 3) {
            result = min(result, price);
            return;
        }

        for (int i = 1; i < n - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                bool skip = false;
                if (visit[i][j]) {
                    skip = true;
                }
                for (int d = 0; d < 4; d++) {
                    if (visit[i + dy[d]][j + dx[d]]) {
                        skip = true;
                    }
                }
                if (skip) {
                    continue;
                }

                visit[i][j]++;
                int totalPrice = arr[i][j];
                for (int d = 0; d < 4; d++) {
                    visit[i + dy[d]][j + dx[d]]++;

                    totalPrice += arr[i + dy[d]][j + dx[d]];
                }
                recursive(price + totalPrice, depth + 1);
                visit[i][j]--;
                for (int d = 0; d < 4; d++) {
                    visit[i + dy[d]][j + dx[d]]--;
                }
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n = 0;
    cin >> n;
    cin.ignore();

    vector<vector<int>> arr(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            cin.ignore();
        }
    }

    DFS dfs = DFS(n, arr);
    cout << dfs.search();
}