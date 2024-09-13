/**
 * Q2
 */
public class Q2 {
	public static void main(String[] args) {
		int[] arr = {5,8,2,4,17,-2};
		System.out.println(
			findMaxDiff(arr)
		);
	}
	public static int findMaxDiff(int[] arr){
		if(arr==null || arr.length == 0){
			return 0;
		}
		int l = 0;
		int LastElement = arr[arr.length-1];
		int m = 0;
		int currentMin = Integer.MAX_VALUE;
		while(l <=arr.length-2){
			if(arr[l] < currentMin){
				currentMin = arr[l];
			} else{
				if(arr[l]- currentMin > m){
					m =  (arr[l]- currentMin);
				}
			}

			if(LastElement- currentMin > m){
				m =  LastElement-currentMin;
			} else if(LastElement - arr[l] > m){
				m =  LastElement-arr[l];
			}
			l++;
		}

		return m;

	}
}
