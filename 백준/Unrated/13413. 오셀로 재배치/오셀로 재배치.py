import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    test_case = int(read())

    for t in range(test_case):
        n = int(read())
        init = list(read().strip())
        dest = list(read().strip())

        if init == dest:
            write("0\n")
            continue

        init_counts = [init.count("B"), 0]
        init_counts[1] = n - init_counts[0]
        dest_counts = [dest.count("B"), 0]
        dest_counts[1] = n - dest_counts[0]

        count = 0

        for i in range(n):
            if init_counts[0] == dest_counts[0]:
                break
            if init_counts[0] > dest_counts[0] and init[i] == "B" and dest[i] == "W":
                init[i] = "W"
                init_counts[0] -= 1
                init_counts[1] += 1
                count += 1
            elif init_counts[0] < dest_counts[0] and init[i] == "W" and dest[i] == "B":
                init[i] = "B"
                init_counts[0] += 1
                init_counts[1] -= 1
                count += 1

        for i in range(n):
            if init_counts[1] == dest_counts[1]:
                break
            if init_counts[1] > dest_counts[1] and init[i] == "W" and dest[i] == "B":
                init[i] = "B"
                init_counts[0] += 1
                init_counts[1] -= 1
                count += 1
            elif init_counts[1] < dest_counts[1] and init[i] == "B" and dest[i] == "W":
                init[i] = "W"
                init_counts[0] -= 1
                init_counts[1] += 1
                count += 1

        tmp = 0
        for i in range(n):
            if init[i] != dest[i]:
                tmp += 1
        count += tmp // 2

        write(f"{count}\n")


main()
