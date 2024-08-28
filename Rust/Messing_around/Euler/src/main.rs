mod euler_1;

fn main() {
    let num:u128= 1000;
    let mut result:u128 = 0;
    euler_1::euler_1(num, &mut result);
    print!("{}\n", result);
    print!("{}\n", num);
}
