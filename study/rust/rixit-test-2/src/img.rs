extern crate rocket;

use std::env;
use std::path::PathBuf;
use rocket::response::NamedFile;


#[get("/img/<id>")]
fn img(id : u32) -> Option<NamedFile> {
    match env::var(::consts::RIXIT_IMG_PATH) {
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
