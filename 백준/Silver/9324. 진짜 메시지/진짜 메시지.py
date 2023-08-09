import sys
import collections

read = sys.stdin.readline
write = sys.stdout.write


def main():
    tc = int(read())

    for _ in range(tc):
        msg = read().strip() + " "
        counter = collections.defaultdict(int)
        next_char = None
        fake = False

        for c in msg:
            if next_char != None and next_char != c:
                fake = True
                break
            count = counter[c] + 1
            if count == 3:
                next_char = c
                count = -1
            else:
                next_char = None
            counter[c] = count

        print("FAKE" if fake else "OK")


main()
