/**
 * Q1
 */
public class Q1 {
	public static void main(String[] args) {
		char[][] arr = {
		{'t', 'z', 'x', 'c', 'd'},
		{'s', 'h', 'a', 'z', 'x'},
		{'h', 'w', 'l', 'o', 'm'},
		{'o', 'r', 'n', 't', 'n'},
		{'a', 'b', 'r', 'i', 'n'}
		};
		findWord(arr,"shalom");
	}
	public static void findWord(char[][] arr, String word){
		int height = arr.length;
		int width = arr[0].length;
		int[][] store = new int[height][width];
		if(findWord(arr,word, 0, 0, 0, store)){
			System.out.println(
				"success"
			);
		} else{
			System.out.println(
				"Word not found"
			);
		}

	}
	public static boolean findWord(char[][] arr, String word, int row, int col, int index, int[][] store){
		boolean outofBounds = ( row < 0 || col < 0 || row > arr.length-1 || col > arr[0].length-1 || arr[row][col] !=0 || arr[row][col] == '#');

		// base case
		if(index == arr.length){
			System.out.println(
				"printArr called, success"
			);
			return true;
		}
		if(outofBounds){
			return false;
		}

		char current = word.charAt(index); // current character we need to check for.
		char temp = arr[row][col];
		arr[row][col] = '#'; // 0x00 is not a printable character

		if(current == temp){
			System.out.println(
				"A"
			);
			store[row][col] = index+1;
			boolean found = findWord(arr,word,row+1,col,index+1,store) || 
			findWord(arr,word,row-1,col,index+1,store) || 
			findWord(arr,word,row,col+1,index+1,store) || 
			findWord(arr,word,row,col-1,index+1,store);
			return found;
		} 
		
		arr[row][col] = temp;  // restore former char
		return findWord(arr,word,row,col+1,index,store);

	}

	

}
