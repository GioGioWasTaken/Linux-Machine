/**
 * Q2
 */
public class Q2 {
  public static void main(String[] args) {
    int[] arr = {2,3,8,14,15,35};
    System.out.println(
      findAverage(arr,8) + " " +
      findAverage(arr,2.5)+ " " +
      findAverage(arr,10)+ " " +
      findAverage(arr,8.5)+ " "
    );
    System.out.println(
      "expected: true, true,true false" 
    );
  }
  public static boolean findAverage(int[] arr, double x) {
    if (arr.length == 0) {
      return false;
    }

    int count = 1;
    int currentSeriesStart = 0;
    double currSum = arr[0];

    if (currSum > x) {
      return false;
    } else if (currSum == x) {
      return true;
    }

    for (int i = 1; i < arr.length; i++) {
      int value = arr[i];
      currSum += value;
      count++;
      System.out.println( "Curr sum : " + 
        currSum / count 
      );
      while (currSum / count > x && count > 1) {
        currSum -= arr[currentSeriesStart];
        currentSeriesStart++;
        count--;
      }

      if (currSum / count == x) {
        return true;
      }

    }

    return false;
  }
}
