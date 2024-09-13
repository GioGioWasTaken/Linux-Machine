/**
 * Q2
 */
public class Q2 {
  public static void main(String[] args) {
    int[] arr = {-1,1,-1,-5,2,2};
    System.out.println(
      longestSubarray(arr)
    );
  }
  public static int longestSubarray(int[] a){
    int MaxLength = 1;
    int length = 1;
    int MaxStartIndex = 0; // the Index from which the longest subarray as described starts from.
    int startIndex = 0;
    boolean isNegative;
    if(a[0] > 0){
      isNegative = false;
    } else{
      isNegative = true;
    }
    for(int i =1 ; i <a.length-1;i++){
      if(a[i] > 0 && isNegative == false){
        // both positive
        length = 1;
        startIndex = i;
      } else if(a[i] < 0 && isNegative == true){
        // both negative
        length = 1;
        startIndex = i;
      } else{
        length++;
        isNegative=(!isNegative);
      }

      if(length>MaxLength){
        MaxStartIndex = startIndex; 
        MaxLength = length;
      }
    }
    System.out.println("Starting index = " + MaxStartIndex);
    int MaxEndIndex = MaxStartIndex+MaxLength-1;
    System.out.println("Ending index = " + MaxEndIndex);
    return MaxLength;
  }
}
