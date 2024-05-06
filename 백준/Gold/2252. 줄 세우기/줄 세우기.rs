use std::collections::VecDeque;
use std::io::Read;

fn main() {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let mut input = input
        .split_whitespace()
        .map(|x| x.parse::<usize>().unwrap());
    let n = input.next().unwrap();
    let m = input.next().unwrap();

    let mut entry: Vec<usize> = vec![0; n];
    let mut queue: VecDeque<usize> = VecDeque::new();
    let mut graph: Vec<VecDeque<usize>> = vec![VecDeque::new(); n];

    for i in 0..m {
        let a = input.next().unwrap() - 1;
        let b = input.next().unwrap() - 1;
        entry[b] += 1;
        graph[a].push_back(b);
    }

    for (i, v) in entry.iter().enumerate() {
        if *v == 0 {
            queue.push_back(i);
        }
    }

    while !queue.is_empty() {
        let cur = queue.pop_front().unwrap();
        print!("{} ", cur + 1);
        for &i in graph[cur].iter() {
            entry[i] -= 1;
            if entry[i] == 0 {
                queue.push_back(i);
            }
        }
    }
}
