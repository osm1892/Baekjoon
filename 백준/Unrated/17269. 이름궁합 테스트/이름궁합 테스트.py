def main():
    lines = [3, 2, 1, 2, 4, 3, 1, 3, 1, 1, 3, 1, 3, 2, 1, 2, 2, 2, 1, 2, 1, 1, 1, 2, 2, 1]
    n, m = map(int, input().split())
    a, b = input().split()
    combination = [0] * (n + m)

    if n > m:
        for i in range(m):
            combination[i * 2 + 1] = lines[ord(b[i]) - ord("A")]
        for i in range(m):
            combination[i * 2] = lines[ord(a[i]) - ord("A")]
        for i in range(m, n):
            combination[m + i] = lines[ord(a[i]) - ord("A")]
    else:
        for i in range(n):
            combination[i * 2] = lines[ord(a[i]) - ord("A")]
        for i in range(n):
            combination[i * 2 + 1] = lines[ord(b[i]) - ord("A")]
        for i in range(n, m):
            combination[n + i] = lines[ord(b[i]) - ord("A")]

    while len(combination) > 2:
        new_combination = [0] * (len(combination) - 1)
        for i in range(len(new_combination)):
            new_combination[i] = (combination[i] + combination[i + 1]) % 10
        combination = new_combination

    print(f"{combination[0] * 10 + combination[1]}%")


main()
