use super::prelude::*;
type Input<'a> = &'a str;

pub fn input_generator(input: &str) -> Input {
    input
}

fn transpose<T>(v: Vec<Vec<T>>) -> Vec<Vec<T>> {
    let len = v[0].len();
    let mut iters: Vec<_> = v.into_iter().map(|n| n.into_iter()).collect();
    (0..len)
        .map(|_| iters.iter_mut().map(|n| n.next().unwrap()).collect())
        .collect()
}

fn diagonals<T: Clone>(grid: Vec<Vec<T>>) -> Vec<Vec<T>> {
    let rows = grid.len();
    let cols = grid[0].len();
    let mut diagonals = vec![Vec::new(); rows + cols - 1];
    for i in 0..rows {
        for j in 0..cols {
            diagonals[i + j].push(grid[i][j].clone());
        }
    }
    diagonals
}

pub fn part1(input: &Input) -> usize {
    pub const XMAS: &str = "XMAS";
    pub const SAMX: &str = "SAMX";

    let h: Vec<Vec<char>> = input.lines().map(|ln| ln.chars().collect()).collect();
    let v = transpose(h.clone());
    let dl = diagonals(h.clone());
    let dr = diagonals(
        h.clone()
            .into_iter()
            .map(|ln| ln.into_iter().rev().collect())
            .collect(),
    );

    let mut count = 0;
    for line in h {
        count += line.iter().join("").match_indices(XMAS).count();
        count += line.iter().join("").match_indices(SAMX).count();
    }
    for line in v {
        count += line.iter().join("").match_indices(XMAS).count();
        count += line.iter().join("").match_indices(SAMX).count();
    }
    for line in dl {
        count += line.iter().join("").match_indices(XMAS).count();
        count += line.iter().join("").match_indices(SAMX).count();
    }
    for line in dr {
        count += line.iter().join("").match_indices(XMAS).count();
        count += line.iter().join("").match_indices(SAMX).count();
    }
    count
}

fn check_x_mas(grid: &Vec<Vec<char>>, i: usize, j: usize) -> bool {
    let tlbr = [grid[i - 1][j - 1], grid[i + 1][j + 1]].iter().join("");
    let trbl = [grid[i - 1][j + 1], grid[i + 1][j - 1]].iter().join("");
    (tlbr == "SM" || tlbr == "MS") && (trbl == "SM" || trbl == "MS")
}

pub fn part2(input: &Input) -> usize {
    let grid: Vec<Vec<char>> = input.lines().map(|ln| ln.chars().collect()).collect();
    let rows = grid.len();
    let cols = grid[0].len();
    let mut count = 0;
    for i in 1..rows - 1 {
        for j in 1..cols - 1 {
            if grid[i][j] == 'A' && check_x_mas(&grid, i, j) {
                count += 1;
            }
        }
    }

    count
}
