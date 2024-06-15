public class recursion_2 {
  public int bunnyEars(int bunnies) {
    if (bunnies == 0)
      return 0;
    else {
      return bunnyEars(bunnies - 1) + 2;
    }
  }
}
