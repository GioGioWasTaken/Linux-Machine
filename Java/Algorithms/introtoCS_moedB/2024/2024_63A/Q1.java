/**
 * Q1
 */
public class Q1 {
	public static void main(String[] args) {
		int[] a = {-1, 2, 4, 5, 7 };
		int [] b = {-1,1,5,9,16};
		System.out.println(
			find(b,-1)
		);
	}

	public static int get(int[] b, int k ){
		if(k==0){
			return b[k];
		} 
		return b[k]-b[k-1];
	}
	public static int find(int[] b, int x){
		int l = 0;
		int r = b.length -1;
		while(l <=r){
			int m = (l +r ) /2;
			int value =  get(b, m);
			if(value == x){
				System.out.println("value found");
				return m;
			} else if(value < x){
				l = m+1;
			} else{
				r = m-1;
			}
		}
		System.out.println(
			"Value not found."
		);
		return -1;

	}
}
