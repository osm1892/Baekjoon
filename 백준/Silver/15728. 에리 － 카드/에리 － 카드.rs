fn main() {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let input: Vec<i32> = input
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let k = input[1];

    let mut shared = String::new();
    std::io::stdin().read_line(&mut shared).unwrap();
    let shared: Vec<i32> = shared
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut team = String::new();
    std::io::stdin().read_line(&mut team).unwrap();
    let team: Vec<i32> = team
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut max_scores: Vec<i32> = team
        .iter()
        .map(|&x| shared.iter().map(|&y| x * y).max().unwrap())
        .collect();
    max_scores.sort();
    let result = *max_scores.iter().rev().skip(k as usize).next().unwrap();

    println!("{:?}", result);
}
