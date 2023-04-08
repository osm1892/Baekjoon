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

    int guns = 0, animals = 0, range = 0;
    cin >> guns >> animals >> range;
    cin.ignore();

    vector<int> gunArr(guns);

    for (int i = 0; i < guns; i++) {
        cin >> gunArr[i];
        cin.ignore();
    }

    sort(gunArr.begin(), gunArr.end());

    int count = 0;
    for (int i = 0; i < animals; i++) {
        int x = 0, y = 0;
        cin >> x >> y;
        cin.ignore();

        auto right = lower_bound(gunArr.begin(), gunArr.end(), x);

        if (right == gunArr.end()) {
            right -= 1;
        }

        auto left = right - 1;

        int rightDist = *right - x + y;
        int leftDist = x - *left + y;

        if (range < leftDist && range < rightDist) {
            continue;
        }
        count++;
    }

    cout << count << endl;
}