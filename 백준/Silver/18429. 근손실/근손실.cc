#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

/* [💭] [💡] [🎈] */

int DFS(vector<int> &arr, vector<bool> &visit, int depth, int weight, int k) {
    if (depth == arr.size()) {
        return 1;
    }

    int result = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (visit[i]) {
            continue;
        }
        int nextWeight = weight - k + arr[i];
        if (nextWeight < 500) {
            continue;
        }
        visit[i] = true;
        result += DFS(arr, visit, depth + 1, nextWeight, k);
        visit[i] = false;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n = 0, k = 0;
    cin >> n >> k;
    cin.ignore();

    vector<int> arr(n);
    vector<bool> visit(n);

    for (auto &i: arr) {
        cin >> i;
        cin.ignore();
    }

    cout << DFS(arr, visit, 0, 500, k) << endl;
}