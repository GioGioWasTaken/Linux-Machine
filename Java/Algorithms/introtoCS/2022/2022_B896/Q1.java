/**
 * Q1
 */
public class Q1 {
    public static void main(String[] args) {
        System.out.println(calc(3,36,4)); 
    }
 public static int calc(int num, int result, int maxOp) {
        // Call the overridden function with the starting values:
        // tempResult = num
        // equationStr = num, as string.
        return calc(num, result, num, maxOp, ""+num);
        // might look a bit weird, but ""+num is a concise way to convert it to a string.
    }

    private static int calc(int num, int result, int tempResult, int maxOp, String equationStr) {
        
        // Checks if passed max operations.
        if (maxOp < 0)
            return 0;

        // Checks if the current equation equals to result.
        // if so, prints the equation as requested.
        if (tempResult == result) {
            // Prints suitable equation.
            System.out.println(equationStr + " = " + result);
            return 1;
        }
        
        // Create new 4 recurtion calls with all possible operations as changing the right data. (tempResult and equationStr)
        return calc(num, result, tempResult + num, maxOp - 1, (equationStr + " + " + num)) +
                calc(num, result, tempResult - num, maxOp - 1, (equationStr + " - " + num)) +
                calc(num, result, tempResult * num, maxOp - 1, (equationStr + " * " + num)) +
                calc(num, result, tempResult / num, maxOp - 1, (equationStr + " / " + num));

    }
}
    




    // public static int calc(int num, int result, int maxOp, int sum , String equation){
    //         if(operation.equals("&")){ // all inputs tried
    //             return 0; }
    //     if(sum == result){
    //             equation += "=" + sum;
    //             System.out.println(equation); // maybe we can use this string as a comparison to prevent infinite loops
    //             if(operation.equals("+"))
    //                 return 1 + calc(num, result, maxOp,sum,num +"-");
    //             if(operation.equals("-"))
    //                 return 1 + calc(num, result, maxOp,sum,num +"*");
    //             if(operation.equals("*"))
    //                 return 1 + calc(num, result, maxOp,sum,num +"/");
    //             if(operation.equals("/"))
    //                 return 1 + calc(num, result, maxOp,sum,num +"&");
    //         }
    //         if(maxOp == 0){
    //             return 0;
    //         }
    //         switch (operation) {
    //             case "+":
    //             sum+=num;
    //             return calc(num, result, maxOp-1, sum, "+", equation + "+" + num);
    //             
    //             case "-":
    //             sum-=num ;
    //             return calc(num, result, maxOp-1, sum, "-", equation + "-"+ num);
    //             
    //             case "*":
    //             sum*=num ;
    //             return calc(num, result, maxOp-1, sum, "*", equation + "*" + num);
    //             
    //             case "/":
    //             sum/=num ;
    //             return calc(num, result, maxOp-1, sum, "/", equation + "/" + num);
    //             
    //             default: // & will never reach this part of the code.
    //             System.out.println("Invalid operation");
    //             return -1; 
    //         }
