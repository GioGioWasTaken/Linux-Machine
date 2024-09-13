
/**
 * Q2
 */
public class Q2 {

	public static void main(String[] args) {
		
	}

	public static int findPeak(int[] arr){
		int length = arr.length ;
		int next;
		int previous;
		for(int i = 0; i<length; i++){
			int value = arr[i];
			if(i == length-1 ){
				previous = arr[i-1];
				next = Integer.MIN_VALUE;
			} else if( i ==0){
				next  = arr[i+1];
				previous = Integer.MIN_VALUE;
			} else{
				next  = arr[i+1];
				previous = arr[i-1];
			}
			if(value >= next && value >= previous){
				return value;
			}
		}
		return -1;


	}
}
