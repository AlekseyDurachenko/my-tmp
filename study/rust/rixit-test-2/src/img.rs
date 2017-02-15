#![feature(plugin)]
#![plugin(rocket_codegen)]

extern crate rocket;

use std::env;
use std::path::PathBuf;
use rocket::response::NamedFile;

const RIXIT_IMG_PATH : &str = "RIXIT_IMG_PATH";


#[get("/img/<id>")]
fn img(id : u32) -> Option<NamedFile> {
    match env::var(RIXIT_IMG_PATH) {
        Ok(img_path) => {
            let mut filename = PathBuf::from(img_path);
            filename.push(id.to_string());
            filename.set_extension("jpg");
            NamedFile::open(filename).ok()
        }
        Err(_) => {
            None
        }
    }
}
