fn main() {
    println!("Hello, world!");

    let x = 6;
    println!("sqrt({x}) = {}", sqr(x));
}

fn sqr(x: i32) -> i32 {
    x * x
}
