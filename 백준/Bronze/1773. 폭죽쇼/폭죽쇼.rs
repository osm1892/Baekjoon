use std::io::Read;

fn main() {
    let (_n, c): (usize, usize) = {
        let input: Vec<usize> = read_line()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        let n = input[0];
        let c = input[1];
        (n, c)
    };

    let mut timings = String::new();
    std::io::stdin().read_to_string(&mut timings).unwrap();
    let timings: Vec<usize> = timings
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut count = 0;
    for i in 1..=c {
        let mut check = 0;
        for &timing in timings.iter() {
            if i % timing == 0 {
                check = 1;
            }
        }
        count += check;
    }

    println!("{}", count);
}

fn read_line() -> String {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    input.trim().to_string()
}
