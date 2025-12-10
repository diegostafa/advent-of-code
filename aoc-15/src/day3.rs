#[allow(unused_imports)]
use super::prelude::*;
type Input = Vec<(i32, i32)>;

fn char_to_dir(c: char) -> (i32, i32) {
    match c {
        '^' => (0, 1),
        'v' => (0, -1),
        '<' => (-1, 0),
        '>' => (1, 0),
        _ => unreachable!(),
    }
}

pub fn input_generator(input: &str) -> Input {
    input.chars().map(char_to_dir).collect()
}

pub fn part1(input: &Input) -> usize {
    let mut seen = HashSet::new();
    let start = (0, 0);
    seen.insert(start);

    let mut santa = start;
    for (x, y) in input.iter() {
        santa = (santa.0 + x, santa.1 + y);
        seen.insert(santa);
    }
    seen.len()
}

pub fn part2(input: &Input) -> usize {
    let mut seen = HashSet::new();
    let start = (0, 0);
    seen.insert(start);

    let mut santa1 = start;
    let mut santa2 = start;
    for (i, (x, y)) in input.iter().enumerate() {
        if i % 2 == 0 {
            santa1 = (santa1.0 + x, santa1.1 + y);
            seen.insert(santa1);
        } else {
            santa2 = (santa2.0 + x, santa2.1 + y);
            seen.insert(santa2);
        }
    }
    seen.len()
}
