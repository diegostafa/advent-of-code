#[allow(unused_imports)]
use super::prelude::*;
type Input = Vec<(usize, Vec<usize>)>;

pub fn input_generator(input: &str) -> Input {
    input
        .lines()
        .map(|ln| {
            let mut vals = ln.split_ascii_whitespace();
            let head = vals.next().unwrap().trim_end_matches(":").parse().unwrap();
            let tail = vals.map(|v| v.parse().unwrap()).collect();
            (head, tail)
        })
        .collect()
}

pub fn has_solutions_rec(tot: usize, curr: usize, vars: &[usize], i: usize) -> bool {
    if curr > tot {
        return false;
    }
    if i == vars.len() && curr == tot {
        return true;
    }
    if i >= vars.len() {
        return false;
    }
    has_solutions_rec(tot, curr + vars[i], vars, i + 1)
        || has_solutions_rec(tot, curr * vars[i], vars, i + 1)
}

pub fn has_solutions_rec_2(tot: usize, curr: usize, vars: &[usize], i: usize) -> bool {
    if curr > tot {
        return false;
    }
    if i == vars.len() && curr == tot {
        return true;
    }
    if i >= vars.len() {
        return false;
    }
    has_solutions_rec_2(tot, curr + vars[i], vars, i + 1)
        || has_solutions_rec_2(tot, curr * vars[i], vars, i + 1)
        || has_solutions_rec_2(
            tot,
            (curr.to_string() + &vars[i].to_string()).parse().unwrap(),
            vars,
            i + 1,
        )
}

pub fn part1(input: &Input) -> usize {
    input
        .iter()
        .filter(|(res, vars)| has_solutions_rec(*res, 0, vars, 0))
        .map(|(res, _)| *res)
        .sum()
}

pub fn part2(input: &Input) -> usize {
    input
        .iter()
        .filter(|(res, vars)| has_solutions_rec_2(*res, 0, vars, 0))
        .map(|(res, _)| *res)
        .sum()
}
