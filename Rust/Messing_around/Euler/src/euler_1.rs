pub fn euler_1(num:u128, res: &mut u128) {
    let mut sum:u128= 0;
    for i in 1..num{
        if(i%3 ==0 || i%5==0){
            sum+=i;
        }
    }
    println!("total : {}\n",sum);
    *res=sum;
}
