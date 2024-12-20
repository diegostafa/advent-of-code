#[allow(unused_imports)]
use super::prelude::*;
type Input = Grid<char>;
type Region = HashSet<(usize, usize)>;

#[derive(Copy, Clone, Debug, PartialEq, Eq, Hash)]
enum Dir {
    U,
    D,
    L,
    R,
}
impl Dir {
    fn from_coord((x, y): (isize, isize)) -> Dir {
        match (x, y) {
            (0, -1) => Dir::U,
            (0, 1) => Dir::D,
            (-1, 0) => Dir::L,
            (1, 0) => Dir::R,
            _ => panic!("Invalid direction"),
        }
    }
}

fn find_regions(input: &Input) -> Vec<(char, Region)> {
    fn find_region(grid: &Grid<char>, c: char, pos: (usize, usize), region: &mut Region) {
        if !region.contains(&pos) && grid[pos] == c {
            region.insert(pos);
            for (x, y) in grid.plus_neighbours(pos) {
                find_region(grid, c, (x, y), region);
            }
        }
    }
    let mut visited: HashSet<(_, _)> = HashSet::new();
    let mut regions = vec![];
    for (pos, c) in input.iter() {
        if !visited.contains(&pos) {
            let mut region = HashSet::new();
            find_region(input, *c, pos, &mut region);
            visited.extend(region.iter());
            regions.push((*c, region));
        }
    }
    regions
}
fn neighbors((x, y): (isize, isize)) -> [(isize, isize); 4] {
    [(x, y - 1), (x, y + 1), (x - 1, y), (x + 1, y)]
}
fn outside(grid: &Grid<char>, (x, y): (isize, isize)) -> bool {
    x < 0 || y < 0 || x >= grid.w() as isize || y >= grid.h() as isize
}

pub fn input_generator(input: &str) -> Input {
    Grid::from_input_chars(input, |c, _, _| (c))
}
pub fn part1(input: &Input) -> usize {
    fn perimeter_of(grid: &Grid<char>, region: &Region, c: char) -> usize {
        let mut perimeter = 0;
        for pos in region.iter() {
            for pos in neighbors((pos.0 as isize, pos.1 as isize)) {
                if outside(grid, pos) || grid[pos] != c {
                    perimeter += 1;
                }
            }
        }
        perimeter
    }
    find_regions(input).into_iter().fold(0, |price, (c, r)| {
        price + r.len() * perimeter_of(input, &r, c)
    })
}
pub fn part2(input: &Input) -> usize {
    find_regions(input)
        .into_iter()
        .fold(0, |price, (_, r)| price + r.len() * sides_of(input, &r))
}

fn sides_of(grid: &Grid<char>, region: &Region) -> usize {
    let mut border = HashSet::new();
    for (pos, _) in grid.iter().filter(|(pos, _)| region.contains(pos)) {
        let pos = (pos.0 as isize, pos.1 as isize);
        neighbors(pos)
            .into_iter()
            .filter(|adj| {
                outside(grid, *adj) || !region.contains(&(adj.0 as usize, adj.1 as usize))
            })
            .map(|n| (n, Dir::from_coord((n.0 - pos.0, n.1 - pos.1))))
            .for_each(|n| {
                border.insert(n);
            });
    }

    let u = sides_of_dir(&border, Dir::U);
    let d = sides_of_dir(&border, Dir::D);
    let l = sides_of_dir(&border, Dir::L);
    let r = sides_of_dir(&border, Dir::R);
    u + d + l + r
}

fn sides_of_dir(border: &HashSet<((isize, isize), Dir)>, dir: Dir) -> usize {
    let mut by_axis: HashMap<isize, Vec<isize>> = HashMap::new();
    for (x, y) in border.iter().filter(|(_, d)| *d == dir).map(|(pos, _)| pos) {
        match dir {
            Dir::U | Dir::D => by_axis.entry(*y).or_default().push(*x),
            Dir::L | Dir::R => by_axis.entry(*x).or_default().push(*y),
        }
    }
    by_axis
        .values()
        .map(|axis| {
            axis.iter()
                .sorted()
                .collect_vec()
                .windows(2)
                .filter(|w| w[1].abs_diff(*w[0]) != 1)
                .count()
                + 1
        })
        .sum()
}
