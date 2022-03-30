fn main() {
    let n = {
        let mut n = String::new();
        std::io::stdin().read_line(&mut n).unwrap();
        n.trim().parse::<usize>().unwrap()
    };

    let arr: Vec<i32> = {
        let mut arr = vec![0; n];
        for i in 0..n {
            let mut arr_item = String::new();
            std::io::stdin().read_line(&mut arr_item).unwrap();
            arr[i] = arr_item.trim().parse::<i32>().unwrap();
        }
        arr.sort();
        arr
    };

    let sum = arr.iter().sum::<i32>();
    let avr = sum as f64 / n as f64;
    let avr = avr.round() as i32;
    let mid = arr[n / 2];

    let mut freq = [0; 8001];
    for i in 0..n {
        freq[(arr[i] + 4000) as usize] += 1;
    }
    let most_freq = *freq.iter().max().unwrap();
    let most_nums = freq
        .iter()
        .enumerate()
        .filter(|(i, x)| **x == most_freq)
        .map(|(i, _)| i as i32 - 4000)
        .collect::<Vec<i32>>();

    let most_freq_num = if most_nums.len() == 1 {
        most_nums[0]
    } else {
        most_nums[1]
    };

    let range = arr.last().unwrap() - arr.first().unwrap();

    println!("{}\n{}\n{}\n{}", avr, mid, most_freq_num, range);
}
