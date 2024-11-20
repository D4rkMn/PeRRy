const xd: i32 = 10;

fn main() {
    let mut x: i32 = 6;
    let mut y: i32 = xd;
    let mut z: i32;

    x = 5;
    y = xd + 5;
    z = 1000000;

    for i in 1+1..2+3 {
        println!("{} {}", xd, 2+xd);
    }

    println!("{}", x);
    println!("{}", y);
    println!("{}", z);
}