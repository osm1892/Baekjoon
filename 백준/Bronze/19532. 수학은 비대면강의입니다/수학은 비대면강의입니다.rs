fn main() {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let input: Vec<i32> = input
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    'outer: for x in -999..=999 {
        for y in -999..=999 {
            if input[0] * x + input[1] * y != input[2] {
                continue;
            }
            if input[3] * x + input[4] * y != input[5] {
                continue;
            }
            println!("{} {}", x, y);
            break 'outer;
        }
    }
}
