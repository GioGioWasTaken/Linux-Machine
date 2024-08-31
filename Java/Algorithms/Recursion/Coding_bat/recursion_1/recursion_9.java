public class recursion_9 {
  public int powerN(int base, int n) {
    if(base==0){
      return 0;
    } if(base==1){
      return 1;
    }
    if(n==0){
      return 1;
    } else if(n==1){
      return base;
    }
    return base*powerN(base,n-1);
  }
}
