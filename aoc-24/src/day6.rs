#[allow(unused_imports)]
use super::prelude::*;
type Input = (Grid<char>, Device);

#[derive(Default, Clone, Copy, PartialEq, Eq, Hash)]
pub enum Direction {
    #[default]
    Up,
    Right,
    Down,
    Left,
}
impl Direction {
    fn as_coords(&self) -> (isize, isize) {
        match self {
            Direction::Up => (0, -1),
            Direction::Right => (1, 0),
            Direction::Down => (0, 1),
            Direction::Left => (-1, 0),
        }
    }
    fn clock(&self) -> Self {
        match self {
            Direction::Up => Direction::Right,
            Direction::Right => Direction::Down,
            Direction::Down => Direction::Left,
            Direction::Left => Direction::Up,
        }
    }
    fn from_char(c: char) -> Option<Self> {
        match c {
            '>' => Some(Direction::Right),
            'v' => Some(Direction::Down),
            '<' => Some(Direction::Left),
            '^' => Some(Direction::Up),
            _ => None,
        }
    }
}
#[derive(Default, Clone)]
pub struct Device {
    pos: (usize, usize),
    dir: Direction,
    is_out: bool,
}

impl Device {
    fn make_step(&mut self, grid: &Grid<char>) {
        let (x, y) = self.pos;
        let (i, j) = self.dir.as_coords();
        let (new_x, new_y) = (x as isize + i, y as isize + j);
        if new_x < 0 || new_y < 0 || new_x >= grid.w() as isize || new_y >= grid.h() as isize {
            self.is_out = true;
            return;
        }
        if grid[(new_x, new_y)] == '#' {
            self.dir = self.dir.clock();
            self.make_step(grid);
            return;
        }
        self.pos = (new_x as usize, new_y as usize);
    }
}

pub fn input_generator(input: &str) -> Input {
    let grid = Grid::from_input_chars(input, |c, _, _| c);
    let mut device = Device::default();
    for i in 0..grid.w() {
        for j in 0..grid.h() {
            let c = grid[(i, j)];
            let dir = Direction::from_char(c);
            if let Some(dir) = dir {
                device.dir = dir;
                device.pos = (i, j);
                return (grid, device);
            }
        }
    }
    (grid, device)
}

pub fn part1((grid, device): &Input) -> usize {
    let mut device = device.clone();
    let mut seen = HashSet::new();
    seen.insert(device.pos);
    while !device.is_out {
        device.make_step(grid);
        seen.insert(device.pos);
    }
    seen.len()
}

pub fn part2((grid, device): &Input) -> usize {
    let mut loops = 0;
    for i in 0..grid.w() {
        for j in 0..grid.h() {
            if grid[(i, j)] == '.' {
                let mut seen = HashSet::new();
                let mut grid = grid.clone();
                let mut device = device.clone();
                grid[(i, j)] = '#';
                seen.insert((device.pos, device.dir));
                loop {
                    device.make_step(&grid);
                    if device.is_out {
                        break;
                    }
                    if seen.contains(&(device.pos, device.dir)) {
                        loops += 1;
                        break;
                    }
                    seen.insert((device.pos, device.dir));
                }
            }
        }
    }
    loops
}
