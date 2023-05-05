import collections


def main():
    data = input()
    counter = collections.Counter(data)
    odd_counter = 0
    odd_key = ""

    for k, v in counter.items():
        if v % 2 == 1:
            odd_counter += 1
            odd_key = k

    if odd_counter > 1:
        print("I'm Sorry Hansoo")
        return

    palindrome_even = "".join(
        [k * (v // 2) for k, v in sorted(counter.items()) if v > 1]
    )
    print(palindrome_even + odd_key + palindrome_even[::-1])


main()
