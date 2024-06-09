use std::io::Read;

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let input = input.split_whitespace();

    let num = input
        .enumerate()
        .find(|(_i, x)| x.parse::<i32>().is_ok())
        .unwrap();

    let ans = num.1.parse::<usize>().unwrap() + 3 - num.0;
    if ans % 3 == 0 {
        if ans % 5 == 0 {
            println!("FizzBuzz");
        } else {
            println!("Fizz");
        }
    } else if ans % 5 == 0 {
        println!("Buzz");
    } else {
        println!("{}", ans);
    }
}
