import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    names = {
        "NLCS": "North London Collegiate School",
        "BHA": "Branksome Hall Asia",
        "KIS": "Korea International School",
        "SJA": "St. Johnsbury Academy",
    }
    name = read().strip()
    write(names[name] + "\n")


main()
