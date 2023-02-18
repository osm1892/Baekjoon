#include <bits/stdc++.h>

using namespace std;

int main() {
    int arr[10] = {0};
    int sum[10] = {0};
    
    for (int i = 0; i < 10; i++) {
        cin >> arr[i];
        cin.ignore();
    }
    
    sum[0] = arr[0];
    for (int i = 1; i < 10; i++) {
        sum[i] = arr[i] + sum[i - 1];
    }
    
    int minIdx = 0;
    int minVal = 100000;
    for (int i = 0; i < 10; i++) {
        if (abs(sum[i] - 100) <= minVal) {
            minVal = abs(sum[i] - 100);
            minIdx = i;
        }
    }
    
    cout << sum[minIdx];
}