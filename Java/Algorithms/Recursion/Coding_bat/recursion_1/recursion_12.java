public class recursion_12 {

  public String changeXY(String str) {
    if (str.length() == 0)
      return str;
    else {
      char currentChar = str.charAt(0);
      if (currentChar == 'x') {
        currentChar = 'y';
      }
      return currentChar + changeXY(str.substring(1));
    }
  }
}
