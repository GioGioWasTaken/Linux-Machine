public class regular_expr {
  public boolean isMatch(String s, String p) {
    return isMatchHelper(s, p, 0, 0);
  }

  private boolean isMatchHelper(String s, String p, int sIndex, int pIndex) {
    // Base case: if both strings reach their ends, they match.
    if (sIndex == s.length() && pIndex == p.length()) {
      return true;
    }

    // If the pattern is exhausted but the string is not, they don't match.
    if (pIndex == p.length()) {
      return false;
    }

    if (sIndex == s.length()) {
      return false;
    }

    // If the current character is *, try to match 0 or more characters.
    if (p.charAt(pIndex) == '*') {
      // Check 0 characters matched with *
      if (isMatchHelper(s, p, sIndex, pIndex + 1)) {
        return true;
      }

      // Check 1 or more characters matched with *
      return (sIndex < s.length()) && isMatchHelper(s, p, sIndex + 1, pIndex);
    }

    // If the current character is ? or matches with the corresponding character
    // in s, proceed.
    if (sIndex < s.length() &&
        (p.charAt(pIndex) == '?' || p.charAt(pIndex) == s.charAt(sIndex))) {
      return isMatchHelper(s, p, sIndex + 1, pIndex + 1);
    }

    // If none of the above conditions match, they don't match.
    return false;
  }
}
