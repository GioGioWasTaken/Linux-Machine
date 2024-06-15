public class recursion_11 {
  public int countHi(String str) {
    if (str.length() <= 1) {
      return 0;
    } else {
      char firstChar = str.charAt(0);
      char secondChar = str.charAt(1);
      int isHi = 0;
      if (firstChar == 'h' && secondChar == 'i')
        // can be imporoved by taking a sub string, if we
        // had a larger word to check for, e.g.
        // currentString=str.substring(0,length-of-word-we-are-checking)
        isHi++;
      return isHi + countHi(str.substring(1));
    }
  }
}
