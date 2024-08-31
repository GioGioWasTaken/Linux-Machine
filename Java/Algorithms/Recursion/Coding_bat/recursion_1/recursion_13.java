public class recursion_13 {

  public String changePi(String str) {
    if(str.length() == 0){
      return "";
    } else if (str.length() == 1){
      return "" +str.charAt(0);
    }
    char first_char = str.charAt(0);
    char second_char = str.charAt(1);
    if(first_char=='p' && second_char == 'i'){
      return "3.14" + changePi(str.substring(2));
    } else {
      return first_char + changePi(str.substring(1));
    }
  }
}
