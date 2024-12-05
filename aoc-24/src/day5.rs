#[allow(unused_imports)]
use super::prelude::*;
type Input = (Vec<(usize, usize)>, Vec<Vec<usize>>);

pub fn input_generator(input: &str) -> Input {
    let mut blk = input.split("\n\n");

    let fst: Vec<(usize, usize)> = blk
        .next()
        .unwrap()
        .lines()
        .map(|l| {
            let mut split = l.split("|");
            (
                split.next().unwrap().parse::<usize>().unwrap(),
                split.next().unwrap().parse::<usize>().unwrap(),
            )
        })
        .collect();

    let snd = blk
        .next()
        .unwrap()
        .lines()
        .map(|l| l.split(",").map(|s| s.parse().unwrap()).collect())
        .collect();

    (fst, snd)
}

pub fn part1((rules, updates): &Input) -> usize {
    updates
        .iter()
        .filter(|u| has_invalid(u, rules).is_none())
        .map(|u| u[u.len() / 2])
        .sum()
}

pub fn part2((rules, updates): &mut Input) -> usize {
    let mut sum = 0;
    for u in updates {
        if has_invalid(u, rules).is_none() {
            continue;
        }
        while let Some((i, j)) = has_invalid(u, rules) {
            u.swap(i, j);
        }
        sum += u[u.len() / 2];
    }
    sum
}

pub fn has_invalid(update: &[usize], rules: &Vec<(usize, usize)>) -> Option<(usize, usize)> {
    for (i, u) in update.iter().enumerate() {
        for (j, l) in update[0..i].iter().enumerate() {
            if !rules.iter().filter(|r| r.1 == *u).map(|r| r.0).contains(l) {
                return Some((i, j));
            }
        }
        for (j, r) in update[i + 1..].iter().enumerate() {
            if !rules.iter().filter(|r| r.0 == *u).map(|r| r.1).contains(r) {
                return Some((i, i + j + 1));
            }
        }
    }
    None
}
