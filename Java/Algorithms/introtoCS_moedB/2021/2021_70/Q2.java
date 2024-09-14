/**
 * Q2
 */
public class Q2 {
	public static int getMedian(int[] arr1, int[]arr2){
		int median1 = 0;
		int median2= 0;
		int p1 = 0;
		int p2 = 0;
		
		int length = arr1.length;
		while(p1 + p2 <=length+1){
			// remember edgecase where one array is entirely smaller then the other: out of bounds check
			if(p1+p2== length){
				median1 = Math.min(arr1[p1],arr2[p2]);
			}

			if(p1+p2== length+1){
				median2 = Math.min(arr1[p1],arr2[p2]);
				break;
			}
			if(arr1[p1] >= arr2[p2]){
				p2++;
			} else{
				p1++;
			}
		}
		return (median1 + median2) /2;
	}

}
