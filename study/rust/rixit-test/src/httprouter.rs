extern crate iron;
use std::collections::HashMap;


pub struct HttpRouter {
    routes: HashMap<String, Box<iron::Handler>>
}


impl HttpRouter {
    pub fn new() -> Self {
        HttpRouter {
            routes: HashMap::new()
        }
    }

    pub fn add_route<H>(&mut self, path: String, handler: H) where H: iron::Handler {
        self.routes.insert(path, Box::new(handler));
    }
}


impl iron::Handler for HttpRouter {
    fn handle(&self, req: &mut iron::Request) -> iron::IronResult<iron::Response> {
        match self.routes.get(&req.url.path().iter().filter(|&i| !i.is_empty()).cloned().collect::<Vec<&str>>().join("/")) {
            Some(handler) => handler.handle(req),
            None => Ok(iron::Response::with(iron::status::NotFound))
        }
    }
}
