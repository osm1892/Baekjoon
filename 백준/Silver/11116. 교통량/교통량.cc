#include <bits/stdc++.h>

using namespace std;

int main()
{
    int testCase = 0;
    cin >> testCase;
    cin.ignore();

    while (testCase--)
    {
        int n = 0;
        cin >> n;
        cin.ignore();

        vector<int> left(n);
        vector<int> right(n);

        for (int i = 0; i < n; i++)
        {
            cin >> left[i];
            cin.ignore();
        }
        for (int i = 0; i < n; i++)
        {
            cin >> right[i];
            cin.ignore();
        }

        int count = 0;
        for (int i = 0; i < n; i += 2)
        {
            if (left[i] < right[i])
            {
                count++;
            }
        }

        cout << count << '\n';
    }
}