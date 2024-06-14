class Solution {
  public int totalFruit(int[] fruits) {
    if (fruits.length == 0) {
      return 0;
    } else if (fruits.length == 1) {
      return 1;
    } else if (fruits.length == 2) {
      return 2;
    }
    int p1 = fruits[0];
    int p2 = fruits[1];
    while (fruits[p2] == fruits[p1]) {
      p2++;
    }
    int p3 = ++p2;
    int GlobalMax = 2; // 2 is the minimum value that an array of more than 2
                       // fruit will have.
    while (p3 < fruits.length) {
      if (fruits[p3] == fruits[p1] || fruits[p3] == fruits[p2]) {
        GlobalMax = Math.max(GlobalMax, p3 - p1 + 1);
        p3++;
      } else {
        GlobalMax = Math.max(GlobalMax, p3 - p1 + 1);
        p1 = p3;
        p2 = ++p1;
        p3 = ++p2;
      }
    }
    return GlobalMax;
  }
}
