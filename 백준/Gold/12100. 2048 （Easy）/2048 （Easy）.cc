#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <deque>
#include <vector>
#include <tuple>
#include <cstdlib>

using namespace std;

void Rotate(vector<vector<int>> &arr, int count) {
    if (count == 0) {
        return;
    }
    int n = arr.size();
    vector<vector<int>> tmp(arr);
    if (count == 1) {
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                arr[y][x] = tmp[n - 1 - x][y];
            }
        }
    } else if (count == 2) {
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                arr[y][x] = tmp[n - 1 - y][n - 1 - x];
            }
        }
    } else if (count == 3) {
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                arr[y][x] = tmp[x][n - 1 - y];
            }
        }
    }
}

int DFS(vector<vector<int>> arr, int depth, int dir) {
    Rotate(arr, dir);

    for (auto &y: arr) {
        auto removed = std::remove(y.begin(), y.end(), 0);
        for (; removed != y.end(); removed++) {
            *removed = 0;
        }
        for (int x = 0; x < arr.size() - 1; x++) {
            if (y[x] == y[x + 1]) {
                y[x] *= 2;
                y[x + 1] = 0;
            }
        }
        removed = std::remove(y.begin(), y.end(), 0);
        for (; removed != y.end(); removed++) {
            *removed = 0;
        }
    }

    Rotate(arr, 4 - dir);

    int res = 0;

    if (depth == 5) {
        for (auto &y: arr) {
            for (auto &x: y) {
                res = max(res, x);
            }
        }

        return res;
    }

    for (int d = 0; d < 4; d++) {
        res = max(res, DFS(arr, depth + 1, d));
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n = 0;
    cin >> n;
    cin.ignore();

    vector<vector<int>> arr(n, vector<int>(n));
    for (auto &y: arr) {
        for (auto &x: y) {
            cin >> x;
            cin.ignore();
        }
    }

    int res = 0;
    for (int d = 0; d < 4; d++) {
        res = max(res, DFS(arr, 1, d));
    }

    cout << res << endl;
    return 0;
}