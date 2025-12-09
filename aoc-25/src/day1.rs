#[allow(unused_imports)]
use super::prelude::*;

type Input = Vec<i32>;

pub fn input_generator(input: &str) -> Input {
    input
        .lines()
        .map(|l| {
            let amount = &l[1..].parse::<i32>().unwrap();
            if &l[0..1] == "R" { *amount } else { -*amount }
        })
        .collect()
}

pub fn part1(input: &Input) -> usize {
    let mut curr = 50;
    let mut hits = 0;

    for amount in input {
        curr = (curr + amount) % 100;
        if curr == 0 {
            hits += 1;
        }
    }
    hits
}

pub fn part2(input: &Input) -> usize {
    let mut curr = 50;
    let mut hits: u32 = 0;

    for amount in input {
        hits += (amount / 100).unsigned_abs();
        let mut next = curr + amount % 100;

        if next == 0 {
            hits += 1;
        } else if next >= 100 {
            next %= 100;
            hits += 1;
        } else if next < 0 {
            next += 100;
            if curr != 0 {
                hits += 1;
            }
        }
        curr = next;
    }
    hits as usize
}
