use std::collections::VecDeque;

fn main() {
    let _n: usize = read_line().trim().parse().unwrap();
    let arr: Vec<usize> = read_line()
        .trim()
        .split_whitespace()
        .map(|x| x.parse::<usize>().unwrap() % 7)
        .collect();
    let mut counter = vec![0usize; 7];

    for &i in arr.iter() {
        counter[i] += 1;
    }

    let mut queue: VecDeque<(usize, Vec<usize>)> = VecDeque::new();

    for i in 1..7 {
        if counter[i] != 0 {
            let mut tmp = counter.clone();
            tmp[i] -= 1;
            queue.push_back((i, tmp));
        }
    }

    while queue.is_empty() == false {
        let (cur, cnt) = queue.pop_front().unwrap();

        if cur == 4 {
            println!("YES");
            return;
        }

        if cnt.iter().all(|&x| x == 0) {
            continue;
        }

        for i in 0..7 {
            if cnt[i] == 0 {
                continue;
            }
            let mut tmp = cnt.clone();
            tmp[i] -= 1;
            queue.push_back(((cur + i) % 7, tmp))
        }
    }

    println!("NO");
}

fn read_line() -> String {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    input
}
