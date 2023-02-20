n, game = input().split()
n = int(n)
if game == 'Y':
    cap = 1
elif game == 'F':
    cap = 2
else:
    cap = 3

people = set(input() for i in range(n))

print(len(people) // cap)