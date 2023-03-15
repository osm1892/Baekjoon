import collections


def main():
    data = [input().split() for i in range(5)]
    colors = [i[0] for i in data]
    points = [int(i[1]) for i in data]

    points.sort()
    colors.sort()

    point_counter = collections.Counter(points)
    point_reverse = dict()
    color_counter = collections.Counter(colors)
    color_reverse = dict()

    for k, v in sorted(map(lambda x: (x[1], x[0]), point_counter.items())):
        if k in point_reverse:
            point_reverse[k].append(v)
        else:
            point_reverse[k] = [v]

    for k, v in sorted(map(lambda x: (x[1], x[0]), color_counter.items())):
        if k in color_reverse:
            color_reverse[k].append(v)
        else:
            color_reverse[k] = [v]

    continuous = True
    for i in range(5):
        if points[i] != min(points) + i:
            continuous = False
            break

    result = 0
    if color_reverse.get(5) and continuous:
        result = points[-1] + 900

    if point_reverse.get(4):
        result = max(result, point_reverse[4][0] + 800)

    if point_reverse.get(3) and point_reverse.get(2):
        result = max(result, point_reverse[3][0] * 10 + point_reverse[2][0] + 700)

    if color_reverse.get(5):
        result = max(result, points[-1] + 600)

    if continuous:
        result = max(result, points[-1] + 500)

    if point_reverse.get(3):
        result = max(result, point_reverse[3][0] + 400)

    if point_reverse.get(2):
        if len(point_reverse[2]) == 2:
            result = max(result, point_reverse[2][1] * 10 + point_reverse[2][0] + 300)
        else:
            result = max(result, point_reverse[2][0] + 200)

    result = max(result, points[-1] + 100)

    print(result)


main()
