import collections


def main():
    dest = input()
    n = int(input())
    books = [tuple() for _ in range(n)]
    for i in range(n):
        price, name = input().split()
        price = int(price)
        books[i] = (price, name)

    books.sort()
    dest_counter = collections.Counter(dest)
    result = min([dfs(books, dest_counter, i, collections.Counter(books[i][1])) for i in range(len(books))])

    if result >= 1e9:
        print(-1)
    else:
        print(result)


def dfs(books: list, dest_counter: dict, index: int, sum_counter: dict):
    if check_counter(dest_counter, sum_counter):
        return books[index][0]
    if index == len(books) - 1:
        return 1e9

    return books[index][0] + min(
        [dfs(books, dest_counter, i, add_counters(sum_counter, collections.Counter(books[i][1]))) for i in
         range(index + 1, len(books))])


def add_counters(a: dict, b: dict) -> dict:
    new_counter = {}
    for i in range(ord('A'), ord('Z') + 1):
        new_counter[chr(i)] = a.get(chr(i), 0) + b.get(chr(i), 0)

    return new_counter


def check_counter(dest: dict, counter: dict) -> bool:
    for i in range(ord('A'), ord('Z') + 1):
        if dest.get(chr(i), 0) > counter.get(chr(i), 0):
            return False
    return True


main()
