use std::collections::HashMap;
use std::io::Read;

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let mut input = input.trim().split("\n");
    let n = input.next().unwrap().trim().parse::<usize>().unwrap();
    let correct = input
        .next()
        .unwrap()
        .trim()
        .split_whitespace()
        .collect::<Vec<_>>();
    let correct_map = correct
        .iter()
        .enumerate()
        .map(|(i, x)| (x, i))
        .collect::<HashMap<&&str, usize>>();
    let answer = input.next().unwrap().split_whitespace().collect::<Vec<_>>();
    let max_score = n * (n - 1) / 2;
    let mut score = 0;

    for i in 0..n {
        for j in (i + 1)..n {
            if correct_map[&answer[i]] < correct_map[&answer[j]] {
                score += 1;
            }
        }
    }

    println!("{}/{}", score, max_score);
}
