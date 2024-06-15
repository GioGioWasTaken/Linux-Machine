public class recursion_31 {
  public int strDist(String str, String sub) {
    // Base case: if the string is shorter than the substring, return 0
    if (str.length() < sub.length()) {
      return 0;
    }

    // If the string starts and ends with the substring, return its length
    if (str.startsWith(sub) && str.endsWith(sub)) {
      return str.length();
    }

    // If the string does not start with the substring, remove the first
    // character
    if (!str.startsWith(sub)) {
      return strDist(str.substring(1), sub);
    }

    // If the string does not end with the substring, remove the last character
    if (!str.endsWith(sub)) {
      return strDist(str.substring(0, str.length() - 1), sub);
    }

    // If none of the above conditions are met, return 0 (although this line is
    // technically unreachable)
    return 0;
  }
}
