/**
 * Q1
 */
public class Q1 {

	public static void main(String[] args) {
		System.out.println(countPairs(3));		
	}	
	public static int countPairs (int n){
		return countPairs(n-1, "(", n);
	}

	public static int countPairs (int open, String expr, int close){
		if(close <open){
			return 0;
		}
		if(open==0){
			if(open!=close){
				return 0 + countPairs(open,expr +")", close-1);
			} else if(open==close){
				System.out.println(expr);
				return 1;
			}
		}
		return countPairs(open -1, expr+"(", close) + countPairs(open, expr+")", close -1);
	}
}
