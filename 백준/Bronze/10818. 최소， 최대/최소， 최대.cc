#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n = 0;
    cin >> n;
    cin.ignore();

    int max = -1000000, min = 1000000;
    int cur = 0;
    for (int i = 0; i < n; i++) {
        cin >> cur;
        cin.ignore();

        if (max < cur) {
            max = cur;
        }
        if (min > cur) {
            min = cur;
        }
    }

    cout << min << ' ' << max << endl;
}
