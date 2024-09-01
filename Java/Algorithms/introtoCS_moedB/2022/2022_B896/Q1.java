/**
 * Q1
 */
public class Q1 {
    public static void main(String[] args) {
        System.out.println(calc(3,36,4)); 
    }
    public static int calc(int num, int target, int maxOp) {
        int addition = 1;
        int subtraction =2;
        int multiplication =3;
        int division =4;
        return calcHelper(num,target,maxOp, num+ "+", 0, addition);
    }

    /* first operator used by the first call.*/
    public static int calcHelper(int num, int target, int maxOp, String expr, int current_value, int first_operator) {
        if(current_value == target){
            System.out.println( expr);
            switch(first_operator){
                case 1:
                return 1 + calcHelper(num,target,maxOp,target+"-",0,2);
                case 2:
                return 1 + calcHelper(num,target,maxOp,target+"*",0,2);
                case 3:
                return 1 + calcHelper(num,target,maxOp,target+"/",0,2);
                case 4:
                return 0;
            }
        }
    }
}
