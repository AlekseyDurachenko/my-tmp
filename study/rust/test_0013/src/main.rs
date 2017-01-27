enum Values {
    One = 8,
    Two,
    Three
}

enum Colors {
    Blue = 0x328850,
    Green = 0x003928,
    Red = 0x99ff88
}

static LANGUAGE: &'static str = "Rust";
const  THRESHOLD: i32 = 10;

fn is_big(n :i32) -> bool {
    n > THRESHOLD
}


fn main() {
    let n = 10;
    println!("{}", LANGUAGE);
    println!("{}", THRESHOLD);
    println!("{}", is_big(n));
    println!("{}", Values::One as i32);
    println!("{}", Values::Two as i32);
    println!("{}", Values::Three as i32);
    println!("{}", Colors::Blue as i32);
    println!("{}", Colors::Red as i32);
    println!("{}", Colors::Green as i32);
}
