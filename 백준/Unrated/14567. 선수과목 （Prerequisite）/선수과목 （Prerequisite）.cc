#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n = 0, m = 0;
    cin >> n >> m;
    cin.ignore();

    vector<vector<int>> graph(n);

    for (int i = 0; i < m; i++) {
        int a = 0, b = 0;
        cin >> a >> b;
        cin.ignore();

        graph[b - 1].push_back(a - 1);
    }

    vector<int> result(n);

    for (int i = 0; i < n; i++) {
        int maxSemester = 0;
        for (int j: graph[i]) {
            maxSemester = max(maxSemester, result[j]);
        }
        result[i] = maxSemester + 1;
    }

    for (int i: result) {
        cout << i << ' ';
    }
}