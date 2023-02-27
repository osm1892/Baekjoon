def main():
    pos_list = [list(map(int, input().split())) for i in range(4)]
    count = 0
    for x in range(1, 101):
        for y in range(1, 101):
            for i in range(4):
                x0, y0, x1, y1 = pos_list[i]
                if not (x0 <= x < x1):
                    continue
                if not (y0 <= y < y1):
                    continue
                count += 1
                break
    print(count)


main()
