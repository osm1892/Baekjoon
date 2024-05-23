use std::io::Read;

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let mut input = input.trim().split('\n');
    let mut line = input.next().unwrap().trim().split_whitespace();
    let n: usize = line.next().unwrap().parse().unwrap();
    let m: usize = line.next().unwrap().parse().unwrap();

    let mut chess: Vec<Vec<char>> = Vec::new();

    for line in input {
        chess.push(line.chars().collect());
    }

    let mut result = 64;
    for y in 0..(n - 7) {
        for x in 0..(m - 7) {
            let count = get_correct_count(&chess, y, x);
            let count = usize::min(count, 64 - count);
            result = usize::min(count, result);
        }
    }

    println!("{}", result);
}

fn get_correct_count(chess: &Vec<Vec<char>>, r: usize, c: usize) -> usize {
    let mut count = 0;
    for y in r..(r + 8) {
        for x in c..(c + 8) {
            if ((y ^ x) & 1) == 1 {
                if chess[y][x] == 'W' {
                    count += 1;
                }
            } else {
                if chess[y][x] == 'B' {
                    count += 1;
                }
            }
        }
    }
    count
}