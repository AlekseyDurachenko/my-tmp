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


fn main() {
    println!("{}", Values::One as i32);
    println!("{}", Values::Two as i32);
    println!("{}", Values::Three as i32);
    println!("{}", Colors::Blue as i32);
    println!("{}", Colors::Red as i32);
    println!("{}", Colors::Green as i32);
}
