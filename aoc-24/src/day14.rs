#[allow(unused_imports)]
use super::prelude::*;

type Area = (i32, i32);
type Device = ((i32, i32), (i32, i32));
type Input = Vec<Device>;

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

fn make_step(((x, y), (dx, dy)): &mut Device, (w, h): Area) {
    *x += *dx;
    *y += *dy;

    if *x < 0 {
        *x += w
    } else if *x >= w {
        *x -= w
    }
    if *y < 0 {
        *y += h
    } else if *y >= h {
        *y -= h
    }
}

pub fn part1(input: &Input) -> usize {
    let (w, h) = (101, 103);
    let devices: Vec<_> = input
        .clone()
        .into_par_iter()
        .map(|mut d| {
            for _ in 0..100 {
                make_step(&mut d, (w, h))
            }
            d
        })
        .collect();

    let mut a = 0;
    let mut b = 0;
    let mut c = 0;
    let mut d = 0;
    for ((x, y), _) in devices {
        if x < w / 2 && y < h / 2 {
            a += 1;
        } else if x < w / 2 && y > h / 2 {
            b += 1;
        } else if x > w / 2 && y < h / 2 {
            c += 1;
        } else if x > w / 2 && y > h / 2 {
            d += 1;
        }
    }
    a * b * c * d
}

pub fn part2(input: &Input) -> usize {
    let (w, h) = (101, 103);
    let mut devices = input.clone();
    let mut i = 0;

    while false {
        devices = devices
            .into_par_iter()
            .map(|mut d| {
                make_step(&mut d, (w, h));
                d
            })
            .collect();
        i += 1;
    }
    i
}
