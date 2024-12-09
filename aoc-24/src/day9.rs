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
        matches!(self, NodeType::File(..))
    }
    pub fn is_space(&self) -> bool {
        matches!(self, NodeType::Space(..))
    }
    pub fn size(&self) -> i32 {
        match self {
            NodeType::File(_, size) => *size,
            NodeType::Space(size) => *size,
        }
    }
    pub fn id(&self) -> i32 {
        match self {
            NodeType::File(id, _) => *id,
            NodeType::Space(_) => -1,
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
    let size = input.iter().fold(0, |acc, node| acc + node.size() as usize);
    let mut data = Vec::with_capacity(size);
    for n in input {
        let id = n.id();
        (0..n.size()).for_each(|_| data.push(id));
    }
    data
}

pub fn checksum(data: Vec<i32>) -> u64 {
    data.into_iter()
        .enumerate()
        .filter(|(_, id)| *id != -1)
        .fold(0, |acc, (i, id)| acc + (i as u64) * (id as u64))
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
        if let Some(i) = data[..j]
            .iter()
            .position(|n| n.is_space() && data[j].is_file() && n.size() >= data[j].size())
        {
            data[i] = NodeType::Space(data[i].size() - data[j].size());
            data.insert(i, data[j]);
            data[j + 1] = NodeType::Space(data[j + 1].size());
        }
        j -= 1;
    }
    checksum(decompress(&data))
}
