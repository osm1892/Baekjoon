fn main() {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let mut input = input
        .split_whitespace()
        .map(|x| x.parse::<usize>().unwrap());
    let x = input.next().unwrap();
    let y = input.next().unwrap();

    if y > x {
        println!("{}", y - x);
    } else {
        println!("{}", x + y);
    }
}
