/**
 * Q2
 */
public class Q2 {
	public static void main(String[] args) {
		int[] arr = {10,3,40,20,50,80,70};
		System.out.println(
			findAlmostSorted(arr,50)
		);
	}
	public static int findAlmostSorted(int[]arr, int num){
		int l = 0;
		int r = arr.length -1;
		while( l <=r){
			int m = (l+r) /2;
			int leftNeighbour = m-1;
			int rightNeighbour =  m+1;
			if(arr[m] == num){
				return m;
			}
			if(arr[leftNeighbour] > arr[m]){
				// treat the left neighbour as the correct middle
				if(arr[leftNeighbour] == num){
					return leftNeighbour;
				}
				else if(arr[leftNeighbour] > num){
					r = m-1;
				} else{
					l = m+1;
				}
			} else if(arr[rightNeighbour] < arr[m]){
				// treat the right neighbour as the correct middle

				if(arr[rightNeighbour] == num){
					return rightNeighbour;
				}
				else if(arr[rightNeighbour] > num){
					r = m-1;
				} else{
					l = m+1;
				}
			} else{
				// m is the correct middle (for all purposes). We already checked if m was equal at the start, so what remains is:
				if(arr[leftNeighbour] > num){
					r = m-1;
				} else{
					l = m+1;
				}

			}
		}

		return -1;
	}
}
