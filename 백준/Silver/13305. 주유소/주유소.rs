use std::collections::VecDeque;
use std::io::Read;

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let mut input = input
        .split_whitespace()
        .map(|x| x.parse::<usize>().unwrap());

    let n = input.next().unwrap();
    let mut distances: VecDeque<usize> = input.clone().take(n - 1).collect();
    let prices = input.skip(n - 1).take(n - 1);
    let mut result = 0;
    let mut min = 1000000000;
    for price in prices {
        let dist = distances.pop_front().unwrap();
        min = min.min(price);
        result += min * dist;
    }

    println!("{}", result)
}
