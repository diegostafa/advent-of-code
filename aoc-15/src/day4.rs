#[allow(unused_imports)]
use super::prelude::*;
type Input<'a> = &'a str;

pub fn input_generator(input: &'_ str) -> Input<'_> {
    input
}

pub fn part1(input: &Input) -> usize {
    let mut n = 1;
    loop {
        let md5 = md5::compute(format!("{input}{n}"));
        if md5[0] == 0 && md5[1] == 0 && (md5[2] & 0xF0) == 0 {
            return n;
        }
        n += 1;
    }
}

pub fn part2(input: &Input) -> usize {
    let mut n = 1;
    loop {
        let md5 = md5::compute(format!("{input}{n}")).0;
        if md5[0] == 0 && md5[1] == 0 && md5[2] == 0 {
            return n;
        }
        n += 1;
    }
}
