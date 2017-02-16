#[derive(FromForm)]
struct CreateGame {
    card_count: u32,
    creator_name: u32,
}


#[get("/api/<method>")]
fn api(method: String) -> String {
    "Hello, world!".to_string()
}
