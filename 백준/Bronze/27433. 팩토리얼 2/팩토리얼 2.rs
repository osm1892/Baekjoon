fn main() {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let n = input.trim().parse::<u64>().unwrap();

    if n == 0 {
        println!("1");
        return;
    }

    let mut result = 1;

    for i in 1..=n {
        result *= i;
    }

    println!("{}", result);
}
