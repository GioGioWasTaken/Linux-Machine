// print all possible pairs of parenthesis given an integer n
public class recursion_27_extended {
  public static void main(String[] args) {
    genParenthesis(3);
  }
  public static void genParenthesis(int num) {
    genParenthesisHelper(1,0,num, "(");
  }
  public static void genParenthesisHelper(int open, int close, int max, String res){
    // base cases
    if(max==0){
      return;
    }
    if(open==close && open == max){
      System.out.println(res);
      return;
    } 

    if(open < max ){
      genParenthesisHelper(open +1 , close, max, res + "(");
    } 

    if(close < open){
      genParenthesisHelper(open  , close+1, max, res + ")");
    }
}



}
