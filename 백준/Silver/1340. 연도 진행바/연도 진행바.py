import datetime
import re
import sys


def read() -> str:
    return sys.stdin.read()


def write(x):
    sys.stdout.write(x)


def main():
    months = "January, February, March, April, May, June, July, August, September, October, November, December".split(
        ", "
    )
    data = read().strip()
    data = re.split(" |, |:", data)
    month = months.index(data[0]) + 1
    day = int(data[1])
    year = int(data[2])
    hour = int(data[3])
    minute = int(data[4])
    date = datetime.datetime(year, month, day, hour, minute).timestamp()
    start = datetime.datetime(year, 1, 1).timestamp()
    end = datetime.datetime(year + 1, 1, 1).timestamp()
    elapsed = date - start
    total = end - start
    print(elapsed / total * 100)


main()
