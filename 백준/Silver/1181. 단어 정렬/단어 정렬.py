import sys

Input = sys.stdin.readlines()
data = []

for i in Input:
	data += i.rstrip("\n").split()

n = int(data[0])
del data[0]

data.sort(key = lambda x:(len(x), x))

print(data[0])
for i in range(1, n):
	if data[i - 1] == data[i]:
		continue
	print(data[i])
