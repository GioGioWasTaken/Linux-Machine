public class recursion_3 {

  
public int fibonacci(int n) {
    if(n==0){
      return 0;
    } else if(n==1){
      return 1;
    } else if(n==2){
      return 1;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}

}
