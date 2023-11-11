import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    x = int(read())
    n = int(read())

    staffs = {}

    for _ in range(n):
        data = read().split()

        if int(data[1]) < x * 0.05:
            continue

        staffs[data[0]] = int(data[1])

    scores = {}
    tokens = dict(zip(staffs.keys(), [0] * len(staffs)))
    for staff in staffs:
        score = staffs[staff]

        for div in range(1, 15):
            div_score = score / div
            scores[div_score] = staff

    for score in sorted(scores, reverse=True)[:14]:
        staff = scores[score]
        tokens[staff] += 1

    for staff in sorted(tokens):
        print(staff, tokens[staff])


main()
