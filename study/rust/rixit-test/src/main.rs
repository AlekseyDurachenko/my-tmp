mod httprouter;

extern crate iron;
extern crate router;
extern crate rustc_serialize;


// use iron::prelude::*;
// use iron::status;
// use router::Router;
// use rustc_serialize::json;
// use std::collections::HashMap;
// use iron::Handler;





#[derive(RustcEncodable, RustcDecodable)]
struct Greeting {
    msg: String
}


fn hello(_ : &mut iron::Request) -> iron::IronResult<iron::Response> {
    println!("hello!\n");
    std::thread::sleep(std::time::Duration::from_secs(10));
    Ok(iron::Response::with((iron::status::Ok, "hello!")))
}


fn main() {
    let mut router = httprouter::HttpRouter::new();
    router.add_route("hello".to_string(), hello);

    iron::Iron::new(router).http("localhost:3000").unwrap();

    //println!("{}", url.path().iter().cloned().collect().join("/"));

    // let mut router = Router::new();
    //
    // router.get("/", hello_world, "index");
    // router.post("/:set", set_greeting, "set");
    //
    // fn hello_world(_: &mut Request) -> IronResult<Response> {
    //     let greeting = Greeting { msg: "Hello, World".to_string() };
    //     let payload = json::encode(&greeting).unwrap();
    //     Ok(Response::with((status::Ok, payload)))
    // }

    // Receive a message by POST and play it back.
    // fn set_greeting(request: &mut Request) -> IronResult<Response> {
    //     let mut payload = String::new();
    //     request.body.read_to_string(&mut payload).unwrap();
    //     let request: Greeting = json::decode(&payload).unwrap();
    //     let greeting = Greeting { msg: request.msg };
    //     let payload = json::encode(&greeting).unwrap();
    //     Ok(Response::with((status::Ok, payload)))
    // }

    // Iron::new(router).http("localhost:3000").unwrap();
}
