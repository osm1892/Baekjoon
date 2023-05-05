def main():
    n = int(input())
    road = input()

    counter = 0
    for i in range(n - 1):
        if road[i] == "E" and road[i + 1] == "W":
            counter += 1
    if road[0] == "W":
        counter += 1
    if road[n - 1] == "E":
        counter += 1

    print(counter)


main()
