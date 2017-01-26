use std::mem;

fn analyze_slice(slice: &[i32]) {
    println!("first: {}", slice[0]);
    println!("len: {}", slice.len());
    println!("last: {}", slice[slice.len()-1]);
}

fn main() {
    let xs: [i32; 5] = [1, 2 ,3 ,4 ,5];
    let ys: [i32; 500] = [0; 500];
    println!("{} {}", mem::size_of_val(&xs), mem::size_of_val(&ys));
    analyze_slice(&xs);
    println!("------");
    analyze_slice(&xs[1 .. 4]);
    println!("------");
    analyze_slice(&xs[..]);
}
