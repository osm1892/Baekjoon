#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int monster = 0, user = 0;
    
    cin >> monster >> user;
    cin.ignore();
    
    cout << ((monster - monster * (0.01 * user)) < 100);
}