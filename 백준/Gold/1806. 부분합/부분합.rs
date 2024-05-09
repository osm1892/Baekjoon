use std::io::Read;
use std::io::Write;

fn main() {
    let mut lines = String::new();
    std::io::stdin().read_to_string(&mut lines).unwrap();
    let mut lines = lines.split("\n").map(|x| x.trim());

    let stdout = std::io::stdout();
    let mut out = std::io::BufWriter::new(stdout.lock());

    let line: Vec<usize> = lines
        .next()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let n = line[0];
    let s = line[1];

    let arr: Vec<usize> = lines
        .next()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut left = 0;
    let mut right = 0;
    let mut sum = 0;
    let mut len = n + 1;

    while left <= right {
        if sum >= s {
            len = len.min(right - left);

            sum -= arr[left];
            left += 1;
        } else if right == n {
            break;
        } else {
            sum += arr[right];
            right += 1;
        }
    }

    out.write_fmt(format_args!(
        "{}\n",
        if let true = len == n + 1 { 0 } else { len }
    ))
    .unwrap();
}
