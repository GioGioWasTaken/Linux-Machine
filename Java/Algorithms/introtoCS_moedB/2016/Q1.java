import java.util.Arrays;

/**
 * Q1
 */
public class Q1 {
	public static void main(String[] args) {
		int[] arr = { 5,6,1,2,8};
		System.out.println(
			where(arr)
		);
	}

	public static int where(int[] arr){
		return where(arr,0);
	}
	public static int where(int[] arr, int index){
		if(arr.length == index){
			return -1;
		}
		int FirstPart = getSum(arr,0,index); //(x,y] range.
		int SecondPart = getSum(arr,index,arr.length);
		if(FirstPart==SecondPart){
			return index;
		}
		return where(arr,index+1);

	}
	public static int getSum(int[] arr, int index, int end){
		if(index == end){
			return 0;
		}
		return arr[index] + getSum(arr,index+1,end);
	}
}
