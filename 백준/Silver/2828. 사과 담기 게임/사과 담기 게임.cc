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

    int n = 0, m = 0, j = 0;
    cin >> n >> m >> j;
    cin.ignore();

    int left = 1;
    int right = left + m - 1;
    int count = 0;

    for (int i = 0; i < j; i++) {
        int pos = 0;
        cin >> pos;
        cin.ignore();

        if (left <= pos && pos <= right) {
            continue;
        }

        if (pos < left) {
            int diff = left - pos;
            left -= diff;
            right -= diff;
            count += diff;
        } else {
            int diff = pos - right;
            left += diff;
            right += diff;
            count += diff;
        }
    }

    cout << count << endl;
}