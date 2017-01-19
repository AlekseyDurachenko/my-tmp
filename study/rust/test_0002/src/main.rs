use std::io;

fn main() {
    println!("Wtf the number?");
    println!("please type a number.");
    let mut guess = String::new();
    io::stdin().read_line(&mut guess).expect("error get a number");
    println!("your number: {}", guess);
}
