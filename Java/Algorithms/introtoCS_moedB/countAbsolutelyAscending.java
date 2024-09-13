/**
 * countAbsolutelyAscending
 */
public class countAbsolutelyAscending {

	public static void main(String[] args) {
		System.out.println(
			count(7)
		);
	}

	public static int count(int sum){
		return count(sum, sum, 1);
	}
	public static int count(int sum, int original_sum, int n){
		if(original_sum == 0){
			return 1; // empty ascending series has 1 valid solution
		}
		if(sum == 0 ){
			return 1;
		}
		if(n > original_sum){
			return 0;
		}
		return count(sum-n,original_sum,n+1) + count(sum,original_sum,n+1);
	}
}
