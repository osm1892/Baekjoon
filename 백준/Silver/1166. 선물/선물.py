import sys

read = sys.stdin.readline
write = sys.stdout.write

n, l, w, h = map(int, read().split())

left, right = 0, min(l, w, h)

for i in range(1000):  # 이진탐색은 log(n) 이므로 반드시 이 안에 근사치를 찾을 수 있다.
    mid = (left + right) / 2
    if (l // mid) * (w // mid) * (h // mid) >= n:
        left = mid
    else:
        right = mid

write(f"{left}")
