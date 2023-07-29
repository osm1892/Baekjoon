import sys
import collections

read = sys.stdin.readline
write = sys.stdout.write

neighbors = [
    [7],
    [2, 4],
    [1, 3, 5],
    [2, 6],
    [1, 5, 7],
    [2, 4, 6, 8],
    [3, 5, 9],
    [0, 4, 8],
    [5, 7, 9],
    [6, 8],
]

dp = [[0 for i in range(10)] for j in range(1001)]
dp[1] = [1 for i in range(10)]

for i in range(2, 1001):
    for j in range(10):
        for neighbor in neighbors[j]:
            dp[i][j] += dp[i - 1][neighbor]
        dp[i][j] %= 1234567

test_case = int(read())

for t in range(test_case):
    n = int(read())
    write(f"{sum(dp[n]) % 1234567}\n")
