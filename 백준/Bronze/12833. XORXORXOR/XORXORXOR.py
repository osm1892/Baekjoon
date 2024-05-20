a, b, c = map(int, input().split())

if c & 1 == 0:
    print(a)
else:
    print(a ^ b)
