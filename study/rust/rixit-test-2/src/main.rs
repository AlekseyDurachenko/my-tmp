#![feature(plugin)]
#![plugin(rocket_codegen)]

extern crate rocket;
mod consts;
mod img;
mod api;

fn main() {
    rocket::ignite().mount("/", routes![api::api, img::img]).launch();
}
