#[allow(unused_imports)]
use super::prelude::*;

type Input<'a> = Vec<&'a str>;

pub fn input_generator(input: &str) -> Input<'_> {
    input.lines().collect()
}

fn max_idx(s: &str) -> Option<usize> {
    s.as_bytes().iter().position_max()
}

fn max_two(s: &str) -> u128 {
    let i = max_idx(s).unwrap();
    let l = max_idx(&s[..i]);
    let r = max_idx(&s[i + 1..]).map(|r| i + 1 + r);

    match (l, r) {
        (None, Some(y)) => num_at(s, &[i, y]),
        (Some(x), None) => num_at(s, &[x, i]),
        (Some(x), Some(y)) => num_at(s, &[x, i]).max(num_at(s, &[i, y])),
        _ => unreachable!(),
    }
}

fn num_at(s: &str, positions: &[usize]) -> u128 {
    positions
        .iter()
        .sorted()
        .map(|i| s.chars().nth(*i).unwrap())
        .join("")
        .parse()
        .unwrap()
}

fn max_twelve(s: &str) -> String {
    let chars: Vec<char> = s.chars().collect();
    let mut result = vec![];
    let mut start = 0;

    for remaining in (0..12).rev() {
        let end = s.len() - remaining - 1;
        let mut best_idx = start;
        let mut best_digit = chars[start];

        for (i, c) in chars.iter().enumerate().take(end + 1).skip(start) {
            if *c > best_digit {
                best_digit = *c;
                best_idx = i;
            }
        }

        result.push(best_digit);
        start = best_idx + 1;
    }

    result.iter().collect()
}

pub fn part1(input: &Input) -> u128 {
    input.iter().map(|s| max_two(s)).sum::<u128>()
}

pub fn part2(input: &Input) -> u128 {
    input
        .iter()
        .map(|s| max_twelve(s).parse::<u128>().unwrap())
        .sum::<u128>()
}
