use std::collections::HashMap;

fn main() {
    let n: usize = read_line().trim().parse().unwrap();
    let mut pills: HashMap<usize, usize> = HashMap::new();

    for _ in 0..n {
        let data: Vec<usize> = read_line().trim().split_whitespace().map(|x| x.parse().unwrap()).collect();
        pills.insert(data[0], data[1]);
    }

    let r: usize = read_line().trim().parse().unwrap();

    for _ in 0..r {
        let sicks: Vec<usize> = read_line().trim().split_whitespace().map(|x| x.parse().unwrap()).skip(1).collect();
        let mut eats: Vec<usize> = Vec::new();
        let mut die = false;

        for sick in sicks {
            match pills.get(&sick) {
                Some(x) => {
                    eats.push(*x);
                }
                None => {
                    die = true;
                    break;
                }
            }
        }

        if !die {
            for eat in eats {
                print!("{} ", eat);
            }
            print!("\n");
        } else {
            println!("YOU DIED");
        }
    }
}

fn read_line() -> String {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    input
}