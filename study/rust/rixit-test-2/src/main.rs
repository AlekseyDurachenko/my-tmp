#![feature(plugin)]
#![plugin(rocket_codegen)]

extern crate rocket;

mod consts {
    pub const RIXIT_IMG_PATH : &str = "RIXIT_IMG_PATH";
}


mod img {
    use std::env;
    use std::path::PathBuf;
    use rocket::response::NamedFile;

    #[get("/img/<id>")]
    pub fn img(id : u32) -> Option<NamedFile> {
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
}

#[get("/world")]              // <- route attribute
fn world() -> &'static str {  // <- request handler
    "Hello, world!"
}

fn main() {
    rocket::ignite().mount("/", routes![world, img::img]).launch();
}
