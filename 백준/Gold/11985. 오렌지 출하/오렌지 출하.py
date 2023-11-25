import sys

read = sys.stdin.readline
write = sys.stdout.write

n, m, k = map(int, read().split())
arr = [0] + [int(read()) for _ in range(n)]
dp = [1e64] * (n + 1)
dp[0] = 0

for i in range(1, n + 1):
    for j in range(max(i - m, 0), i):
        curs = arr[j + 1 : i + 1]
        price = k + len(curs) * (max(curs) - min(curs))
        dp[i] = min(dp[i], dp[j] + price)

print(dp[n])
