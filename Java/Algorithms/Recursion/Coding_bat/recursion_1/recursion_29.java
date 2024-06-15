public class recursion_29 {

  public int strCount(String str, String sub) {
    if (str.length() < sub.length()) {
      return 0;
    } else {
      String substr = str.substring(0, sub.length());
      if (substr.equals(sub)) {
        return 1 + strCount(str.substring(sub.length()), sub);
      } else {
        return strCount(str.substring(1), sub);
      }
    }
  }
}
