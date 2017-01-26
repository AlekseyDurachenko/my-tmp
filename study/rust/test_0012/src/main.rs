enum State {
    Started,
    Processing { cur: i32, total: i32 },
    Stoped,
}

fn next(state: State) -> Option<State> {
    match state {
        State::Started => {
            println!("started");
            Some(State::Processing {
                cur: 0,
                total: 10,
            })
        }

        State::Processing { cur, total } => {
            println!("processing {} of {}", cur, total);
            if cur < total {
                Some(State::Processing {
                    cur: cur + 1,
                    total: total,
                })
            } else {
                Some(State::Stoped)
            }
        }

        State::Stoped => {
            println!("stoped");
            None
        }
    }
}

fn main() {
    let mut status = State::Started;
    loop {
        match next(status) {
            Some(new_status) => status = new_status,
            None => break,
        }
    }
}
