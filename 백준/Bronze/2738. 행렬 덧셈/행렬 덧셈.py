row, col = map(int, input().split())
a = [list(map(int, input().split())) for _ in range(row)]
b = [list(map(int, input().split())) for _ in range(row)]

for i in range(row):
    for j in range(col):
        print(a[i][j] + b[i][j], end=" ")
    print()
