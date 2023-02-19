fn read_line() -> String {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    input
}

fn main() {
    let [n, m, t, k] = if let [n, m, t, k] = read_line()
        .trim()
        .split_whitespace()
        .map(|x| x.parse::<usize>().unwrap())
        .collect::<Vec<usize>>()[..]
    {
        [n, m, t, k]
    } else {
        panic!()
    };

    let mut pos_list = Vec::<(usize, usize)>::new();

    for _i in 0..t {
        pos_list.push(
            if let [x, y] = read_line()
                .trim()
                .split_whitespace()
                .map(|x| x.parse::<usize>().unwrap())
                .collect::<Vec<usize>>()[..]
            {
                (x, y)
            } else {
                panic!()
            },
        );
    }

    let mut max_count = 0;
    let mut max_pos = (0, 0);

    for x in pos_list.iter().map(|x| x.0) {
        for y in pos_list.iter().map(|x| x.1) {
            let x0 = if x + k <= n { x } else { n - k };
            let y0 = if y + k <= m { y } else { m - k };

            let count = stone_counter(&pos_list, x0, y0, k);
            if max_count < count {
                max_count = count;
                max_pos = (x0, y0);
            }
        }
    }

    println!("{} {}\n{}", max_pos.0, max_pos.1 + k, max_count);
}

fn stone_counter(stones: &Vec<(usize, usize)>, x: usize, y: usize, size: usize) -> usize {
    let mut count = 0;
    for pos in stones {
        if !(x <= pos.0 && pos.0 <= x + size) {
            continue;
        }
        if !(y <= pos.1 && pos.1 <= y + size) {
            continue;
        }
        count += 1;
    }

    count
}

// https://justicehui.github.io/koi/2019/09/19/BOJ2492/ 참고
