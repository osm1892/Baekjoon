import sys
import collections

read = sys.stdin.readline
write = sys.stdout.write

q = int(read())

gorilla = collections.defaultdict(list)

final_cost = 0

for i in range(q):
    n, name, *data = read().split()

    if n == "1":
        gorilla[name] += list(map(int, data[1:]))
        gorilla[name].sort()
    else:
        b = int(data[0])
        if len(gorilla[name]) > b:
            cost = sum(gorilla[name][-b:])
            gorilla[name] = gorilla[name][:-b]
        else:
            cost = sum(gorilla[name])
            gorilla[name] = []
        final_cost += cost

print(final_cost)
