public class recursion_13 {

  public String changePi(String str) {
    if (str.length() < 2) {
      return str;
    } else {
      String currentString = str.substring(0, 2);
      if (currentString.equals("pi")) {
        return "3.14" + changePi(str.substring(2));
      }
      return str.charAt(0) + changePi(str.substring(1));
    }
  }
}
