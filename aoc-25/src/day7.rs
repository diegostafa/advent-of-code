#[allow(unused_imports)]
use super::prelude::*;

type Input = Grid<char>;
type Ray = (usize, usize);

pub fn input_generator(input: &str) -> Input {
    Grid::from_input_chars(input, |c, _, _| c)
}

fn start(grid: &Grid<char>) -> Option<Ray> {
    for x in 0..grid.w() {
        for y in 0..grid.h() {
            if grid[(x, y)] == 'S' {
                return Some((x, y));
            }
        }
    }
    None
}

fn has_splitter_ahead(grid: &Grid<char>, (x, y): Ray) -> Option<Ray> {
    for y in y + 1..grid.h() {
        if grid[(x, y)] == '^' {
            return Some((x, y));
        }
    }
    None
}

fn timelines(grid: &Grid<char>, ray: Ray, memo: &mut HashMap<Ray, u128>) -> u128 {
    if let Some(times) = memo.get(&ray) {
        return *times;
    }
    let times = match has_splitter_ahead(grid, ray) {
        Some((x, y)) => timelines(grid, (x - 1, y), memo) + timelines(grid, (x + 1, y), memo),
        None => 1,
    };
    memo.insert(ray, times);
    times
}

pub fn part1(input: &Input) -> usize {
    let grid = input;
    let mut rays = vec![start(grid).unwrap()];
    let mut splits = HashSet::new();

    while let Some(ray) = rays.pop() {
        if let Some((x, y)) = has_splitter_ahead(grid, ray)
            && !splits.contains(&(x, y))
        {
            rays.push((x - 1, y));
            rays.push((x + 1, y));
            splits.insert((x, y));
        }
    }
    splits.len()
}

pub fn part2(input: &Input) -> usize {
    let grid = input;
    timelines(grid, start(grid).unwrap(), &mut HashMap::new()) as usize
}
