import sys

read = sys.stdin.readline
write = sys.stdout.write

n, d = map(int, read().split())
hs = list(map(int, read().split()))

max_building = max(hs)

count = 0
dest_level = max(max_building - d, 0)
hs.append(dest_level)
hs.sort(reverse=True)
for i in range(1, n + 1):
    if hs[i] < max_building:
        count += i * (max_building - hs[i])
        max_building = hs[i]

    if hs[i] == dest_level:
        break

print(count)