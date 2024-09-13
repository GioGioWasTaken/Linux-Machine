public class Q1 {
    public static void main(String[] args) {
        System.out.println(OneFiveSeven(10)); // Output should be 2
    }

    public static int OneFiveSeven(int n) {
        if (n < 0) {
            return Integer.MAX_VALUE; // Invalid solution
        }
        if (n == 0) {
            return 0; // Base case
        }

        int option1 = OneFiveSeven(n - 7);
        int option2 = OneFiveSeven(n - 5);
        int option3 = OneFiveSeven(n - 1);

        // Only increment the valid options (i.e., those that are not Integer.MAX_VALUE)
        int min = Math.min(option1, Math.min(option2, option3));
        if (min == Integer.MAX_VALUE) {
            return Integer.MAX_VALUE; // No valid option
        }

        return min + 1; // Add the current step
    }
}
