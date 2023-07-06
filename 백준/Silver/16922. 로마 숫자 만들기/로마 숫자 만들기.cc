#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

/* [💭] [💡] [🎈] */

class Finder {
  private:
    int n;
    unordered_set<int> nums;
    int pool[4] = {1, 5, 10, 50};

  public:
    Finder(int n) { this->n = n; }

    void search(int num = 0, int cur = 0, int depth = 0) {
        if (depth == n) {
            nums.insert(num);
            return;
        }

        for (int i = cur; i < 4; i++) {
            search(num + pool[i], i, depth + 1);
        }
    }

    int getResult() { return nums.size(); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n = 0;
    cin >> n;
    cin.ignore();

    Finder finder = Finder(n);
    finder.search();
    cout << finder.getResult() << endl;
}