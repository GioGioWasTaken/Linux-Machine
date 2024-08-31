public class recursion_7 {
public int count7(int n) {
    // base case
    if(n%10 == n){
      if(n==7){
        return 1;
      } else{
        return 0;
      }
    }

    // recursive step
    if(n%10 == 7){
      return count7(n/10) + 1;
    } else{
      return count7(n/10);
    }
}

}
