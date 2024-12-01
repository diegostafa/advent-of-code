#[allow(unused_imports)]
use super::prelude::*;
type Input = (Vec<i32>, Vec<i32>);

pub fn input_generator(input: &str) -> Input {
    input
        .lines()
        .map(|line| line.split_whitespace().collect_vec())
        .map(|split| {
            (
                split[0].parse::<i32>().unwrap(),
                split[1].parse::<i32>().unwrap(),
            )
        })
        .unzip()
}

pub fn part1(input: &Input) -> i32 {
    input
        .0
        .iter()
        .sorted_by(|a, b| a.cmp(b))
        .zip(input.1.iter().sorted_by(|a, b| a.cmp(b)))
        .map(|(a, b)| (a - b).abs())
        .sum()
}

pub fn part2(input: &Input) -> i32 {
    input
        .0
        .iter()
        .map(|n| *n * input.1.iter().filter(|m| *m == n).count() as i32)
        .sum()
}
