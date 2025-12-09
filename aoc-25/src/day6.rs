#[allow(unused_imports)]
use super::prelude::*;

type Input<'a> = &'a str;

enum Op {
    Add,
    Mul,
}
impl Op {
    fn neutral(&self) -> u128 {
        match self {
            Op::Add => 0,
            Op::Mul => 1,
        }
    }
    fn apply(&self, a: u128, b: u128) -> u128 {
        match self {
            Op::Add => a + b,
            Op::Mul => a * b,
        }
    }
}
impl TryFrom<char> for Op {
    type Error = ();

    fn try_from(value: char) -> Result<Self, Self::Error> {
        match value {
            '+' => Ok(Op::Add),
            '*' => Ok(Op::Mul),
            _ => Err(()),
        }
    }
}

struct OpRange {
    op: Op,
    start: usize,
    end: usize,
}

pub fn input_generator(input: &str) -> Input<'_> {
    input
}

pub fn part1(input: &Input) -> u128 {
    let input = input.trim();
    let mut lines = input.lines().collect_vec();
    let ops = lines
        .pop()
        .unwrap()
        .split_whitespace()
        .map(|s| match s {
            "+" => Op::Add,
            "*" => Op::Mul,
            _ => unreachable!(),
        })
        .collect_vec();

    let rows: Vec<Vec<u128>> = lines
        .into_iter()
        .map(|l| {
            l.split_whitespace()
                .map(|s| s.parse().unwrap())
                .collect_vec()
        })
        .collect_vec();

    let mut res = vec![vec![]; rows[0].len()];
    for row in rows {
        for i in 0..row.len() {
            res[i].push(row[i]);
        }
    }
    res.into_iter()
        .zip(ops)
        .map(|(nums, op)| nums.iter().fold(op.neutral(), |a, b| op.apply(a, *b)))
        .sum::<u128>() as u128
}

pub fn part2(input: &Input) -> u128 {
    let end = input.rfind('\n').unwrap();
    let nums = &input[..end];
    let last = &input[end..].trim_start();

    let grid: Grid<Option<u128>> =
        Grid::from_input_chars(nums, |c, _, _| c.to_digit(10).map(|d| d as u128));

    let mut ops: Vec<OpRange> = vec![];
    let mut curr: Option<OpRange> = None;
    for (j, c) in last.chars().enumerate() {
        if let Ok(op) = Op::try_from(c) {
            if let Some(mut curr) = curr {
                curr.end = j;
                ops.push(curr);
            }
            curr = Some(OpRange {
                op,
                start: j,
                end: 0,
            });
        }
    }
    if let Some(mut curr) = curr {
        curr.end = last.len() + 1;
        ops.push(curr);
    }

    let mut res: u128 = 0;
    for OpRange { op, start, end } in ops {
        let mut acc = op.neutral();
        for x in start..(end - 1) {
            let mut ten = 1;
            let mut num = 0;
            for y in (0..grid.h()).rev() {
                if let Some(n) = grid[(x, y)] {
                    let n = n * ten;
                    ten *= 10;
                    num += n;
                }
            }
            acc = op.apply(acc, num);
        }
        res += acc;
    }
    res
}
