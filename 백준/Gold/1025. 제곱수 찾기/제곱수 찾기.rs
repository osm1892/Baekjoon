use std::{collections::HashSet, io::Read};

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();

    let mut input = input.split_whitespace();
    let n = input.next().unwrap().parse::<usize>().unwrap();
    let m = input.next().unwrap().parse::<usize>().unwrap();

    let data: Vec<Vec<usize>> = input
        .map(|x| x.chars().map(|x| x as usize - '0' as usize).collect())
        .collect();

    let mut nums: HashSet<usize> = HashSet::new();

    for root in 0..=31622 {
        let num = root * root;
        nums.insert(num);
    }

    let mut res: isize = -1;

    for y in 0..n {
        for x in 0..m {
            for dy in -10..10 {
                for dx in -10..10 {
                    let mut cur = 0;
                    for step in 0..10 {
                        let ny = y as i32 + dy * step;
                        let nx = x as i32 + dx * step;

                        if ny < 0 || ny >= n as i32 || nx < 0 || nx >= m as i32 {
                            continue;
                        }

                        cur = cur * 10 + data[ny as usize][nx as usize];

                        if nums.contains(&cur) {
                            res = res.max(cur as isize);
                        }
                    }
                }
            }
        }
    }

    println!("{}", res);
}
