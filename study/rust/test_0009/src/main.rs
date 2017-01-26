use std::fmt;

fn reverse(pair : (i32, bool)) -> (bool, i32) {
    let (integer, boolean) = pair;
    (boolean, integer)
}


struct Matrix(f32, f32, f32, f32);

fn transpose(matrix : Matrix) -> Matrix {
    let Matrix(a11, a12, a21, a22) = matrix;
    Matrix(a11, a21, a12, a22)
}


impl fmt::Display for Matrix {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "(( {} {} ), ( {} {} ))", self.0, self.1, self.2, self.3)
    }

}

fn main() {
    println!("Rev: {:?}", reverse((666i32, true)));
    println!("Mastrix: {}", Matrix(1.0,2.0,3.0,4.0));
    println!("Transponse: {}", transpose(Matrix(1.0,2.0,3.0,4.0)));
}
