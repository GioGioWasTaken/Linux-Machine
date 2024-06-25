/**
 * Q2
 */
public class Q2 {
	public static void main(String[] args) {
	int[] arr =  {1,-3,6,2,0,15};
	int[] arr2  = {1 , 1 , 1 , 1};
	int[] arr3  = {1 , 2, 3 , 4};
	int[] arr4  = {5, -1, 3, 1 , 0, -2 , 2};
	int[] arr5  = {7, 8, 9, 11, 12, 14};
	System.out.println(FindFirstMissing(arr));	
	System.out.println(FindFirstMissing(arr2));	
	System.out.println(FindFirstMissing(arr3));	
	System.out.println(FindFirstMissing(arr4));	
	System.out.println(FindFirstMissing(arr5));	
	}
	public static int FindFirstMissing(int[] arr ){
		int SmallestNotFound = 1;
		for (int i = 0; i < arr.length; i++) {
			if(arr[i] == SmallestNotFound){
				SmallestNotFound++;
			}
		}
		

		return SmallestNotFound;
	}
}
