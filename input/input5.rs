const xd: i32 = 10;

fn test(a: i32) -> i32 {
    return a;
}

fn main() {
    let mut x = 1;
    let mut y: i32 = xd;
    let mut z: i32;

    x = 5;
    y = xd + 1;
    z = 1000000;

    test(xd);

    println!("{}", x);
    println!("{}", y);
    println!("{}", z);
}