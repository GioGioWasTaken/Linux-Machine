public class findMissing {
  public static void main(String[] args) {
    int[] arr1 = { 22, 24, 26, 32, 34, 36, 38, 40 }; // 3
    int[] arr2 = { 22, 26, 28 }; // 1
    int[] arr3 = { 2, 4, 6, 8, 10 }; // 5
    System.out.println(findMissingIndex(arr1));
    System.out.println(findMissingIndex(arr2));
    System.out.println(findMissingIndex(arr3));
  }

  public static int findMissingIndex(int[] a) {
    int d;
    if (a[1] - a[0] == a[2] - a[1]) {
      d = a[1] - a[0]; // d for difference
    } else {
      if (a[1] - a[0] > a[2] - a[1]) {
        d = a[2] - a[1];
      } else {
        d = a[1] - a[0];
      }
    } // we first must find out the sequence d.
    if (a[a.length - 1] - ((a.length - 1) * d) == a[0])
      return a.length;
    // if all elements are in tact, the d between a[0] and the last
    // indexed element should be d*a.length-1, which is the amount of
    // elements between them.
    int l = 0;
    int r = a.length - 1;
    int m = -1;
    while (l <= r) {
      m = l + (r - l) / 2;
      if (a[m] > a[0] + d * m) {
        r = m - 1;
      } else {
        l = m + 1;
      }
    }
    return m + 1;
  }
}
