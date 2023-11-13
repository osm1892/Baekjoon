fn main() {
    let n: usize = read_line().trim().parse().unwrap();
    let mut party: Vec<usize> = Vec::with_capacity(n);
    let mut dp: Vec<usize> = vec![0; n];

    for _ in 0..n {
        let score: usize = read_line().trim().parse().unwrap();
        party.push(score);
    }

    for i in 0..n {
        let mut max = 0;
        for j in 0..i {
            if party[j] >= party[i] {
                continue;
            }
            max = max.max(dp[j]);
        }
        dp[i] = max + party[i];
    }

    println!("{}", dp.iter().max().unwrap());
}

fn read_line() -> String {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    input
}
