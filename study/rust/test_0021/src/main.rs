use std::thread;
use std::time;

static NTHREADS: i32 = 10;

fn main() {
    let mut children = vec![];

    for i in 0..NTHREADS {
        children.push(thread::spawn(move || {
            println!("this is thread number {}", i);
            thread::sleep(time::Duration::from_millis(2000))
        }));
    }

    for child in children {
        let _ = child.join();
    }

    println!("main thread ends");
}
