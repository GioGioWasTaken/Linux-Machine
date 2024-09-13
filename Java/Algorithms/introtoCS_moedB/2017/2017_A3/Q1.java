
/**
 * Q1
 */
public class Q1 {
    public static void main(String[] args) {
        System.out.println(
            ways(4,2)
        );
    }
    public static int ways(int k ,int n){
        if(k==0 ){
            if(n==0){
                return 1;
            } else{
                return 0;
            }

        }
        return ways(k-1, n-1)+ ways(k-1, n+1);
    }
    
}
