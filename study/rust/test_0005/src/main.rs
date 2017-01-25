use std::fmt;

struct MyStruct(i32);

impl fmt::Display for MyStruct {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "({})", self.0)
    }
}


fn main() {
    println!("Hello, world!");
    println!("{} value", 31);
    println!("{} value", "value");
    println!("{0} value 1; {1} value 2", 1, 2);
    println!("{name} is name, {value} is value", name="name", value=11);
    println!("{0} in bin {0:b} in hex {0:x}", 30);
    println!("align right : {text:>width$} |", text=1, width=6);
    println!("align left  : {text:<width$} |", text=1, width=6);
    println!("align center: {text:^width$} |", text=1, width=6);
    println!("my struct: {}", MyStruct(10));
    println!("{number:.3}", number=3.141592);
}
