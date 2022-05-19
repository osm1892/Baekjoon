fn main() {
    let tc: usize = read_line().trim().parse().unwrap();

    for _t in 0..tc {
        let (n, m, w): (usize, usize, usize) = {
            let input = read_line();
            let mut input = input.split_whitespace();
            (
                input.next().unwrap().parse().unwrap(),
                input.next().unwrap().parse().unwrap(),
                input.next().unwrap().parse().unwrap(),
            )
        };

        let mut arr: Vec<Vec<i32>> = vec![vec![i32::MAX; n]; n];

        for _ in 0..m {
            let (s, e, t): (usize, usize, i32) = {
                let input = read_line();
                let mut input = input.split_whitespace();
                (
                    input.next().unwrap().parse().unwrap(),
                    input.next().unwrap().parse().unwrap(),
                    input.next().unwrap().parse().unwrap(),
                )
            };
            if arr[s - 1][e - 1] > t {
                arr[s - 1][e - 1] = t;
            }
            if arr[e - 1][s - 1] > t {
                arr[e - 1][s - 1] = t;
            }
        }

        for _ in 0..w {
            let (s, e, t): (usize, usize, i32) = {
                let input = read_line();
                let mut input = input.split_whitespace();
                (
                    input.next().unwrap().parse().unwrap(),
                    input.next().unwrap().parse().unwrap(),
                    input.next().unwrap().parse().unwrap(),
                )
            };
            if arr[s - 1][e - 1] > -t {
                arr[s - 1][e - 1] = -t;
            }
        }

        for via in 0..n {
            for start in 0..n {
                for end in 0..n {
                    let via_route = arr[start][via].overflowing_add(arr[via][end]);
                    if via_route.1 {
                        continue;
                    }
                    arr[start][end] = arr[start][end].min(via_route.0);
                }
            }
        }

        let mut is_possible = false;
        for i in 0..n {
            if arr[i][i] < 0 {
                is_possible = true;
            }
        }

        if is_possible {
            println!("YES");
        } else {
            println!("NO");
        }
    }
}

fn read_line() -> String {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    input
}
