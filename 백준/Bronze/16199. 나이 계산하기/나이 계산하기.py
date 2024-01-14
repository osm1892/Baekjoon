import datetime
import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    birth = list(map(int, read().split()))
    today = list(map(int, read().split()))

    birth = datetime.datetime(*birth)
    today = datetime.datetime(*today)
    year_age = today.year - birth.year
    korean_age = year_age + 1
    birth_days_from_year = (birth - datetime.datetime(birth.year, 1, 1)).days
    today_days_from_year = (today - datetime.datetime(today.year, 1, 1)).days
    global_age = today.year - birth.year
    if birth_days_from_year > today_days_from_year:
        global_age -= 1

    print(global_age)
    print(korean_age)
    print(year_age)


main()
