#[allow(unused_imports)]
use super::prelude::*;

type Input = (Vec<(u128, u128)>, Vec<u128>);

pub fn input_generator(input: &str) -> Input {
    let (ranges, ids) = input.split_once("\n\n").unwrap();
    let ranges = ranges
        .lines()
        .map(|ln| {
            let (l, r) = ln.split_once('-').unwrap();
            (l.parse().unwrap(), r.parse().unwrap())
        })
        .collect();
    let ids = ids.lines().map(|ln| ln.parse().unwrap()).collect();
    (ranges, ids)
}

fn is_fresh(ranges: &[(u128, u128)], id: u128) -> bool {
    for (a, b) in ranges {
        if id >= *a && id <= *b {
            return true;
        }
    }
    false
}

pub fn part1(input: &Input) -> usize {
    let (ranges, ids) = input;
    ids.iter()
        .filter(|id| is_fresh(ranges.as_slice(), **id))
        .count()
}

pub fn part2(input: &mut Input) -> usize {
    let (ranges, _) = input;

    ranges.sort_unstable_by_key(|r| r.0);
    let mut merged = vec![];
    let mut acc = ranges[0];

    for &(c, d) in &ranges[1..] {
        if c <= acc.1 {
            acc.1 = acc.1.max(d);
        } else {
            merged.push(acc);
            acc = (c, d);
        }
    }
    merged.push(acc);
    merged.into_iter().map(|(a, b)| b - a + 1).sum::<u128>() as usize
}
