import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    while True:
        n = read().strip()
        if n == "0":
            break
        rev = list(reversed(n))
        is_palindrome = True
        for i in range(len(n)):
            if n[i] != rev[i]:
                is_palindrome = False
                break
        write("yes\n" if is_palindrome else "no\n")


main()
