import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    n = int(read())
    nums = sys.stdin.read().strip().split()
    nums = list(map(int, nums))
    output = []
    stack = []
    max_num = 0

    for i in nums:
        if stack and i == stack[-1]:
            stack.pop()
            output.append("-")
        elif i > max_num:
            while i > max_num:
                max_num += 1
                stack.append(max_num)
                output.append("+")
            stack.pop()
            output.append("-")
        else:
            write("NO\n")
            return

    for i in output:
        write(f"{i}\n")


main()
