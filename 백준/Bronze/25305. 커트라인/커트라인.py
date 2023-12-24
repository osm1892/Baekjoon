import sys

read = sys.stdin.readline
write = sys.stdout.write

n, k = map(int, read().split())
scores = list(map(int, read().split()))
scores.sort(reverse=True)
print(scores[k - 1])
