import collections
import sys

read = sys.stdin.readline
write = sys.stdout.write

test_case = int(read())

for t in range(test_case):
    s = read().strip()
    stack = collections.deque()
    start = 0
    end = 0
    state = s[0]
    for i in range(len(s)):
        if state == s[i]:
            end = i
        else:
            if end - start >= 1:
                stack.append(s[:start] + s[end + 1:])
            start = i
            end = i
            state = s[i]

    if end - start >= 1:
        stack.append(s[:start] + s[end + 1:])

    empty = False

    while len(stack):
        data = stack.pop()

        if len(data) == 0:
            empty = True
            break

        start = 0
        state = data[0]

        for i in range(len(data)):
            if state == data[i]:
                end = i
            else:
                if end - start >= 1:
                    stack.append(data[:start] + data[end + 1:])
                start = i
                end = i
                state = data[i]

        if end - start >= 1:
            stack.append(data[:start] + data[end + 1:])

    print(1 if empty else 0)
