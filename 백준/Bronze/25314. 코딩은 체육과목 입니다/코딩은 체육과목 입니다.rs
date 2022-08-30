fn main() {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();

    for _ in 1..=(n / 4 + (n % 4 != 0) as usize) {
        print!("long ");
    }
    println!("int");
}
