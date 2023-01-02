h, w = map(int, input().split())

arr = [input() for _ in range(h)]
caster = [[0] * w for _ in range(h)]

for y in range(h):
    hour_count = -1
    for x in range(w):
        if arr[y][x] == 'c':
            hour_count = 0
        
        caster[y][x] = hour_count
        
        if hour_count >= 0:
            hour_count += 1

for i in caster:
    for j in i:
        print(j, end = ' ')
    print()