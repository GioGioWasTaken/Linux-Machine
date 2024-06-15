public class removedup {
  public static void main(String[] args) {
    System.out.println(RmvAdjDup("AAABBBCCDDD"));
  }

  public static String RmvAdjDup(String str) {
    if (str.length() < 2)
      return str;
    else {
      char currentChar = str.charAt(0);
      char nextChar = str.charAt(1);
      if (currentChar == nextChar) {
        return RmvAdjDup(str.substring(1));
      } else {
        return currentChar + RmvAdjDup(str.substring(1));
      }
    }
  }
}
