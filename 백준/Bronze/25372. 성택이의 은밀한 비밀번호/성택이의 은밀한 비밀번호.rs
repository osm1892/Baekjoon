use std::io::Read;

fn main() {
    let mut inputs = String::new();
    std::io::stdin().read_to_string(&mut inputs).unwrap();
    let inputs: Vec<&str> = inputs.trim().split_whitespace().collect();

    let n: usize = inputs[0].parse().unwrap();

    for i in 1..=n {
        if inputs[i].len() < 6 || inputs[i].len() > 9 {
            println!("no");
        } else {
            println!("yes")
        }
    }
}
