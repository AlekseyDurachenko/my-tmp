// open.rs
use std::error::Error;
use std::fs::File;
use std::fs;
use std::path;
use std::io::prelude::*;
use std::path::Path;
use std::io::BufReader;
use std::env;

fn main() {
    // Create a path to the desired file
    let path = std::env::home_dir().unwrap().join(Path::new(".emacs"));

    // Open the path in read-only mode, returns `io::Result<File>`
    let mut file = match File::open(&path) {
        // The `description` method of `io::Error` returns a string that
        // describes the error
        Err(why) => panic!("couldn't open {}: {}", path.display(),
                                                   why.description()),
        Ok(file) => file,
    };

    let mut buffer : String = "".to_owned();
    let mut bf = BufReader::new(&file);
    println!("{:?}", bf.read_line(&mut buffer));
    println!("{}", buffer);



    // `file` goes out of scope, and the "hello.txt" file gets closed
}
