use std::env;
use std::path::PathBuf;
use rocket::response::NamedFile;


#[get("/img/<id>")]
fn img(id: u32) -> Option<NamedFile> {
    match env::var(::consts::RIXIT_IMG_PATH) {
        Ok(img_path) => {
            let mut filename = PathBuf::from(img_path);
            filename.push(id.to_string());
            filename.set_extension("jpg");
            match NamedFile::open(&filename) {
                Ok(val) => Some(val),
                Err(_) => {
                    println!("file not found: {}", filename.as_path().to_string_lossy());
                    None
                }
            }
        }
        Err(_) => {
            println!("environment variable {} is not set", ::consts::RIXIT_IMG_PATH);
            None
        }
    }
}
