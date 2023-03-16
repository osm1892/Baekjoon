use std::io::Read;

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let mut input = input.trim().split_whitespace();

    let n = input.next().unwrap().parse::<usize>().unwrap();
    let m = input.next().unwrap().parse::<usize>().unwrap();

    let mut train = vec![0usize; n];

    for _ in 0..m {
        let t = input.next().unwrap().parse::<usize>().unwrap();
        let i = input.next().unwrap().parse::<usize>().unwrap() - 1;

        let x = {
            if t >= 3 {
                0
            } else {
                input.next().unwrap().parse::<usize>().unwrap() - 1
            }
        };

        match t {
            1 => train[i] |= 1 << x,
            2 => train[i] &= !(1 << x),
            3 => train[i] <<= 1,
            4 => train[i] >>= 1,
            _ => (),
        }
        train[i] &= (1 << 20) - 1;
    }

    train.sort_unstable();
    train.dedup();

    println!("{}", train.len());
}
