#![feature(plugin)]
#![plugin(rocket_codegen)]

extern crate rocket;
mod consts;
mod img;


#[get("/world")]
fn world() -> &'static str {
    "Hello, world!"
}

fn main() {
    rocket::ignite().mount("/", routes![world, img::img]).launch();
}
