#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int d1 = 0, d2 = 0;
    cin >> d1 >> d2;
    cin.ignore();

    unordered_set<double> radiusSet;
    int count = 0;

    for (int i = d1; i <= d2; i++) {
        for (int j = 0; j < i; j++) {
            double radius = 1.0 * j / i;

            if (radiusSet.count(radius)) {
                continue;
            }

            count++;
            radiusSet.insert(radius);
        }
    }

    cout << count << endl;
}