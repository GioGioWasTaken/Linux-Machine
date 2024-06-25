/**
 * Q2
 */
public class Q2 {
  public static void main(String[] args) {
    
  }
  public static int longestSubarray(int[] a){
    int isNegative = 0;
     if(a[0] < 0) {
        isNegative = 1;
      }
    int maxCount = 1;
    int count  = 1;
    for (int i = 1; i < a.length; i++) {
      if(a[i] <0 && isNegative==0){
        count++;
        isNegative =1;
      } else if(a[i] > 0 && isNegative==1;){
        count++;
        isNegative = 0;
      } else{
        count = 0;
      }
      if(count > maxCount){
        maxCount = count;
      }
    }
    return maxCount;
  }
}
