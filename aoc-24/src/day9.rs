use num::Integer;

#[allow(unused_imports)]
use super::prelude::*;

type Input = Vec<NodeType>;

#[derive(Clone, Copy, Debug)]
pub enum NodeType {
    File(i32, i32),
    Space(i32),
}
impl NodeType {
    pub fn is_file(&self) -> bool {
        matches!(self, NodeType::File(_, _))
    }
    pub fn is_space(&self) -> bool {
        matches!(self, NodeType::Space(_))
    }
    pub fn size(&self) -> i32 {
        match self {
            NodeType::File(_, size) => *size,
            NodeType::Space(size) => *size,
        }
    }
}

pub fn input_generator(input: &str) -> Input {
    input
        .trim_end()
        .chars()
        .map(|c| c.to_digit(10).unwrap() as i32)
        .enumerate()
        .map(|(i, n)| {
            if i.is_even() {
                NodeType::File(i as i32 / 2, n)
            } else {
                NodeType::Space(n)
            }
        })
        .collect()
}

pub fn decompress(input: &Vec<NodeType>) -> Vec<i32> {
    let mut data = vec![];
    for node in input {
        match node {
            NodeType::File(id, size) => {
                for _ in 0..*size {
                    data.push(*id);
                }
            }
            NodeType::Space(size) => {
                for _ in 0..*size {
                    data.push(-1);
                }
            }
        }
    }
    data
}

pub fn checksum(data: Vec<i32>) -> u64 {
    let mut sum = 0;
    for (i, id) in data.into_iter().enumerate() {
        if id != -1 {
            sum += (i as u64) * (id as u64);
        }
    }
    sum
}

pub fn part1(input: &Input) -> u64 {
    let mut data = decompress(input);
    while let Some(i) = data.iter().position(|&x| x == -1) {
        data.swap_remove(i);
    }
    checksum(data)
}

pub fn part2(input: &Input) -> u64 {
    let mut data = input.clone();
    let mut j = data.len() - 1;
    while j > 0 {
        if let Some(i) = data
            .iter()
            .position(|n| n.is_space() && data[j].is_file() && n.size() >= data[j].size())
        {
            if i < j {
                data[i] = NodeType::Space(data[i].size() - data[j].size());
                data.insert(i, data[j]);
                data[j + 1] = NodeType::Space(data[j + 1].size());
            }
        }
        j -= 1;
    }
    checksum(decompress(&data))
}
