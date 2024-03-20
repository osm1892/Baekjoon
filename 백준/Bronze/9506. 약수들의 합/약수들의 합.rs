use std::io::Read;

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let input = input
        .trim()
        .split_whitespace()
        .map(|x| x.parse::<i32>().unwrap())
        .take_while(|&x| x != -1);

    for i in input {
        let mut divisors = Vec::<i32>::new();
        for j in 1..=(i / 2) {
            if i % j == 0 {
                divisors.push(j);
            }
        }
        if divisors.iter().sum::<i32>() == i {
            println!(
                "{} = {}",
                i,
                divisors
                    .iter()
                    .map(|x| x.to_string())
                    .collect::<Vec<String>>()
                    .join(" + ")
            );
        } else {
            println!("{} is NOT perfect.", i);
        }
    }
}
