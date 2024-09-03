/**
 * Q1
 */
public class Q1 {
	public static void main(String[] args) {
		
	}
	public static boolean checkPath(int[][] mat){
		return checkPath(mat, 0,0);
	}
	public static boolean checkPath(int[][] mat, int row, int col){
		// out of bounds or invalid square path
		if(row <0 || col <0 || row>mat.length-1 || mat[row][col] == 0){
			return false;
		}
		// column out of bounds
		if(col==mat.length){
			row++;
			col = 0;
		}
		mat[row][col] *=-1;
		// base case
		if(row==mat.length-1 && col==mat.length-1){
			if(checkMat(mat)){
				return true;
			} 
			return false;
		}
		mat[row][col] *=-1;

		// recursive step
		return checkPath(mat,row+1,col) || checkPath(mat,row,col+1); // can go either right or down
	}

	public static int countPathsThroughOnes(int[][] mat){
		if(checkPath(mat,0,0)){
			 checkPath(mat,row+1,col)? 1:0 + checkPath(mat,row,col+1)? 1:0;
		}
	}

	

}
