N = int(input())
paper = [[0 for x in range(100)] for y in range(100)]

for n in range(N):
    x, y = map(int, input().split())

    for i in range(y, y + 10):
        for j in range(x, x + 10):
            paper[i][j] = 1

print(sum([sum(k) for k in paper]))