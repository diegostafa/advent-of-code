#[allow(unused_imports)]
use super::prelude::*;

type Input = Vec<((i64, i64, i64), (i64, i64, i64))>;

pub fn input_generator(input: &str) -> Input {
    let get_n = |sep: &str, ln: &str| ln.split(sep).nth(1).unwrap().parse::<i64>().unwrap();
    input
        .split("\n\n")
        .map(|block| {
            let lns = block.lines().collect_vec();

            let (btn_ay, btn_ax) = lns[0]
                .split_whitespace()
                .rev()
                .take(2)
                .map(|s| get_n("+", s.trim_end_matches(',')))
                .collect_tuple()
                .unwrap();

            let (btn_by, btn_bx) = lns[1]
                .split_whitespace()
                .rev()
                .take(2)
                .map(|s| get_n("+", s.trim_end_matches(',')))
                .collect_tuple()
                .unwrap();

            let (prize_y, prize_x) = lns[2]
                .split_whitespace()
                .rev()
                .take(2)
                .map(|s| get_n("=", s.trim_end_matches(',')))
                .collect_tuple()
                .unwrap();

            ((btn_ax, btn_bx, prize_x), (btn_ay, btn_by, prize_y))
        })
        .collect()
}

fn eq_solution(
    (a1, b1, mut c1): &(i64, i64, i64),
    (a2, b2, mut c2): &(i64, i64, i64),
    offset: i64,
) -> Option<(i64, i64)> {
    c1 += offset;
    c2 += offset;

    let det = a1 * b2 - a2 * b1;
    if det == 0 {
        return None;
    }
    let x = b2 * c1 - b1 * c2;
    let y = a1 * c2 - a2 * c1;
    if x % det != 0 || y % det != 0 {
        return None;
    }
    Some((x / det, y / det))
}

pub fn part1(input: &Input) -> i64 {
    input
        .iter()
        .filter_map(|(s1, s2)| eq_solution(s1, s2, 0))
        .filter(|(x, y)| *x <= 100 && *y <= 100)
        .map(|(x, y)| x * 3 + y)
        .sum()
}

pub fn part2(input: &Input) -> i64 {
    input
        .iter()
        .filter_map(|(s1, s2)| eq_solution(s1, s2, 10000000000000))
        .map(|(x, y)| x * 3 + y)
        .sum()
}
