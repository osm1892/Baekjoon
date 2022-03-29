fn main() {
    let n = {
        let mut input = String::new();
        std::io::stdin().read_line(&mut input).unwrap();
        input.trim().parse::<usize>().unwrap()
    };

    println!("{}", 1 << n);
}
