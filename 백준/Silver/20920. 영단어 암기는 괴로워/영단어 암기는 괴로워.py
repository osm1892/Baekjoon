import sys
import collections

read = sys.stdin.readline
write = sys.stdout.write

n, m = map(int, read().split())
words = [read().strip() for i in range(n)]
words = list(filter(lambda x: len(x) >= m, words))
freq = collections.defaultdict(int)

for word in words:
    freq[word] += 1

result = sorted(list(freq.keys()), key=lambda x: (-freq[x], -len(x), x))

for i in result:
    write(i + '\n')