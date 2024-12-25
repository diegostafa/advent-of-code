#[allow(unused_imports)]
use super::prelude::*;

const W: usize = 5;
const H: usize = 7;
type Input = (Vec<[usize; W]>, Vec<[usize; W]>);

pub fn input_generator(input: &str) -> Input {
    input.split("\n\n").fold((vec![], vec![]), |mut acc, grid| {
        let heights = grid
            .lines()
            .map(|ln| {
                ln.chars()
                    .map(|c| if c == '#' { 1 } else { 0 })
                    .collect_vec()
            })
            .fold([0; 5], |mut acc, row| {
                (0..5).for_each(|i| acc[i] += row[i]);
                acc
            });
        if grid.lines().next().unwrap().chars().all(|c| c == '#') {
            acc.1.push(heights);
        } else {
            acc.0.push(heights);
        }
        acc
    })
}

pub fn part1((keys, locks): &Input) -> usize {
    let mut fits = 0;
    for a in keys {
        for b in locks {
            if a.iter().zip(b.iter()).all(|(a, b)| a + b <= H) {
                fits += 1
            }
        }
    }
    fits
}

pub fn part2(input: &Input) -> usize {
    0
}
