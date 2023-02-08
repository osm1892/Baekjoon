n = int(input())

positive = [0 for i in range(1000002)]
negative = [0 for i in range(1000002)]
positive[1] = 1
negative[1] = 1

for i in range(2, 1000001):
    positive[i] = (positive[i - 1] + positive[i - 2]) % 1000000000
    negative[i] = negative[i - 2] - negative[i - 1]

    if negative[i] < 0:
        negative[i] = -((-negative[i]) % 1000000000)
    else:
        negative[i] = negative[i] % 1000000000

if n < 0:
    n = -n
    if negative[n] < 0:
        print(-1)
    else:
        print(1)
    print(abs(negative[n]))
elif n > 0:
    print(1)
    print(positive[n])
else:
    print("0\n0")