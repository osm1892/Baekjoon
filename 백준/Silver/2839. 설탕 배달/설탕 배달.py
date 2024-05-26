import sys
import collections

read = sys.stdin.readline
# read = open("input.txt", "rt").readline
write = sys.stdout.write


def main():
    n = int(read())
    dp = [-1 for _ in range(500001)]
    dp[3] = 1
    dp[5] = 1

    for i in range(6, 500001):
        res = 1e9
        for j in [3, 5]:
            if dp[i - j] != -1:
                res = min(res, dp[i - j] + 1)
        if res != 1e9:
            dp[i] = res
    
    print(dp[n])


main()
