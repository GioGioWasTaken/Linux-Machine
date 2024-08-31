/**
 * Q2
 */
public class Q2 {
	public static void main(String[] args) {
		int[] arr = {0,0,0,0};
		int[] arr2 = {0,0,0,0};
		minNumWithSum(arr, 14);
		PrintArray(arr);	
		minNumWithSum(arr, 11);
		PrintArray(arr);	

		minNumWithSum(arr2, 50);
		PrintArray(arr2);	
	}
	public static void minNumWithSum(int[]arr, int s){
		if(s > 9*arr.length || s < arr.length){
			return;
		}

		// o(n) time
		for (int i = 0; i < arr.length; i++) {
			arr[i]	 =1;
			s--;
		}
		int i =0;
		// o(n). in total O(2n) ~= O(n).
		while(s!=0){
			if(s>=8){
				arr[i] = 9;
				s-=8;
				i++;
			} else{
				arr[i]+=s;
				s = 0;
			}
		}

	}
	public static void PrintArray(int[] arr){
		System.out.print("{");
		for (int i = 0; i < arr.length; i++) {
			System.out.print("" + arr[i]+ ", ");
		}
		System.out.print("}\n");
	}
}
