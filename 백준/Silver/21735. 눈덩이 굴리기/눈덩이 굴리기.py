import collections

class Block:
    def __init__(self, s, t, p):
        self.scale = s
        self.time = t
        self.pos = p

def main():
    n, m = map(int, input().split())
    a = [0] + list(map(int, input().split()))

    q = collections.deque()
    q.append(Block(1, 0, 0))

    max_scale = 0
    while q:
        cur = q.popleft()

        max_scale = max(max_scale, cur.scale)

        if cur.time >= m:
            continue

        if cur.pos <= n - 1:
            q.append(Block(cur.scale + a[cur.pos + 1], cur.time + 1, cur.pos + 1))
        if cur.pos <= n - 2:
            q.append(Block(cur.scale // 2 + a[cur.pos + 2], cur.time + 1, cur.pos + 2))

    print(max_scale)

main()
