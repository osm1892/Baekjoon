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

    int n = 0;
    cin >> n;
    cin.ignore();

    vector<int> arr(n);
    for (auto &i: arr) {
        cin >> i;
        cin.ignore();
    }

    sort(arr.begin(), arr.end());

    auto left = arr.begin();
    auto right = arr.begin();

    ll count = 0;
    while (true) {
        right++;
        while (*left < *right * 0.9) {
            left++;
        }
        if (right == arr.end()) {
            break;
        }
        count += right - left;
    }

    cout << count << endl;
}