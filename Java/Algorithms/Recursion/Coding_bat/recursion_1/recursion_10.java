public class recursion_10 {

  public int countX(String str) {
    if (str.length() == 0) {
      return 0;
    } else {
      char currentChar = str.charAt(0);
      int isX = 0;
      if (currentChar == 'x')
        isX++;
      return isX + countX(str.substring(1));
    }
  }
}
