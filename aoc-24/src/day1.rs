#[allow(unused_imports)]
use super::prelude::*;
type Input = (Vec<i32>, Vec<i32>);

pub fn input_generator(input: &str) -> Input {
    input
        .lines()
        .map(|line| {
            let mut x = line.split_whitespace().flat_map(str::parse::<i32>);
            (x.next().unwrap(), x.next().unwrap())
        })
        .unzip()
}

pub fn part1(input: &Input) -> i32 {
    input
        .0
        .iter()
        .sorted()
        .zip(input.1.iter().sorted())
        .map(|(a, b)| (a - b).abs())
        .sum()
}

pub fn part2(input: &Input) -> i32 {
    input
        .0
        .iter()
        .map(|n| n * input.1.iter().filter(|m| *m == n).count() as i32)
        .sum()
}
