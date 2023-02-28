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

    int dy[4] = {1, 0, -1, 0};
    int dx[4] = {0, 1, 0, -1};

    int c = 0, r = 0;
    int k = 0;

    cin >> c >> r >> k;
    cin.ignore();

    if (k > c * r) {
        cout << "0" << endl;
        return 0;
    }

    vector<vector<int>> arr(r, vector<int>(c, -1));
    arr[0][0] = 1;

    int y = 0, x = 0;
    int d = 0;
    for (int i = 2; i <= k; i++) {
        int ny = y + dy[d];
        int nx = x + dx[d];
        if (ny < 0 || r <= ny || nx < 0 || c <= nx || arr[ny][nx] != -1) {
            i -= 1;
            d = (d + 1) % 4;
            continue;
        }
        y = ny;
        x = nx;
        arr[y][x] = i;
    }
    cout << x + 1 << ' ' << y + 1 << endl;
}