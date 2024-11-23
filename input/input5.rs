const a: i32 = 1;
const b: i64 = 2;
const c: i32 = 3;
const d: u64 = 4u64;
const e: bool = false;

fn factorial(n: i32) -> i32 {
    if n == 0 {
        return 1;
    }
    return n * factorial(n-1);
}

fn test() -> i32 {
    return 1;
}

fn main() {
    let mut x: i32 = -6;
    let mut y: i32 = -7;
    let mut z: u64;

    x = 5;
    y = a;
    z = 6;
 
    for i in 1..5 {
        println!("{} {}", c, 2);
    }
    
    let abc = test();

    //println!("{}", abc); //factorial(5));

    println!("{}", x);
    println!("{}", y);
    println!("{}", z);
}