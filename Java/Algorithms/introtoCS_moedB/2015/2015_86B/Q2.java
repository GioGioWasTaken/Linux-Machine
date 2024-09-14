/**
 * Q2
 */
public class Q2 {
	public static void printPairs(int[] arr, int k){
		int l = 0;
		int r = l+1;
		while(l<=arr.length-1){
			int diff = Math.abs(arr[l] -arr[r]);
			if(diff ==k){
				System.out.println(
					"pair: (" + arr[l] + "," + arr[r] + ")"
				);
				l++;
				r=l+1;
			} else if(diff >k){
				l++;
				r++;
			} else{
				r++;
			}
		}
	}

}
