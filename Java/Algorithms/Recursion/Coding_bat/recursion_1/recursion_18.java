import java.lang.Character.Subset;

public class recursion_18 {
  public String allStar(String str) {
    if(str.length() ==0){
      return "";
    }
    if(str.length() ==1 ){
      return ""+str.charAt(0);
    } else{
      return str.charAt(0) + "*" + allStar(str.substring(1));
    }
  }
}
