use std::thread;
use mio::{EventLoop, Handler};

struct MyHandler;

impl Handler for MyHandler {
    type Timeout = ();
    type Message = u32;

    fn notify(&mut self, event_loop: &mut EventLoop<MyHandler>, msg: u32) {
        assert_eq!(msg, 123);
        event_loop.shutdown();
    }
}
fn main() {
    let mut event_loop = EventLoop::new().unwrap();
    let sender = event_loop.channel();

    // Send the notification from another thread
    thread::spawn(move || { let _ = sender.send(123); });

    let _ = event_loop.run(&mut MyHandler);
}
