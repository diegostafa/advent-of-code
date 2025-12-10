#[allow(unused_imports)]
use super::prelude::*;
type Input = Vec<XmasBox>;

pub struct XmasBox {
    l: u32,
    w: u32,
    h: u32,
}
impl XmasBox {
    fn volume(&self) -> u32 {
        let l = self.l;
        let w = self.w;
        let h = self.h;
        l * w * h
    }
    fn surface(&self) -> u32 {
        let l = self.l;
        let w = self.w;
        let h = self.h;
        (2 * l * w) + (2 * w * h) + (2 * h * l)
    }
    fn smallest_face_area(&self) -> u32 {
        let l = self.l;
        let w = self.w;
        let h = self.h;
        (l * w).min(w * h).min(h * l)
    }
    fn smallest_face_perimeter(&self) -> u32 {
        let l = self.l;
        let w = self.w;
        let h = self.h;
        (l + w).min(w + h).min(h + l) * 2
    }
}

pub fn input_generator(input: &str) -> Input {
    input
        .lines()
        .map(|l| {
            let mut splits = l.split("x").map(|s| s.parse::<u32>().unwrap());
            let l = splits.next().unwrap();
            let w = splits.next().unwrap();
            let h = splits.next().unwrap();
            XmasBox { l, w, h }
        })
        .collect()
}

pub fn part1(input: &Input) -> u32 {
    input
        .iter()
        .map(|b| b.surface() + b.smallest_face_area())
        .sum()
}

pub fn part2(input: &Input) -> u32 {
    input
        .iter()
        .map(|b| b.volume() + b.smallest_face_perimeter())
        .sum()
}
