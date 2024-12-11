#[allow(unused_imports)]
use super::prelude::*;
type Input = VecDeque<u64>;

pub fn input_generator(input: &str) -> Input {
    input
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect()
}

pub fn blink(memo: &mut HashMap<(u64, u64), u64>, stone: u64, times: u64) -> u64 {
    if times == 0 {
        return 0;
    }
    if let Some(count) = memo.get(&(stone, times)) {
        return *count;
    }
    let count = if stone == 0 {
        blink(memo, 1, times - 1)
    } else {
        let s = stone.to_string();
        if s.len() % 2 == 0 {
            let l = s[..s.len() / 2].parse().unwrap();
            let r = s[s.len() / 2..].parse().unwrap();
            1 + blink(memo, l, times - 1) + blink(memo, r, times - 1)
        } else {
            blink(memo, stone * 2024, times - 1)
        }
    };
    memo.insert((stone, times), count);
    count
}

pub fn part1(input: &Input) -> u64 {
    let mut memo = HashMap::new();
    input.iter().fold(input.len() as u64, |acc, stone| {
        acc + blink(&mut memo, *stone, 25)
    })
}

pub fn part2(input: &Input) -> u64 {
    let mut memo = HashMap::new();
    input.iter().fold(input.len() as u64, |acc, stone| {
        acc + blink(&mut memo, *stone, 75)
    })
}
