fn fun_1() {
    // std::unique_ptr p1(new int(10))
    let p1 = Box::new(10);
    {
        // std::unique_ptr p2(std::move(p1))
        let p2 = p1;
    }
    // ERROR
    // println!("Hello, world! {}", b);
}

fn fun_2() {
    // std::unique_ptr p1(new int(10))
    let mut p1 = Box::new(10);
    // p1 = std::unique_ptr(new int(10))
    p1 = Box::new(20);
    println!("Hello, world! {}", p1);
}

fn fun_3() {
    fn fun(p1: Box<i32>) {
        // std::unique_ptr p2(std::move(p1))
    }

    // std::unique_ptr p1(new int(10))
    let p1 = Box::new(10);
    fun(p1);
    // ERROR
    // println!("Hello, world! {}", p1);
}

fn fun_4(a : i32) {
}

struct A {
    v: i32
}

fn main() {
    let a = 10;
    let b = a;
    fun_4(b);
    println!("{} {}", a, b);
    fun_1();
    fun_2();
    fun_3();
    let t = A { v: 10 };
    let y = t;
    println!("{}", y.v);
}
