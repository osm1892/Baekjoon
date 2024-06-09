use std::io::Read;

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let data: Vec<i32> = input
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    println!("{}", data[0] + data[1] - data[2]);
    println!(
        "{}",
        format!("{}{}", data[0], data[1]).parse::<i32>().unwrap() - data[2]
    );
}
