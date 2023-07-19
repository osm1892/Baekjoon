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

    int k = 0, l = 0, n = 0;
    cin >> k >> l >> n;
    cin.ignore();

    string stream;
    cin >> stream;
    cin.ignore();

    int state = 0;
    int enterTimer = 0;
    int leaveTimer = 0;
    deque<int> flush;

    for (int i = 0; i < n; i++) {
        char cur = stream[i];

        if (state == 0) {
            if (cur == '1') {
                state = 1;
                enterTimer++;

                if (enterTimer == k) {
                    state = 2;
                    enterTimer = 0;
                }
            }
            continue;
        }

        if (state == 1) {
            if (cur == '1') {
                enterTimer++;
                if (enterTimer == k) {
                    state = 2;
                    enterTimer = 0;
                }
            } else {
                enterTimer = 0;
                state = 0;
            }
            continue;
        }

        if (state == 2) {
            if (cur == '1') {
                leaveTimer = 0;
            } else {
                leaveTimer++;
                if (leaveTimer >= l) {
                    leaveTimer = 0;
                    flush.push_back(i + 1);
                    state = 0;
                }
            }
        }
    }

    if (state == 2) {
        flush.push_back(n + l - leaveTimer);
    }

    if (!flush.empty()) {
        for (auto &i : flush) {
            cout << i << endl;
        }
    } else {
        cout << "NIKAD" << endl;
    }
}