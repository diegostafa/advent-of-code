#[allow(unused_imports)]
use super::prelude::*;
type Input<'a> = &'a str;

pub fn input_generator(input: &str) -> Input {
    input
}

pub fn part1(input: &Input) -> i32 {
    Regex::new(r"mul\((\d+),(\d+)\)")
        .unwrap()
        .captures_iter(input)
        .map(|cap| {
            let a: i32 = cap[1].parse().unwrap();
            let b: i32 = cap[2].parse().unwrap();
            (a, b)
        })
        .fold(0, |acc, (x, y)| acc + x * y)
}

pub fn part2(input: &Input) -> i32 {
    let matches = Regex::new(r"mul\((\d+),(\d+)\)")
        .unwrap()
        .captures_iter(input)
        .collect_vec();

    let mut sum = 0;
    let mut last_end = 0;

    for m in matches {
        let curr_pos = last_end + input[last_end..input.len()].find(&m[0]).unwrap();
        let behind = &input[0..curr_pos];
        let dont_pos = behind.rfind("don't()").unwrap_or(0);
        let do_pos = behind.rfind("do()").unwrap_or(0);
        if do_pos >= dont_pos {
            let a: i32 = m[1].parse().unwrap();
            let b: i32 = m[2].parse().unwrap();
            sum += a * b;
        }
        last_end = curr_pos + m[0].len();
    }
    sum
}
