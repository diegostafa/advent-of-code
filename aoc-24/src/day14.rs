#[allow(unused_imports)]
use super::prelude::*;

const W: i32 = 101;
const H: i32 = 103;

type Device = ((i32, i32), (i32, i32));
type Input = Vec<Device>;

fn move_device(((x, y), (dx, dy)): &mut Device) {
    *x += *dx;
    *y += *dy;

    if *x < 0 {
        *x += W
    } else if *x >= W {
        *x -= W
    }
    if *y < 0 {
        *y += H
    } else if *y >= H {
        *y -= H
    }
}

pub fn input_generator(input: &str) -> Input {
    input
        .lines()
        .map(|ln| {
            let parse = |s: &str| {
                s.split_once(',')
                    .map(|(x, y)| (x.parse::<i32>().unwrap(), y.parse::<i32>().unwrap()))
                    .unwrap()
            };
            let (p, s) = ln.split_once(' ').unwrap();
            let pos = p.trim_start_matches("p=");
            let speed = s.trim_start_matches("v=");
            (parse(pos), parse(speed))
        })
        .collect()
}

pub fn part1(input: &Input) -> usize {
    let devices: Vec<_> = input
        .clone()
        .into_par_iter()
        .map(|mut d| {
            (0..100).for_each(|_| move_device(&mut d));
            d
        })
        .collect();

    let mut a = 0;
    let mut b = 0;
    let mut c = 0;
    let mut d = 0;
    for ((x, y), _) in devices {
        if x < W / 2 && y < H / 2 {
            a += 1;
        } else if x < W / 2 && y > H / 2 {
            b += 1;
        } else if x > W / 2 && y < H / 2 {
            c += 1;
        } else if x > W / 2 && y > H / 2 {
            d += 1;
        }
    }
    a * b * c * d
}

pub fn part2(input: &Input) -> usize {
    fn move_devices(devices: &mut [Device]) {
        devices.iter_mut().for_each(move_device)
    }
    fn is_possible_tree(((x1, y1), _): &Device, devices: &[Device]) -> bool {
        let positions = devices.iter().map(|((x, y), _)| (*x, *y)).collect_vec();
        let adjacents = [
            (0, 1),
            (1, 0),
            (0, -1),
            (-1, 0),
            (1, 1),
            (1, -1),
            (-1, 1),
            (-1, -1),
        ]
        .map(|d| (*x1 + d.0, *y1 + d.1));
        for adj in adjacents {
            if !positions.contains(&adj) {
                return false;
            }
        }
        true
    }

    let mut devices = input.clone();
    let mut i = 0;
    loop {
        if devices.iter().any(|d| is_possible_tree(d, &devices)) {
            break i;
        }
        move_devices(&mut devices);
        i += 1;
    }
}
