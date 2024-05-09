import sys

read = sys.stdin.readline
write = sys.stdout.write

read()
a = set(map(int, read().split()))
b = set(map(int, read().split()))

res = (a - b) | (b - a)
print(len(res))
