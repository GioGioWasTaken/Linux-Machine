/**
 * Q1
 */
public class Q1 {
	public static void main(String[] args) {
		System.out.println(
			count(7)
		);
	}

	public static int count(int sum){
		return count(sum,1);
	}
	public static int count(int sum, int currNum){
		// found 1
		if(sum==0){
			return 1;
		}  else if(sum<0){
			return 0;
		}
		// prevent the logic path where currNum is incremented forever and never returns
		if(currNum > sum){
			return 0;
		}
		return count(sum-currNum, currNum +1 ) + count(sum,currNum +1);
	}


}
