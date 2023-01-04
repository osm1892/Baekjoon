a, b, n = map(int, input().split())
n_digit = 10 ** n
big_a = a * n_digit
result = (big_a // b) % 10
print(result)
