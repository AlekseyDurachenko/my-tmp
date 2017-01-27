enum List {
    Cons(u32, Box<List>),
    Nil,
}

impl List {
    fn new() -> List {
        List::Nil
    }

    fn prepend(self, elem: u32) -> List {
        List::Cons(elem, Box::new(self))
    }

    fn len(&self) -> u32 {
        match *self {
            List::Cons(_, ref tail) => 1 + tail.len(),
            List::Nil => 0,
        }
    }

    fn to_string(&self) -> String {
        match *self {
            List::Cons(head, ref tail) => format!("{}, {}", head, tail.to_string()),
            List::Nil => format!("Nil"),
        }
    }

    fn next(&self) -> List {
        match *self {
            List::Cons(val, ref tail) => List::Cons(val, *tail),
            List::Nil => List::Nil,
        }
    }
}

fn main() {
    let mut l1 = List::new();
    l1 = l1.prepend(1);
    l1 = l1.prepend(2);
    l1 = l1.prepend(3);
    println!("len = {}", l1.len());
    println!("{}", l1.to_string());
    println!("len = {}", l1.next().len());
    println!("{}", l1.next().to_string());
}
