def get_section(local_dist, phase):
    diff = abs(local_dist - phase * 5)

    return phase - diff // 5

def main():
    n = int(input()) % 100

    if n < 10:
        print(get_section(n, 1))
    elif n < 30:
        print(get_section(n - 10, 2))
    elif n < 60:
        print(get_section(n - 30, 3))
    else:
        print(get_section(n - 60, 4))

main()
