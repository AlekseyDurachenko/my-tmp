enum State {
    Started,
    Processing {cur: i32, total: i32},
    Stoped
}

fn next(state: State) -> State {
    match state {
        State::Started => {
            println!("started");
            State::Processing { cur: 0, total: 10 }
        },
        State::Processing {cur, total } => {
            println!("processing {} of {}", cur, total);
            if cur < total {
                State::Processing { cur: cur + 1, total: total }
            }
            else {
                State::Stoped
            }
        },
        State::Stoped => {
            println!("stoped");
            State::Stoped
        }
    }
}

fn main() {
    let mut status = State::Started;
    loop {
        status = next(status);
        match status {
            State::Stoped => break,
            _ => {}
        };
    }
}
