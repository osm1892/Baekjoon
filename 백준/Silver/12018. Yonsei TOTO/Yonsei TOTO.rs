use std::io::Read;

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let mut input = input.trim().split_whitespace();

    let n = input.next().unwrap().parse::<usize>().unwrap();
    let m = input.next().unwrap().parse::<usize>().unwrap();

    let mut required = Vec::<usize>::with_capacity(n);

    for _i in 0..n {
        let p = input.next().unwrap().parse::<usize>().unwrap();
        let l = input.next().unwrap().parse::<usize>().unwrap();

        let mut points: Vec<usize> = Vec::with_capacity(p);
        for _j in 0..p {
            points.push(input.next().unwrap().parse::<usize>().unwrap());
        }
        points.sort_unstable();

        if p >= l {
            required.push(points[p - l]);
        } else {
            required.push(1);
        }
    }

    required.sort_unstable();
    let mut point_sum = 0;

    for (i, v) in required.iter().enumerate() {
        point_sum += v;
        if point_sum > m {
            println!("{}", i);
            return;
        }
    }

    println!("{}", n);
}
