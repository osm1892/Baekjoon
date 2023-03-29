import sys


def main():
    r, g = map(int, input().split())
    r_dividers = [i for i in range(1, int(r ** 0.5) + 1) if r % i == 0]
    g_dividers = [i for i in range(1, int(g ** 0.5) + 1) if g % i == 0]

    r_dividers.extend([r // i for i in r_dividers])
    g_dividers.extend([g // i for i in g_dividers])

    both_dividers = list(set(r_dividers) & set(g_dividers))

    for i in both_dividers:
        sys.stdout.write("{} {} {}\n".format(i, r // i, g // i))


main()
