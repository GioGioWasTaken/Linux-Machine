public class Q1{
	public static void main(String[] args) {
		
	}


	public static boolean maxMatrix(int[][] mat){
		return maxMatrix(mat,0,1);
	}

	public static boolean maxMatrix(int[][] mat, int x, int size){
		int middle = x+(size/2);
		if(isIdentity(mat,x,size) && middle== (mat.length-1)/2){

		}
	}


	public static boolean isIdentity(int[][] mat, int x, int size){
		return isIdentity(mat,x,size,0,0);
	}

	public static boolean isIdentity(int[][] mat, int x, int size, int row,
		int col) {
		if (row == x + size - 1 && col == x + size - 1) {
			if (mat[row][col] == 1) {
				return true;
			}
			return false;
		}
		if (col == x + size) {
			col = x;
			row++;
		}

		if (row == col) {
			if (mat[row][col] == 1) {
				return isIdentity(mat, x, size, row, col + 1);
			}
			return false;
		}
		if (mat[row][col] == 0) {
			return isIdentity(mat, x, size, row, col + 1);
		} else {
			return false;
		}
	}
}
