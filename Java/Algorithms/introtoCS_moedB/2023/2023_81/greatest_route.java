// wongi question
/**
 * greatest_route
 */
public class greatest_route {

public static int greatestRoute(int[][] matrix) {
        int[][] movements_left = new int[matrix.length][matrix[0].length];

        // Copy matrix values to movements_left matrix
		// can be implemented recursively, but waste of time
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) {
                movements_left[i][j] = matrix[i][j];
            }
        }

        System.out.println("All routes:");
        int maxRoute = greatestRoute(matrix, movements_left, 0, 0, "");
        System.out.println("Max route value: " + maxRoute);

        return maxRoute;
    }

    public static int greatestRoute(int[][] matrix, int[][] movements_left, int row, int col, String path) {
        // Out of bounds or invalid position
        if (row < 0 || col < 0 || row >= matrix.length || col >= matrix[0].length) {
            return Integer.MIN_VALUE;
        }

        // No more movements allowed from this cell
        if (movements_left[row][col] == 0) {
            return Integer.MIN_VALUE;
        }

        // Include current position in the path
        path += "(" + row + "," + col + ") -> ";

        // Check if we've reached the bottom-right corner
        if (row == matrix.length - 1 && col == matrix[0].length - 1) {
            System.out.println(path + "END"); // can be replaced with sum local var
            return matrix[row][col];
        }

        // Decrease the movement count for the current cell
        movements_left[row][col]--;

        // Explore all possible directions: up, down, right, left
        int up = greatestRoute(matrix, movements_left, row - 1, col, path);
        int down = greatestRoute(matrix, movements_left, row + 1, col, path);
        int right = greatestRoute(matrix, movements_left, row, col + 1, path);
        int left = greatestRoute(matrix, movements_left, row, col - 1, path);

        // Restore the movement count after exploration for backtracking
        movements_left[row][col]++;

        // Find the maximum path sum from the current position
        int maxRoute = Math.max(Math.max(up, down), Math.max(right, left));

        // If no valid route, return minimum value
        if (maxRoute == Integer.MIN_VALUE) {
            return Integer.MIN_VALUE;
        }
        // Add the current cell's value to the maxRoute and return
        return matrix[row][col] + maxRoute;
    }
	
}
