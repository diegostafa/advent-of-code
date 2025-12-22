#[allow(unused_imports)]
use super::prelude::*;

type Input = Vec<Point>;
type Point = (u128, u128);
type Line = (Point, Point);
type Rect = (Point, Point);

pub fn input_generator(input: &str) -> Input {
    input
        .lines()
        .map(|l| {
            let (x, y) = l.split_once(',').unwrap();
            (x.parse().unwrap(), y.parse().unwrap())
        })
        .collect()
}

fn area((a, b): Rect) -> u128 {
    let w = a.0.abs_diff(b.0) + 1;
    let h = a.1.abs_diff(b.1) + 1;
    w * h
}

fn point_in_line((x, y): Point, ((ax, ay), (bx, by)): Line) -> bool {
    if ax == bx {
        return x == ax && y >= ay.min(by) && y <= ay.max(by);
    } else if ay == by {
        return y == ay && x >= ax.min(bx) && x <= ax.max(bx);
    }
    false
}

fn rect_intersects_line(((rx1, ry1), (rx2, ry2)): Rect, ((ax, ay), (bx, by)): Line) -> bool {
    if ax == bx {
        let (y1, y2) = (ay.min(by), ay.max(by));
        ax > rx1 && ax < rx2 && y2 > ry1 && y1 < ry2
    } else {
        let (x1, x2) = (ax.min(bx), ax.max(bx));
        ay > ry1 && ay < ry2 && x2 > rx1 && x1 < rx2
    }
}

fn point_in_polygon(p @ (px, py): Point, points: &Input) -> bool {
    let mut inside = false;
    for i in 0..points.len() {
        let a @ (ax, ay) = points[i];
        let b @ (bx, by) = points[(i + 1) % points.len()];

        if point_in_line(p, (a, b)) {
            return true;
        }
        if ay == by {
            continue;
        }

        let (x1, y1, _x2, y2) = if ay < by {
            (ax, ay, bx, by)
        } else {
            (bx, by, ax, ay)
        };
        if py >= y1 && py < y2 && x1 > px {
            inside = !inside;
        }
    }
    inside
}

fn rect_in_polygon(r @ ((x1, y1), (x2, y2)): Rect, poly: &Input) -> bool {
    for i in 0..poly.len() {
        let a = poly[i];
        let b = poly[(i + 1) % poly.len()];
        if rect_intersects_line(r, (a, b)) {
            return false;
        }
    }
    for &corner in &[(x1, y1), (x1, y2), (x2, y1), (x2, y2)] {
        if !point_in_polygon(corner, poly) {
            return false;
        }
    }
    true
}

fn normalize_rect(((x1, y1), (x2, y2)): Rect) -> Rect {
    ((x1.min(x2), y1.min(y2)), (x1.max(x2), y1.max(y2)))
}

pub fn part1(input: &Input) -> usize {
    let mut curr_max = 0;
    for i in 0..input.len() {
        for j in i + 1..input.len() {
            let r = (input[i], input[j]);
            curr_max = curr_max.max(area(r));
        }
    }
    curr_max as usize
}

pub fn part2(input: &Input) -> usize {
    let mut curr_max = 0;
    for i in 0..input.len() {
        for j in i + 1..input.len() {
            let r = normalize_rect((input[i], input[j]));
            if rect_in_polygon(r, input) {
                curr_max = curr_max.max(area(r));
            }
        }
    }
    curr_max as usize
}
