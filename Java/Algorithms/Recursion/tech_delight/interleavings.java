public class interleavings {
  public static void main(String[] args) {
    System.out.println(FindInterleaving("ABC", "ACB"));
  }

  public static String FindInterleaving(String str1, String str2) {
    if (str1.length() == 0) {
      return str1;
    } else {
    }
    if (str2.length() == 0) {
      return str2;
    }
    return str1.concat("\n" + str2);
  }
}
