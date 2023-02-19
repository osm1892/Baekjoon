def main():
    n, m, t, k = map(int, input().split())
    pos_list = [tuple(map(int, input().split())) for i in range(t)]

    max_count = 0
    max_pos = (0, 0)

    """
    모든 좌표를 탐색할 필요 없이, 임의의 점의 x 좌표, 임의의 점의 y 좌표를 좌하단으로 하여 사각형을 그리고
    모든 점들을 탐색하면서 각각의 점이 사각형 범위 내에 있는지 체크합니다.
    
    임의의 돌 두개의 x, y 좌표를 각각 이용하는 이유는,
    임의의 사각형에서 가장 좌측에 있는 돌의 왼쪽 공간은 무조건 비어있으므로 살필 필요가 없고, 오른쪽에 돌이 있기에 최대한 오른쪽으로 사각형을 맞추는게 이득이기 때문이며
    임의의 사각형에서 가장 하단에 있는 돌의 아래쪽 공간도 무조건 비어있으므로 살필 필요가 없고, 위쪽에 돌이 있기에 최대한 위쪽으로 사각형을 맞추는게 이득이기 때문입니다.
    """
    for x, _ in pos_list:
        for _, y in pos_list:
            if x + k <= n:
                x0 = x
            else:  # x + k, 즉 사각형의 위쪽 좌표가 범위를 넘어가는 경우, 탐색을 수행할 사각형의 아래 위치를 n - k로 고정하여 범위 내로 맞춥니다.
                x0 = n - k

            if y + k <= m:
                y0 = y
            else:  # y + k, 즉 사각형의 오른쪽 좌표가 범위를 넘어가는 경우, 탐색을 수행할 사각형의 왼쪽 위치를 m - k로 고정하여 범위 내로 맞춥니다.
                y0 = m - k

            # x0, y0 좌표를 좌하단으로 하는 사각형에서 돌이 몇개가 존재하는지를 세고, 최댓값을 갱신합니다.
            count = stone_counter(pos_list, x0, y0, k)
            if max_count < count:
                max_count = count
                max_pos = (x0, y0)

    print(f"{max_pos[0]} {max_pos[1] + k}\n{max_count}")


def stone_counter(stones, x, y, size):
    """
    x, y 좌표와 사각형 사이즈를 제공하면 사각형 범위 내의 돌 개수를 셉니다.
    리스트를 순회하면서 돌 좌표가 사각형 좌표 내인지 체크하는 방식입니다.
    O(T)의 시간복잡도를 가집니다.
    """
    count = 0
    for pos in stones:
        if not (x <= pos[0] <= x + size):
            continue
        if not (y <= pos[1] <= y + size):
            continue
        count += 1
    return count


main()


# https://justicehui.github.io/koi/2019/09/19/BOJ2492/ 참고
