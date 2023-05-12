import sys


def read() -> str:
    return sys.stdin.readline()


def write(*args):
    sys.stdout.write(*args)


n = int(read())
goals = [0, 0]
times = [0, 0]
last_time = 0

finish_time = 48 * 60

for i in range(n):
    team, cur = read().split(" ")
    team = int(team)
    elapsed = list(map(int, cur.split(":")))
    elapsed = elapsed[0] * 60 + elapsed[1]
    if goals[0] > goals[1]:
        times[0] += elapsed - last_time
    elif goals[0] < goals[1]:
        times[1] += elapsed - last_time
    goals[team - 1] += 1
    last_time = elapsed

if goals[0] > goals[1]:
    times[0] += finish_time - last_time
elif goals[1] > goals[0]:
    times[1] += finish_time - last_time

print("%02d:%02d" % (times[0] // 60, times[0] % 60))
print("%02d:%02d" % (times[1] // 60, times[1] % 60))
