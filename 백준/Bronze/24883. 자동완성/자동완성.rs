fn main() {
    let input = {
        let mut input = String::new();
        std::io::stdin().read_line(&mut input).unwrap();
        input.trim().chars().next().unwrap()
    };

    println!(
        "{}",
        match input {
            'N' | 'n' => "Naver D2",
            _ => "Naver Whale",
        }
    );
}
