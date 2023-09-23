import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    t = 0
    while True:
        t += 1
        n = int(read())
        if n == 0:
            return

        manito = dict()
        visit = set()
        cycle = 0

        for i in range(n):
            key, val = read().split()
            manito[key] = val

        for key in manito:
            if key in visit:
                continue

            visit.add(key)
            val = manito[key]

            while val != key:
                visit.add(val)
                val = manito[val]

            cycle += 1

        write("{} {}\n".format(t, cycle))


main()
