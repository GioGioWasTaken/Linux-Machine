public class recursion_4 {

  public int bunnyEars2(int bunnies) {
    if (bunnies == 0)
      return 0;
    if (bunnies % 2 == 0)
      return bunnyEars2(bunnies - 1) + 3; // even bunnies
    else {
      return bunnyEars2(bunnies - 1) + 2; // odd bunnies
    }
  }
}