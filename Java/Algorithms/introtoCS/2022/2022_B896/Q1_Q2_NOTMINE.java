package Exam_2022_B96.Q1_Q2;

/**  Gilmore & the Dragon
 *                       ,-,-
 *                      / / |
 *    ,-',            _/ / /
 *   (-_  )       _,-' `Z_/
 *    "#:      ,-'_,-.    \  _
 *     #'    _(_-'_()\     \" |
 *   ,--_,--'                 |
 *  / ""                      L-'\
 *  \,--^---v--v-._        /   \ |
 *    \_________________,-'      |
 *                     \
 *                      \
 *                       \
 *   created by M.F.
 *   version: v1.0
 */

public class Q1_Q2 {


        public static void main(String[] args) {
            System.out.println(calc(3, 36, 4));
            System.out.println(calc(5,50,4));

            int [] arr = {3,0,0,4,7,9,0,0,0,0,11,15,0,19,20,0,0,31,40,0};
            System.out.println(searchAlmostKSorted(arr, 9)); // output: 5
            System.out.println(searchAlmostKSorted(arr, 31)); // output: 17
            System.out.println(searchAlmostKSorted(arr, 30)); // output: -1
            int [] arr2 = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            int [] arr3 = {0,0,0,0,0,0,0,0};
            System.out.println(searchAlmostKSorted(arr2,1));
            System.out.println(searchAlmostKSorted(arr3,1));
        }


        public static int calc(int num, int result, int maxOp){

            return calc(num,result,maxOp,0,String.valueOf(num),num);
        }


        private static int calc(int num, int result, int maxOp, int currentOp, String str, int currentValue) {
            // If the operation count has exceeded the max allowed, return 0
            if (currentOp > maxOp) {
                return 0;
            }

            // If the current value is equal to the result, print the expression and return 1
            if (currentValue == result) {
                System.out.println(str + " = " + result);
                return 1;
            }

            // Try all the operations recursively
            int total = 0;
            if (currentOp < maxOp) {
                total += calc(num, result, maxOp, currentOp + 1, str + " + " + num, currentValue + num);
                total += calc(num, result, maxOp, currentOp + 1, str + " - " + num, currentValue - num);
                total += calc(num, result, maxOp, currentOp + 1, str + " * " + num, currentValue * num);
                if (currentValue % num == 0) {
                    total += calc(num, result, maxOp, currentOp + 1, str + " / " + num, currentValue / num);
                }
            }

            return total;
        }





        public static int searchAlmostKSorted(int[] arr, int num) {
            int low = 0, high = arr.length - 1;
            while(low <= high) {
                int mid = (low + high) / 2;
                if (arr[mid] == num) {
                    return mid;
                }
                if(arr[mid] == 0) {
                    // If zero is encountered, shift the search space to non-zero numbers.
                    int midLeft = mid - 1;
                    int midRight = mid + 1;
                    while(midLeft >= low && arr[midLeft] == 0) {
                        midLeft--;
                    }
                    while(midRight <= high && arr[midRight] == 0) {
                        midRight++;
                    }
                    // Check which one is closer to the search number.
                    if(midLeft < low || (midRight <= high && Math.abs(arr[midRight] - num) < Math.abs(arr[midLeft] - num))) {
                        low = midRight;
                    } else {
                        high = midLeft;
                    }
                } else if(arr[mid] < num) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            return -1;
        }



}




