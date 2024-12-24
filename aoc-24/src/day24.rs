#[allow(unused_imports)]
use super::prelude::*;

type Link = (String, Op, String, String);
type Input = (HashMap<String, bool>, Vec<Link>);

#[derive(Clone, Copy)]
pub enum Op {
    And,
    Or,
    Xor,
}
impl Op {
    fn apply(self, a: bool, b: bool) -> bool {
        match self {
            Op::And => a && b,
            Op::Or => a || b,
            Op::Xor => a ^ b,
        }
    }
}
impl From<&str> for Op {
    fn from(value: &str) -> Self {
        match value {
            "AND" => Self::And,
            "OR" => Self::Or,
            "XOR" => Self::Xor,
            _ => unreachable!(),
        }
    }
}

pub fn input_generator(input: &str) -> Input {
    let (start, connections) = input.split_once("\n\n").unwrap();

    let mut links = vec![];
    for ln in connections.lines() {
        let tokens = ln.split_whitespace().collect_vec();
        links.push((
            tokens[0].to_string(),
            Op::from(tokens[1]),
            tokens[2].to_string(),
            tokens[4].to_string(),
        ));
    }

    let mut gates = HashMap::new();
    for ln in start.lines() {
        let (k, v) = ln.split_once(" ").unwrap();
        let k = k.trim_end_matches(':');
        let val = v == "1";
        gates.insert(k.to_string(), val);
    }

    (gates, links)
}

fn resolve<'a>(vals: &HashMap<String, bool>, links: &'a Vec<Link>) -> (usize, &'a str, bool) {
    for (i, (src, op, dst, res)) in links.iter().enumerate() {
        if let Some(v1) = vals.get(src) {
            if let Some(v2) = vals.get(dst) {
                return (i, res, op.apply(*v1, *v2));
            }
        }
    }
    unreachable!()
}

pub fn part1((vals, links): &Input) -> usize {
    let mut vals = vals.clone();
    let mut links = links.clone();

    while !links.is_empty() {
        let (i, s, v) = resolve(&vals, &links);
        vals.insert(s.to_string(), v);
        links.swap_remove(i);
    }

    let s = vals
        .into_iter()
        .filter(|(k, _)| k.starts_with("z"))
        .map(|(k, v)| (k[1..].parse::<usize>().unwrap(), v))
        .sorted_by(|a, b| a.0.cmp(&b.0))
        .rev()
        .map(|(_, v)| if v { 1 } else { 0 })
        .join("");

    usize::from_str_radix(&s, 2).unwrap()
}

pub fn part2(_input: &Input) -> usize {
    0
}
