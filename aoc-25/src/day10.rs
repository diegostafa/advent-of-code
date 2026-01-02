#[allow(unused_imports)]
use super::prelude::*;

type Input = Vec<(Lights, ButtonList, Joltages)>;
pub type Lights = u32;
pub type LightsMask = u32;
pub type ButtonList = Vec<LightsMask>;
pub type Joltages = Vec<u32>;

pub fn input_generator(input: &str) -> Input {
    input
        .lines()
        .map(|l| (parse_lights(l), parse_buttons(l), parse_joltages(l)))
        .collect()
}

fn parse_lights(s: &str) -> Lights {
    let bytes = s.as_bytes();
    let mut bits = 0u32;
    let mut pos = 0;

    for i in 0..bytes.len() {
        if bytes[i] == b'[' {
            let mut j = 1;
            while bytes[i + j] != b']' {
                if bytes[i + j] == b'#' {
                    bits |= 1 << pos;
                }
                pos += 1;
                j += 1;
            }
        }
    }
    bits
}

fn parse_buttons(s: &str) -> ButtonList {
    let bytes = s.as_bytes();
    let mut buttons = vec![];

    for i in 0..bytes.len() {
        if bytes[i] == b']' {
            let mut j = 0;
            while bytes[i + j] != b'{' {
                if bytes[i + j] == b'(' {
                    let mut k = 0;
                    let mut mask = 0u32;
                    let mut num = 0usize;
                    let mut has_num = false;

                    while bytes[i + j + k] != b')' {
                        let c = bytes[i + j + k];
                        if c.is_ascii_digit() {
                            num = num * 10 + (c - b'0') as usize;
                            has_num = true;
                        } else if c == b',' {
                            mask |= 1 << num;
                            num = 0;
                            has_num = false;
                        }
                        k += 1;
                    }
                    if has_num {
                        mask |= 1 << num;
                    }
                    buttons.push(mask);
                }
                j += 1;
            }
        }
    }
    buttons
}

fn parse_joltages(s: &str) -> Joltages {
    let s = s.as_bytes();
    let mut joltages = vec![];
    for i in 0..s.len() {
        let c = s[i];
        if c == b'{' {
            let mut j = 0;
            while s[i + j] != b'}' {
                let mut bytes = vec![];
                let mut k = 1;
                while s[i + j + k] != b',' && s[i + j + k] != b'}' {
                    let c = s[i + j + k];
                    if c.is_ascii_digit() {
                        bytes.push(c);
                    }
                    k += 1;
                }
                let n = bytes.as_ascii().unwrap().as_str().parse::<u32>().unwrap();
                joltages.push(n);
                j += k;
            }
        }
    }
    joltages
}

fn min_steps_lights(target: Lights, masks: &ButtonList) -> u32 {
    let mut queue = VecDeque::new();
    queue.push_back((0, 0));

    while let Some((state, steps)) = queue.pop_front() {
        let next_steps = steps + 1;

        for mask in masks {
            let next = state ^ mask;
            if next == target {
                return next_steps;
            }
            queue.push_back((next, next_steps));
        }
    }
    unreachable!()
}

pub fn part1(input: &Input) -> usize {
    let mut min = 0;
    for (lights, buttons_list, _) in input {
        min += min_steps_lights(*lights, buttons_list);
    }
    min as usize
}

pub fn part2(input: &Input) -> usize {
    0
}
