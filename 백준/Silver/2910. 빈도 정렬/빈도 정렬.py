import collections
import sys

n, c = map(int, input().split())
msg = list(map(int, input().split()))

counter = collections.Counter(msg)

msg = sorted(msg, key=lambda x: (-counter[x], msg.index(x)))

for i in msg:
    sys.stdout.write(str(i) + ' ')