public class Q2 {
    public static void main(String[] args) {
        int[] a = {10, 20, 30, 40};
        int[] b = {0, 4, 6, 11, 11};
        printClosest(a, b, 11);
    }

    public static void printClosest(int[] a, int[] b, int x) {
        int value1 = -1;
        int value2 = -1;
        int smallestDiff = Integer.MAX_VALUE;
        int p1 = 0;
        int p2 = b.length - 1;

        while (p1 <= a.length - 1 && p2 >= 0) {
            int sum = a[p1] + b[p2];
            int diff = Math.abs(sum - x);  // Correct difference calculation

            if (diff < smallestDiff) {
                value1 = a[p1];
                value2 = b[p2];
                smallestDiff = diff;
            }

            if (sum > x) {
                p2--;
            } else {
                p1++;
            }
        }

        System.out.println("Closest pair is: " + value1 + " and " + value2);
    }
}
