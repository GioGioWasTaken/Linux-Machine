public class palindrome {
  public static void main(String[] args) {
    System.out.println(isPalindrome("ABBA"));
    System.out.println(isPalindrome("ABC"));
  }

  public static boolean isPalindrome(String str) {
    if (str.length() < 2)
      return true;
    else {
      if (str.charAt(0) == str.charAt(str.length() - 1)) {
        return isPalindrome(str.substring(1, str.length() - 1));
      } else {
        return false;
      }
    }
  }
}
