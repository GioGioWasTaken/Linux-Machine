class Solution {
  public boolean backspaceCompare(String s, String t) {
    int rightS = s.length() - 1;
    int rightT = t.length() - 1;

    while (rightS >= 0 || rightT >= 0) {
      rightS = getValidIndex(s, rightS);
      rightT = getValidIndex(t, rightT);

      if (rightS < 0 && rightT < 0) {
        return true; // Both strings are processed completely
      }
      if (rightS < 0 || rightT < 0) {
        return false; // One string is processed completely, the other is not
      }
      if (s.charAt(rightS) != t.charAt(rightT)) {
        return false; // Characters at current positions do not match
      }

      rightS--;
      rightT--;
    }

    return true; // Strings are considered equal if both are processed
                 // completely
  }

  public static int getValidIndex(String str, int currentIndex) {
    int countBackspace = 0;
    while (currentIndex >= 0) {
      if (str.charAt(currentIndex) == '#') {
        countBackspace++;
      } else if (countBackspace > 0) {
        countBackspace--;
      } else {
        break;
      }
      currentIndex--;
    }
    return currentIndex;
  }
}
