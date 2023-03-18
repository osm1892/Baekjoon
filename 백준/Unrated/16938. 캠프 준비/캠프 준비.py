def main():
    n, l, r, x = map(int, input().split())
    problems = list(map(int, input().split()))
    problems.sort()

    result = 0
    for i in range(1, 2**n):
        mask = bin(i)[2:]
        mask = mask[::-1]

        first_index = mask.find("1")
        last_index = mask.rfind("1")

        if problems[last_index] - problems[first_index] < x:
            continue

        masked_sum = 0
        for j, bit in enumerate(mask):
            if bit == "1":
                masked_sum += problems[j]
        if not (l <= masked_sum <= r):
            continue

        result += 1

    print(result)


main()
