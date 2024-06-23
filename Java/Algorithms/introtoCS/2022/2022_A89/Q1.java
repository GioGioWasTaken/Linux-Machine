public class Q1 {
  public static void main(String[] args) {}

  public static boolean isJump(String str1, String str2, int step) {
    if (str2.equals(""))
      return true;

    if (str1.charAt(0) == str2.charAt(0))
      return isJump(str1.substring(step), str2.substring(1), step);

    return false;
    public static int strStep(String str1, String str2) {
      return strStep(str1, str2, 1);
    }

    public static int strStep(String str1, String str2, int curStep) {
      int maxStep = str1.length() / str2.length();
      if (curStep > maxStep) {
        return -1;
      }
      if (isJump(str1, str2, curStep)) {
        return curStep;
      }
      return strStep(str1, str2, curStep + 1);
    }
  }
