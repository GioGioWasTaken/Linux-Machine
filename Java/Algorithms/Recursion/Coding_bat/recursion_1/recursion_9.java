public class recursion_9 {
  public int powerN(int base, int n) {
    if (base == 0)
      return 0;
    if (base == 1)
      return 1;
    if (n == 1)
      return base;
    else {
      return powerN(base, n - 1) * base;
    }
  }
}
