/**
 * true_regions
 */
public class true_regions {
		
	public static void main(String[] args)	{
		int[][] matrix = {
		{0, 0, 0, 0, 1},
		{0, 1, 1, 1, 0},
		{0, 0, 1, 1, 0},
		{1, 0, 0, 0, 0},
		{1, 1, 0, 0, 0}
		};
		System.out.println(cntTrueRegion(matrix));
		
	}
	public static int cntTrueRegion(int[][] matrix){
		return cntTrueRegion(matrix, 0,0);
	}
	public static int cntTrueRegion(int[][] matrix, int row, int col){
		boolean outofBounds=(row == matrix.length -1|| col ==matrix[0].length -1);
		int nextRow = row;
		int nextCol = col+1;
		if(nextCol == matrix[0].length){
			nextCol = 0;
			nextRow++;
			outofBounds=(row == matrix.length || col ==matrix[0].length);
		}
		if(outofBounds){ // base case, reached end.
			return 0;
		}
		if(matrix[row][col] == 1) {
			if(matrix[row+1][col] ==1 || matrix[row][col-1] ==1 ){
				return cntTrueRegion(matrix,nextRow,nextCol); // true region already detected earlier.
				// observe that we don't check the right and downwards. only upwards and to the left(already observed true regions).
			}
			return 1 + cntTrueRegion(matrix,nextRow,nextCol);
		}
		return cntTrueRegion(matrix,nextRow,nextCol);
	}
	
}

