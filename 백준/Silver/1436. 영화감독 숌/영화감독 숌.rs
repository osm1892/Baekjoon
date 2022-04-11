fn main() {
    let n: usize = {
        let mut input = String::new();
        std::io::stdin().read_line(&mut input).unwrap();
        input.trim().parse().unwrap()
    };

    let mut counter = 0;
    let mut i = 666;

    while counter < n {
        let mut tmp = i;
        let mut six_counter = 0;

        while tmp > 0 {
            if tmp % 10 != 6 {
                six_counter = 0;
                tmp /= 10;
                continue;
            }
            six_counter += 1;
            if six_counter == 3 {
                counter += 1;
                break;
            }
            tmp /= 10;
        }
        i += 1;
    }

    println!("{}", i - 1);
}
