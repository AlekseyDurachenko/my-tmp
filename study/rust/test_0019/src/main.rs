fn pass_x<'a, 'b>(x: &'a i32, _: &'b i32) -> &'a i32 {
    x
}

fn fun(x: &i32, y:i32) -> &i32 {
    x
}


fn main() {
    let mut a = 10;
    {
        let ref mut b = a;
        *b = 20;
    }

    let ref b = a;

    let x = 7;
    let y = 10;
    let y = fun(&x, &y);

    println!("Hello, world! {} {}", a, *b);
}
