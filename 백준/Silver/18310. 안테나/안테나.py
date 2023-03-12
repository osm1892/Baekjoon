def main():
    n = int(input())
    data = list(map(int, input().split()))
    data.sort()
    print(data[(n - 1) // 2])


main()

# https://jjunsu.tistory.com/150 참조하여 중간값 원리 파악
