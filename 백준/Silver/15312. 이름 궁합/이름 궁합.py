lines = [3, 2, 1, 2, 3, 3, 2, 3, 3, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 1, 1, 2, 2, 1]

a = list(map(lambda x: lines[ord(x) - ord("A")], input()))
b = list(map(lambda x: lines[ord(x) - ord("A")], input()))

couple = [0] * (2 * len(a))
for i in range(len(a)):
    couple[i * 2] = a[i]
    couple[i * 2 + 1] = b[i]

while len(couple) > 2:
    next_couple = [(couple[i] + couple[i + 1]) % 10 for i in range(len(couple) - 1)]
    couple = next_couple

print(couple[0], couple[1], sep="")
