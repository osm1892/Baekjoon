import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    n = int(read())
    current = int(read())
    degrees = [int(read()) for _ in range(n)]
    total = 0

    for degree in degrees:
        if current < degree:
            clock = degree - current
            counter_clock = current + 360 - degree
        else:
            clock = degree + 360 - current
            counter_clock = current - degree

        current = degree
        total += min(clock, counter_clock)

    print(total)


main()
