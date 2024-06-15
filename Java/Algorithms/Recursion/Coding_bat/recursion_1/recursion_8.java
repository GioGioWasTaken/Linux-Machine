public class recursion_8 {
  public int count8(int n) {
    if (n % 10 == n)
      if (n == 8)
        return 1;
      else
        return 0;
    else {
      if (count8((n / 10) % 10) == 1 && count8(n % 10) == 1) {
        return count8(n % 10) + count8(n / 10) + 1;
      } else {
        return count8(n % 10) + count8(n / 10);
      }
    }
  }
}
