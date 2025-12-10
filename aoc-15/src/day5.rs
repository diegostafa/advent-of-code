#[allow(unused_imports)]
use super::prelude::*;
type Input<'a> = Vec<&'a str>;

pub fn input_generator(input: &'_ str) -> Input<'_> {
    input.lines().collect()
}

fn is_nice(s: &str) -> bool {
    let mut vowels = 0;
    let mut is_repeating_twice = false;
    let bad = [['a', 'b'], ['c', 'd'], ['p', 'q'], ['x', 'y']];

    for c in s.chars() {
        if c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' {
            vowels += 1;
        }
        if vowels >= 3 {
            break;
        }
    }
    for window in s.chars().collect_vec().windows(2) {
        if window[0] == window[1] {
            is_repeating_twice = true;
        }
        if bad.contains(&[window[0], window[1]]) {
            return false;
        }
    }
    vowels >= 3 && is_repeating_twice
}

fn is_nicer(s: &str) -> bool {
    let mut is_repeating_twice = false;
    let mut has_char_between = false;

    for i in 0..s.len() - 1 {
        if let Some(idx) = s.rfind(&s[i..i + 2])
            && idx > i + 1
        {
            is_repeating_twice = true;
            break;
        }
    }

    for window in s.chars().collect_vec().windows(3) {
        if window[0] == window[2] {
            has_char_between = true;
            break;
        }
    }
    is_repeating_twice && has_char_between
}

pub fn part1(input: &Input) -> usize {
    input.iter().filter(|s| is_nice(s)).count()
}

pub fn part2(input: &Input) -> usize {
    input.iter().filter(|s| is_nicer(s)).count()
}
