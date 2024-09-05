public class Q1{
	public static void main(String[] args) {
		/* approach:*/
		/* 1. calculate the max path sum from the last index to the first index in the matrix in a helper func
		* 2. let that value be called z. return -(z-1)
		* */
	int mat[][] = {
			{ -2,-3,3 },
			{ -5,-10,1 },
			{ 10,30,-5 } 
		};
		System.out.println(
			minPoints(mat)
		);
	}
	public static int minPoints(int[][] m) {
		if(m[m.length-1][m[0].length-1] <= 0){
			return minPointsHelper(m, m.length-1, m[0].length-1, 0, 1);
		} else{

			return minPointsHelper(m, m.length-1, m[0].length-1, 0, 0);
		}
	}



	
	public static int minPointsHelper(int[][] m, int row, int col, int sum, int res) {
		// out of bounds
		if (row < 0 || col < 0) {
			return Integer.MAX_VALUE; // Return a large value to avoid considering out-of-bounds paths
		}

		// base case: top-left corner
		if (row == 0 && col == 0) {
			sum += m[row][col];
			if (sum <= 0) {
				res += Math.abs(sum);
			}
			return res;
		}

		int val = m[row][col];
		if (sum + val <= 0) {
			res += Math.abs(sum + val);
		}

		// Recurse to find the minimum `res` between the two possible paths
		return Math.min(
			minPointsHelper(m, row - 1, col, sum + val, res),
			minPointsHelper(m, row, col - 1, sum + val, res)
		);
	}

}

