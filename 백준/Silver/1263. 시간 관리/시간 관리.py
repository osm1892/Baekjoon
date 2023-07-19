import sys

read = sys.stdin.readline
write = sys.stdout.write

n = int(read())
works = [list(map(int, read().split())) for i in range(n)]
works.sort(key=lambda x: (-x[1], -x[0]))
start_time = works[0][1] - works[0][0]

for i in range(1, len(works)):
    t, s = works[i]
    if start_time <= s:
        start_time -= t
    else:
        start_time = s - t        

print(max(start_time, -1))