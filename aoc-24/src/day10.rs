#[allow(unused_imports)]
use super::prelude::*;

type Input = (Vec<(usize, usize)>, Grid<u32>);

pub fn input_generator(input: &str) -> Input {
    let grid = Grid::from_input_chars(input, |c, _, _| c.to_digit(10).unwrap_or(100));
    let start = grid.iter().filter(|c| *c.1 == 0).map(|c| c.0).collect();
    (start, grid)
}

pub fn part1(input: &Input) -> u32 {
    let mut sum = 0;
    for start in &input.0 {
        let mut score = HashSet::new();
        trail_score(&input.1, start, &mut score);
        sum += score.len();
    }
    sum as u32
}

pub fn part2(input: &Input) -> u32 {
    input
        .0
        .iter()
        .fold(0, |acc, start| acc + trail_rating(&input.1, start))
}

fn trail_score(grid: &Grid<u32>, curr: &(usize, usize), score: &mut HashSet<(usize, usize)>) {
    for next in grid.plus_neighbours(*curr) {
        if grid[next] == grid[*curr] + 1 {
            if grid[next] == 9 {
                score.insert(next);
            } else {
                trail_score(grid, &next, score);
            }
        }
    }
}
fn trail_rating(grid: &Grid<u32>, curr: &(usize, usize)) -> u32 {
    let mut rating = 0;
    for next in grid.plus_neighbours(*curr) {
        if grid[next] == grid[*curr] + 1 {
            if grid[next] == 9 {
                rating += 1;
            } else {
                rating += trail_rating(grid, &next);
            }
        }
    }
    rating
}
