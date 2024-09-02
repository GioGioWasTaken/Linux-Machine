public class Q1 {
  public static void main(String[] args) {
    System.out.println( "true:" +
      isJump("adbrcfa","abc",2)
    );
  }

  public static int strStep(String str1, String str2) {
    return strStep(str1,str2,1);
  }

  public static int strStep(String str1, String str2, int step) {
    int max_step = str1.length()/ str2.length();
    if(step <=max_step ){
      return -1;
    }
    if(!isJump(str1,str2,step)){
      return strStep(str1,str2,step+1);
    } else{
      return step;
    }
  }
  public static boolean isJump(String str1, String str2, int step) {
    return isJump(str1,str2,step,0);
  }


  public static boolean isJump(String str1, String str2, int step, int index) {
    if(str1.length() <str2.length()){
      return false;
    }
    if(step*str2.length() > str1.length()){
      return false;
    }
    if(index==str2.length()-1){
    if(str1.charAt(step*index) == str2.charAt(index)){
        return true;
      }
    }
    if(str1.charAt(step*index) == str2.charAt(index)){
      return isJump(str1,str2,step,index+1);
    } else{
      return false;
    }
  }
}
