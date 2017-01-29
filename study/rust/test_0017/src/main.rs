use std::fmt;


struct Gen<T> {
    value: T
}


impl Gen<i32> {
    fn v(&self) {
        println!("i32: {}", self.value);
    }
}

impl Gen<String> {
    fn v(&self) {
        println!("str: {}", self.value);
    }
}

fn main() {
    let a = Gen {value: 10};
    let b = Gen {value: "abc".to_owned()};
    a.v();
    b.v();
}
