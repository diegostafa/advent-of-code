#[allow(unused_imports)]
use super::prelude::*;

type Input<'a> = &'a str;

#[derive(Clone, Copy, PartialEq, Eq)]
pub enum Move {
    U,
    D,
    L,
    R,
}
impl TryFrom<char> for Move {
    type Error = ();
    fn try_from(value: char) -> Result<Self, Self::Error> {
        match value {
            '^' => Ok(Move::U),
            'v' => Ok(Move::D),
            '<' => Ok(Move::L),
            '>' => Ok(Move::R),
            _ => Err(()),
        }
    }
}

#[derive(Clone, Copy, PartialEq, Eq)]
pub enum Tile {
    Wall,
    Box,
    Empty,
    Player,
}
impl TryFrom<char> for Tile {
    type Error = ();
    fn try_from(c: char) -> Result<Self, Self::Error> {
        match c {
            '#' => Ok(Tile::Wall),
            '.' => Ok(Tile::Empty),
            'O' => Ok(Tile::Box),
            '@' => Ok(Tile::Player),
            _ => Err(()),
        }
    }
}

pub fn input_generator(input: &str) -> Input {
    input
}

pub fn part1(input: &Input) -> usize {
    let (grid, moves) = input.split_once("\n\n").unwrap();
    let mut grid = Grid::from_input_chars(grid, |c, _, _| Tile::try_from(c).unwrap());
    let moves = moves.chars().flat_map(Move::try_from).collect_vec();
    let mut player = grid.iter().find(|(_, t)| **t == Tile::Player).unwrap().0;

    for m in moves {
        player = step(&mut grid, m, player);
    }

    grid.iter()
        .filter(|c| *c.1 == Tile::Box)
        .map(|((x, y), _)| x + 100 * y)
        .sum()
}

pub fn part2(_input: &Input) -> usize {
    0
}

fn move_with_dir((x, y): (usize, usize), m: Move) -> (usize, usize) {
    match m {
        Move::U => (x, y - 1),
        Move::D => (x, y + 1),
        Move::L => (x - 1, y),
        Move::R => (x + 1, y),
    }
}
fn first_empty(curr: (usize, usize), dir: Move, grid: &Grid<Tile>) -> Option<(usize, usize)> {
    match grid[curr] {
        Tile::Wall => None,
        Tile::Empty => Some(curr),
        Tile::Box => first_empty(move_with_dir(curr, dir), dir, grid),
        Tile::Player => unreachable!(),
    }
}
fn step(grid: &mut Grid<Tile>, m: Move, curr: (usize, usize)) -> (usize, usize) {
    let next = move_with_dir(curr, m);
    match grid[next] {
        Tile::Wall => curr,
        Tile::Empty => {
            grid[next] = Tile::Player;
            grid[curr] = Tile::Empty;
            next
        }
        Tile::Box => match first_empty(next, m, grid) {
            Some(box_next) => {
                grid[box_next] = Tile::Box;
                grid[curr] = Tile::Empty;
                grid[next] = Tile::Player;
                next
            }
            None => curr,
        },
        Tile::Player => unreachable!(),
    }
}
