struct Nil;

struct Pair(i32, f32);

#[derive(Debug)]
struct Point {
    x: f32,
    y: f32,
}

#[derive(Debug)]
struct Rectangle {
    p1: Point,
    p2: Point,
}

fn rect_area(rect: &Rectangle) -> f32 {
    let Rectangle { p1: Point { x: x1, y: y1 }, p2: Point { x: x2, y: y2} } = *rect;
    (x1.max(x2) - x1.min(x2)) * (y1.max(y2) - y1.min(y2))
}

fn square(p: &Point, k: &f32) -> Rectangle {
    Rectangle {
        p1: Point {
            x: p.x,
            y: p.y
        },
        p2: Point {
            x: p.x + k,
            y: p.y + k,
        }
    }
}

fn main() {
    let point: Point = Point{x: 0.0, y: 20.0};
    println!("Point: {}, {}", point.x, point.y);
    let Point{x: my_x, y: my_y} = point;
    let _rectangle = Rectangle {
        p1: Point {x : my_y, y: my_x},
        p2: Point { x: point.x, y: point.y },
    };

    let _nil = Nil;

    let pair = Pair(1, 0.1);
    println!("pair {:?} , {:?}", pair.0, pair.1);
    println!("area: {}", rect_area(&_rectangle));
    println!("area: {}", rect_area(&_rectangle));
    println!("square: {:?}", square(&point, &20.0));
    println!("square: {:?}", square(&point, &10.0));
}
