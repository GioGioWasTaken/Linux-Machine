/**
 * Q2
 */
public class Q2 {
  public static void main(String[] args) {
   System.out.println(findTriplet(new int[] {-4,1,-8,9,6})); 
    System.out.println("expected above to be 288");
  }
  public static int findTriplet(int[] arr){
    int FirstSum = arr[0] * arr[1] * arr[2]; // it is guranteed that the array holds at least 3 elements. 
    int[] triplet = {arr[0], arr[1], arr[2]};
    if(arr.length ==3){
      return FirstSum;
    } 
    int globalMax = Integer.MIN_VALUE;
    if(FirstSum > globalMax) {
      globalMax = FirstSum;
    }
    int[] savedValues = {Integer.MIN_VALUE, Integer.MIN_VALUE, Integer.MIN_VALUE};
    // savedValues = [_1stBiggest, _2ndBiggest, _3rdBiggest]

    // Goes over all the array once, and saves the 3 highest numbers and the 2 lowest negative numbers.
    for (int i = 0; i < arr.length; i++) {
      if(arr[i] > savedValues[0]){
        savedValues[2] = savedValues[1];
        savedValues[1] = savedValues[2];
        savedValues[1] = arr[i];
      }
      else if(arr[i] > savedValues[1]){
        savedValues[2]=savedValues[1];
        savedValues[1] = arr[i]
      }
      else if(arr[i] > savedValues[2]){
        savedValues[2] = arr[i];
      }
    }
  }
}
