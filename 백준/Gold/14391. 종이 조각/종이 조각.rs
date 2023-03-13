use std::io::Read;

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let mut input = input.trim().split('\n').map(|x| x.trim());

    let (n, m) = {
        let mut line = input
            .next()
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse::<usize>().unwrap());
        (line.next().unwrap(), line.next().unwrap())
    };

    let arr = input
        .map(|x| x.chars().map(|x| x.to_digit(10).unwrap()).collect())
        .collect::<Vec<Vec<u32>>>();

    let mut result = 0;

    for mask_index in 0..(2usize.pow((n * m) as u32)) {
        let mask = (0..(n * m))
            .map(|x| (mask_index >> x) & 1)
            .collect::<Vec<usize>>();
        let mut visit = [false; 16];
        let mut sum = 0;

        for (i, &direction) in mask.iter().enumerate() {
            sum += get_num(&arr, &mask, &mut visit, i, direction);
        }

        result = result.max(sum);
    }

    println!("{}", result);
}

fn get_num(
    arr: &Vec<Vec<u32>>,
    mask: &Vec<usize>,
    visit: &mut [bool],
    index: usize,
    direction: usize,
) -> u32 {
    let n = arr.len();
    let m = arr[0].len();
    let y = index / m;
    let x = index % m;

    if n <= y {
        return 0;
    }
    if m <= x {
        return 0;
    }

    if visit[index] {
        return 0;
    }

    let mut result = 0;

    if direction == 0 {
        for i in 0..(m - x) {
            if visit[index + i] {
                break;
            }
            if mask[index + i] == 1 {
                break;
            }
            visit[index + i] = true;
            result = result * 10 + arr[y][x + i];
        }
    } else {
        for i in 0..(n - y) {
            if visit[index + i * m] {
                break;
            }
            if mask[index + i * m] == 0 {
                break;
            }
            visit[index + i * m] = true;
            result = result * 10 + arr[y + i][x];
        }
    }

    result
}
