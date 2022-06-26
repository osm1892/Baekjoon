#include <bits/stdc++.h>

using namespace std;

void Solution();

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Solution();
}

void Solution()
{
    int x = 0;
    int n = 0;
    int a = 0, b = 0;
    
    cin >> x >> n;
    cin.ignore();
    
    while (n--)
    {
        cin >> a >> b;
        cin.ignore();
        
        x -= a * b;
    }
    
    if (x == 0)
    {
        cout << "Yes";
    } else
    {
        cout << "No";
    }
}