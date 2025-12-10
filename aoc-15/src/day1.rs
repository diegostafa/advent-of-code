#[allow(unused_imports)]
use super::prelude::*;
type Input<'a> = &'a str;

pub fn input_generator(input: &str) -> Input<'_> {
    input
}

pub fn part1(input: &Input) -> usize {
    let mut floor = 0;
    for c in input.chars() {
        if c == '(' {
            floor += 1;
        } else if c == ')' {
            floor -= 1;
        }
    }
    floor as usize
}

pub fn part2(input: &Input) -> usize {
    let mut floor = 0;
    for (i, c) in input.chars().enumerate() {
        if c == '(' {
            floor += 1;
        } else if c == ')' {
            floor -= 1;
        }
        if floor == -1 {
            return i + 1;
        }
    }
    unreachable!()
}
