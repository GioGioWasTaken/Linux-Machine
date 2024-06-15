public class recursion_27 {
  public String parenBit(String str) {
    // Base case: if the string is empty, return an empty string
    if (str.isEmpty()) {
      return "";
    }

    // Check if the first character is '('
    if (str.charAt(0) == '(') {
      // Check if the last character is ')'
      if (str.charAt(str.length() - 1) == ')') {
        return str;
      } else {
        // If the last character is not ')', recurse by removing the last
        // character
        return parenBit(str.substring(0, str.length() - 1));
      }
    } else {
      // If the first character is not '(', recurse by removing the first
      // character
      return parenBit(str.substring(1));
    }
  }
}
