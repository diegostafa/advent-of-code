#[allow(unused_imports)]
use super::prelude::*;
type Input = Vec<Vec<i32>>;

pub fn input_generator(input: &str) -> Input {
    input
        .lines()
        .map(|line| {
            line.split_whitespace()
                .map(|s| s.parse().unwrap())
                .collect_vec()
        })
        .collect_vec()
}

fn is_safe(v: &[i32]) -> bool {
    let dec = v.windows(2).all(|w| w[1] <= w[0]);
    let inc = v.windows(2).all(|w| w[0] <= w[1]);
    if dec || inc {
        return v.windows(2).all(|w| (1..=3).contains(&(w[1] - w[0]).abs()));
    }
    false
}

fn is_almost_safe(v: &[i32], asc: bool, ignore: Option<usize>) -> bool {
    if let Some(idx) = ignore {
        return is_safe(
            &v[..idx]
                .iter()
                .chain(v[idx + 1..].iter())
                .cloned()
                .collect_vec(),
        );
    }
    for i in 1..v.len() {
        let x1 = v[i - 1];
        let x2 = v[i];
        if (asc && x2 < x1) || (!asc && x2 > x1) || !(1..=3).contains(&(x2 - x1).abs()) {
            return is_almost_safe(v, asc, Some(i - 1))
                || is_almost_safe(v, asc, Some(i))
                || is_almost_safe(v, asc, Some(i + 1));
        }
    }
    true
}

pub fn part1(input: &Input) -> usize {
    input.iter().filter(|x| is_safe(x)).count()
}

pub fn part2(input: &Input) -> usize {
    input
        .iter()
        .filter(|x| is_almost_safe(x, false, None) || is_almost_safe(x, true, None))
        .count()
}
