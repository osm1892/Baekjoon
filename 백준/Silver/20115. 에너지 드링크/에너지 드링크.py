import sys

read = sys.stdin.readline
write = sys.stdout.write

n = int(read())
arr = list(map(int, read().split()))
arr.sort()
print(arr[-1] + sum(arr[:-1]) / 2)
