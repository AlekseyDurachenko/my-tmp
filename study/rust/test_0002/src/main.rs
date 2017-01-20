extern crate rand;

use std::io;
use rand::Rng;
use std::cmp::Ordering;

fn main() {
    println!("Wtf the number?");
    let secret_number = rand::thread_rng().gen_range(1, 101);
    loop {
        //println!("secret number: {}", secret_number);
        println!("please type a number.");
        let mut guess = String::new();
        io::stdin().read_line(&mut guess).expect("error get a number");
        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_)  => continue,
        };

        println!("your number: {}", guess);

        match guess.cmp(&secret_number) {
            Ordering::Less      => println!("too small"),
            Ordering::Greater   => println!("too big"),
            Ordering::Equal     => {
                println!("Win!");
                break;
            }
        }
    }
}
