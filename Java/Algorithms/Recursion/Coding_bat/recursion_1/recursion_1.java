public class recursion_1 {

  public static void main(String[] args) {
    System.out.println(factorial(6));
  }

  public int factorial(int n) {
    if (n == 0)
      return 1;
    else {
      return factorial(n - 1) * n;
    }
  }
}
