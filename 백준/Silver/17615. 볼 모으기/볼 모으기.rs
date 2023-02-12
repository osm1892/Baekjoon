use std::cmp::min;

fn read_line() -> String {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    input
}

fn main() {
    let _n = read_line().trim().parse::<usize>().unwrap();
    let arr = read_line().trim().chars().collect::<Vec<char>>();

    let left_red = arr
        .iter()
        .skip_while(|&&x| x == 'R')
        .filter(|&&x| x == 'R')
        .count();
    let right_red = arr
        .iter()
        .rev()
        .skip_while(|&&x| x == 'R')
        .filter(|&&x| x == 'R')
        .count();
    let left_blue = arr
        .iter()
        .skip_while(|&&x| x == 'B')
        .filter(|&&x| x == 'B')
        .count();
    let right_blue = arr
        .iter()
        .rev()
        .skip_while(|&&x| x == 'B')
        .filter(|&&x| x == 'B')
        .count();

    println!(
        "{}",
        min(min(left_red, right_red), min(left_blue, right_blue))
    );
}
