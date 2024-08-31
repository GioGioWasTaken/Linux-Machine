public class recursion_6 {

  
public int sumDigits(int n) {
    if(n%10 ==n){
      return n;
    } 
    return sumDigits(n/10) + n%10;
}

}
