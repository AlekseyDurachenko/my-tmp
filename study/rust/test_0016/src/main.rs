struct SingleGen<T>(T);
struct TwoGen<T, M>(T, M);

struct A;          // Concrete type `A`.
struct S(A);       // Concrete type `S`.
struct SGen<T>(T); // Generic type `SGen`.


fn reg_fn(_s: S) {}

fn gen_spec_t(_s: SGen<A>) {}

fn gen_spec_i32(_s: SGen<i32>) {}

fn generic<T>(_s: SGen<T>) {}


fn main() {
    let _x = SingleGen(6);
    let _y = SingleGen("abc");
    let _z = TwoGen("abc", 7);

    reg_fn(S(A));
    gen_spec_t(SGen(A));
    gen_spec_i32(SGen(6));
    generic::<char>(SGen('a'));
    generic(SGen('c'));
}
