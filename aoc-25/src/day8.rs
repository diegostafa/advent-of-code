#[allow(unused_imports)]
use super::prelude::*;

type Input = Vec<Junction>;

#[derive(Clone, Debug)]
pub struct Junction {
    group: usize,
    x: i64,
    y: i64,
    z: i64,
}
impl Junction {
    fn new(group: usize, x: i64, y: i64, z: i64) -> Self {
        Self { group, x, y, z }
    }
}
fn distance(j1: &Junction, j2: &Junction) -> i64 {
    let dx = j1.x - j2.x;
    let dy = j1.y - j2.y;
    let dz = j1.z - j2.z;
    dx * dx + dy * dy + dz * dz
}

pub fn input_generator(input: &str) -> Input {
    input
        .lines()
        .enumerate()
        .map(|(i, l)| {
            let mut parts = l.split(",");
            Junction::new(
                i,
                parts.next().unwrap().parse().unwrap(),
                parts.next().unwrap().parse().unwrap(),
                parts.next().unwrap().parse().unwrap(),
            )
        })
        .collect()
}

pub fn part1(input: &Input) -> usize {
    let mut junctions = input.clone();
    let mut distances = Vec::with_capacity((input.len() * input.len()) / 2);
    let mut groups = HashMap::new();

    for i in 0..input.len() {
        for j in i + 1..input.len() {
            distances.push((i, j, distance(&input[i], &input[j])));
        }
    }
    distances.sort_by_key(|d| d.2);

    for (i, j, _) in distances.iter().take(1000) {
        let ci = junctions[*i].group;
        let cj = junctions[*j].group;
        if ci != cj {
            let r = groups.remove(&cj).unwrap_or(1);
            let l = groups.entry(ci).or_insert(1);
            *l += r;

            for jun in &mut junctions {
                if jun.group == cj {
                    jun.group = ci;
                }
            }
        }
    }

    let mut values = groups.values().collect::<Vec<_>>();
    values.sort();
    let m1 = values.pop().unwrap();
    let m2 = values.pop().unwrap();
    let m3 = values.pop().unwrap();
    (m1 * m2 * m3) as usize
}

pub fn part2(input: &Input) -> usize {
    let mut junctions = input.clone();
    let mut distances = Vec::with_capacity((input.len() * input.len()) / 2);
    for i in 0..input.len() {
        for j in i + 1..input.len() {
            distances.push((i, j, distance(&input[i], &input[j])));
        }
    }
    distances.sort_by_key(|d| d.2);

    let mut groups = junctions.len();
    let mut res = 0;
    for (i, j, _) in distances {
        let ci = junctions[i].group;
        let cj = junctions[j].group;

        if ci != cj {
            groups -= 1;
            if groups == 1 {
                res = junctions[i].x * junctions[j].x;
                break;
            }
            for jun in &mut junctions {
                if jun.group == cj {
                    jun.group = ci;
                }
            }
        }
    }
    res as usize
}
