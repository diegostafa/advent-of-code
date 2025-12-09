#[allow(unused_imports)]
use super::prelude::*;

type Input = Grid<char>;

pub fn input_generator(input: &str) -> Input {
    Grid::from_input_chars(input, |c, _, _| c)
}

fn adjacent_cells(grid: &Grid<char>, i: i32, j: i32) -> Vec<Option<(usize, usize)>> {
    vec![
        (i - 1, j),
        (i + 1, j),
        (i - 1, j - 1),
        (i, j - 1),
        (i + 1, j - 1),
        (i - 1, j + 1),
        (i, j + 1),
        (i + 1, j + 1),
    ]
    .into_iter()
    .map(|(i, j)| {
        if i >= 0 && j >= 0 && i < grid.h() as i32 && j < grid.w() as i32 {
            Some((i as usize, j as usize))
        } else {
            None
        }
    })
    .collect()
}

fn is_roll(c: char) -> bool {
    c == '@'
}

fn is_roll_accessible(grid: &Grid<char>, i: i32, j: i32) -> bool {
    adjacent_cells(grid, i, j)
        .into_iter()
        .filter(|at| match at {
            Some(at) => is_roll(grid[*at]),
            None => false,
        })
        .count()
        < 4
}

fn accessible_rolls(grid: &Grid<char>) -> Option<Vec<(usize, usize)>> {
    let rolls: Vec<_> = grid
        .iter()
        .filter(|((i, j), _)| {
            is_roll(grid[(*i, *j)]) && is_roll_accessible(grid, *i as i32, *j as i32)
        })
        .map(|cell| cell.0)
        .collect();
    if rolls.is_empty() { None } else { Some(rolls) }
}

fn remove_rolls(grid: &mut Grid<char>, rolls: &[(usize, usize)]) -> usize {
    for roll in rolls {
        grid[*roll] = '.';
    }
    rolls.len()
}

pub fn part1(input: &Input) -> usize {
    accessible_rolls(input).unwrap().len()
}

pub fn part2(input: &mut Input) -> usize {
    let mut removed = 0;
    while let Some(rolls) = accessible_rolls(input) {
        removed += remove_rolls(input, &rolls);
    }
    removed
}
