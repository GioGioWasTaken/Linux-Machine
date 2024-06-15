import java.lang.Character.Subset;

public class recursion_18 {
  public String allStar(String str) {
    if (str.length() < 2)
      return str;
    else {
      char currentChar = str.charAt(0);
      return Character.toString(currentChar) + "*" + allStar(str.substring(1));
    }
  }
}
