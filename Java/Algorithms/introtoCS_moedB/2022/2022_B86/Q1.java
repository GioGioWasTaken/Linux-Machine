public class Q1{
	public static void main(String[] args) {
		int[][] mat = {
		{12,22,23,54,11},
		{43,35,21,20,30},
		{34,23,43,22,30},
		{25,31,2,20,34},
		{10,22,10,11,10},
		{40,13,3,1,23}
		};
		System.out.println(
			maxPath(mat)
		);
	}
	public static int maxPath(int[][] mat){
		return maxPath(mat,0,0, 0);
	}

	public static int maxPath(int[][] mat, int row, int col, int currSum){
		// out of bounds
		if(row > mat.length -1  || col > mat[0].length-1 || row< 0 || col <0 ){
			return Integer.MIN_VALUE;
		} 
		// base case
		if(row == mat.length-1 && col == mat[0].length -1){
			return currSum + mat[row][col];
		}

		int CurrValue =mat[row][col];
		int option_1 = CurrValue % 10;
		int option_2 = CurrValue / 10;

		// recursive step
		int move1 = maxPath(mat,row+option_1,col +option_2, currSum + CurrValue);
		int move2 = maxPath(mat,row+option_2,col +option_1, currSum + CurrValue);	
		return Math.max(move1,move2);
	}
}
