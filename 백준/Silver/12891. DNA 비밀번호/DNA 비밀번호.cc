#include <bits/stdc++.h>

using namespace std;

int DnaToIdx(char dna)
{
    switch (dna)
    {
    case 'A':
        return 0;
    case 'C':
        return 1;
    case 'G':
        return 2;
    case 'T':
        return 3;
    default:
        return -1;
    }
}

int Checker(int *arr, int *correct)
{
    for (int i = 0; i < 4; i++)
    {
        if (arr[i] < correct[i])
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int s = 0, p = 0;
    cin >> s >> p;
    cin.ignore();

    string dna;
    cin >> dna;
    cin.ignore();

    int acgt[4] = {0};
    for (int i = 0; i < 4; i++)
    {
        cin >> acgt[i];
        cin.ignore();
    }

    int current[4] = {0};
    int count = 0;
    for (int i = 0; i < p; i++)
    {
        current[DnaToIdx(dna[i])]++;
    }

    count += Checker(current, acgt);
    int left = 0, right = p;
    while (right < s)
    {
        current[DnaToIdx(dna[right++])]++;
        current[DnaToIdx(dna[left++])]--;
        count += Checker(current, acgt);
    }

    cout << count << '\n';
}