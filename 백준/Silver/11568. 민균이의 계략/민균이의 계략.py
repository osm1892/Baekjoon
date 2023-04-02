import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    n = int(read())
    arr = list(map(int, read().split()))
    dp = [1 for _ in range(n)]

    for i in range(1, n):
        for j in range(i):
            if arr[j] >= arr[i]:
                continue
            dp[i] = max(dp[i], dp[j] + 1)

    print(max(dp))


main()
