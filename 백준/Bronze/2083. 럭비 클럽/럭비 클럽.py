while True:
    name, age, weight = input().split()

    if name == "#":
        break

    age = int(age)
    weight = int(weight)

    print(name, end=" ")
    if age > 17 or weight >= 80:
        print("Senior")
    else:
        print("Junior")
