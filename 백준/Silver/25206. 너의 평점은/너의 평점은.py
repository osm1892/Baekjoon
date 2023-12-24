total_score = 0
total_scale = 0
point_to_score = {
    "A+": 4.5,
    "A0": 4.0,
    "B+": 3.5,
    "B0": 3.0,
    "C+": 2.5,
    "C0": 2.0,
    "D+": 1.5,
    "D0": 1.0,
    "F": 0.0,
}
for i in range(20):
    name, scale, point = input().split()
    if point == "P":
        continue

    scale = float(scale)
    score = point_to_score[point]
    total_score += scale * score
    total_scale += scale

print(total_score / total_scale)
