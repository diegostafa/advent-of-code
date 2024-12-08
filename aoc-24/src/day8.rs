#[allow(unused_imports)]
use super::prelude::*;
type Input = Grid<char>;

pub fn input_generator(input: &str) -> Input {
    Grid::from_input_chars(input, |c, _, _| c)
}

pub fn find_matches(input: &Input, i: usize, j: usize) -> Vec<(usize, usize)> {
    let mut matches = vec![];
    for x in 0..input.w() {
        for y in 0..input.h() {
            if (x != i || y != j) && input[(i, j)] == input[(x, y)] {
                matches.push((x, y));
            }
        }
    }
    matches
}

pub fn part1(input: &Input) -> usize {
    let mut antinodes = HashSet::new();
    for i in 0..input.w() {
        for j in 0..input.h() {
            if input[(i, j)] != '.' {
                for m in find_matches(input, i, j) {
                    let diff = (m.0 as i32 - i as i32, m.1 as i32 - j as i32);
                    let p = (i as i32 - diff.0, j as i32 - diff.1);
                    let q = (m.0 as i32 + diff.0, m.1 as i32 + diff.1);

                    if p.0 >= 0 && p.0 < input.w() as i32 && p.1 >= 0 && p.1 < input.h() as i32 {
                        antinodes.insert(p);
                    }
                    if q.0 >= 0 && q.0 < input.w() as i32 && q.1 >= 0 && q.1 < input.h() as i32 {
                        antinodes.insert(q);
                    }
                }
            }
        }
    }
    antinodes.len()
}

pub fn part2(input: &Input) -> usize {
    let mut antinodes = HashSet::new();
    for i in 0..input.w() {
        for j in 0..input.h() {
            if input[(i, j)] != '.' {
                for m in find_matches(input, i, j) {
                    let diff = (m.0 as i32 - i as i32, m.1 as i32 - j as i32);
                    let mut p = (i as i32, j as i32);
                    let mut q = (m.0 as i32, m.1 as i32);

                    while p.0 >= 0 && p.0 < input.w() as i32 && p.1 >= 0 && p.1 < input.h() as i32 {
                        antinodes.insert(p);
                        p = (p.0 - diff.0, p.1 - diff.1);
                    }
                    while q.0 >= 0 && q.0 < input.w() as i32 && q.1 >= 0 && q.1 < input.h() as i32 {
                        antinodes.insert(q);
                        q = (q.0 + diff.0, q.1 + diff.1);
                    }
                }
            }
        }
    }
    antinodes.len()
}
