fn read_line() -> String {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    input
}

fn main() {
    let n = read_line().trim().parse::<usize>().unwrap();
    let result = read_line()
        .trim()
        .split_whitespace()
        .map(|x| x.parse::<usize>().unwrap())
        .map(|x| x.min(n))
        .sum::<usize>();
    println!("{}", result);
}
