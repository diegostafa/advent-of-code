#[allow(unused_imports)]
use super::prelude::*;

type Input = Vec<(u128, u128)>;

pub fn input_generator(input: &str) -> Input {
    input
        .trim_end()
        .split(',')
        .map(|s| {
            let (l, r) = s.split_once('-').unwrap();
            (l.parse().unwrap(), r.parse().unwrap())
        })
        .collect_vec()
}

fn is_repeating_twice(s: &str) -> bool {
    if !s.len().is_multiple_of(2) {
        return false;
    }
    let l = &s[..s.len() / 2];
    let r = &s[s.len() / 2..];
    l == r
}

pub fn part1(input: &Input) -> usize {
    let mut sum: usize = 0;
    for range in input {
        for i in range.0..=range.1 {
            let s = i.to_string();
            if is_repeating_twice(&s) {
                sum += i as usize
            }
        }
    }
    sum
}

pub fn part2(input: &Input) -> usize {
    let mut sum: usize = 0;
    for (start, end) in input {
        for i in *start..=*end {
            let s = i.to_string();
            if s.len() >= 2 {
                let ss = s.clone() + &s;
                if ss[1..ss.len() - 1].contains(&s) && s.len() >= 2 {
                    sum += i as usize
                }
            }
        }
    }
    sum
}
