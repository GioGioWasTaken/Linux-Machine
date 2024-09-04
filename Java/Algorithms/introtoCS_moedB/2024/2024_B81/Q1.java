/**
 * Q1
 */
public class Q1 {
	public static void main(String[] args) {
		int[][] C = {
			{4,1,9,3,25},
			{24,23,2,21,5},
			{13,12,15,16,14},
			{17,11,18,19,20},
			{10,2,8,7,6}
		};

		int[][] D = {
			{4,1,9,3,25},
			{24,23,2,21,5},
			{13,12,15,16,22},
			{17,11,18,19,20},
			{10,14,8,7,6}
		};
		int[][] A= {
			{1,2},
			{3,4}
		};
		int[][] B= {
			{1,3},
			{4,2}
		};
		System.out.println(
			minOfMax(C)
		);
		System.out.println(
			minOfMax(D)
		);
	}
	public static int minOfMax(int m[][]){
		return minOfMax(m,0,0,Integer.MIN_VALUE);
	}

	
	public static int minOfMax(int m[][], int row, int col, int currMax) {
		// Out of range or visited
		if (row < 0 || row >= m.length || col < 0 || col >= m[0].length || m[row][col] == -1) {
			return Integer.MAX_VALUE;
		}

		// Update current maximum
		currMax = Math.max(currMax, m[row][col]);

		// If we reached the bottom-right corner
		if (row == m.length - 1 && col == m[0].length - 1) {
			return currMax;
		}

		int value = m[row][col];
		m[row][col] = -1; // Mark the cell as visited

		// Recursive calls
		int down = minOfMax(m, row + 1, col, currMax);
		int right = minOfMax(m, row, col + 1, currMax);
		int up = minOfMax(m, row - 1, col, currMax);
		int left = minOfMax(m, row, col - 1, currMax);

		m[row][col] = value; // Restore the cell value, preserve state

		// Return the minimum of the maximum values
		return Math.min(down, Math.min(right, Math.min(up, left)));
	}

}
