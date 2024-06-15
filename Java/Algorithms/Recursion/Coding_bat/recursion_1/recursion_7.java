public class recursion_7 {
  public int count7(int n) {
    if (n % 10 == n)
      if (n == 7)
        return 1;
      else
        return 0;
    else {
      return count7(n % 10) + count7(n / 10);
    }
  }
}
