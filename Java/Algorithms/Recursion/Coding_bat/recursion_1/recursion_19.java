import java.lang.Character.Subset;

public class recursion_19 {
  public String pairStar(String str) {
    if(str.length() ==0){
      return "";
    } else if(str.length() ==1){
      return ""+ str.charAt(0);
    } else{
      if(str.charAt(0) == str.charAt(1)){
        return "" + str.charAt(0) + "*" + pairStar(str.substring(1));
      } else{
        return "" + str.charAt(0) + pairStar(str.substring(1));
      }
    }
  }
}
