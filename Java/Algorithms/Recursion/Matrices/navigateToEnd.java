public class navigateToEnd {
  public static void main(String[] args) {
    int[][] maze = {
        { 1, 1, 2, 3 },
        { 1, 2, 2, 2 },
        { 1, 1, 1, 1 },
    };
    int[][] maze2 = { { 1, 1, 1 }, { 1, 2, 2 }, { 1, 1, 1 } };
    int[][] maze3 = { { 1, 1, 1 }, { 1, 2, 2 }, { 1, 1, 1 } };
    int[][] maze4 = { { 1, 1, 1 }, { 2, 2, 2 }, { 1, 1, 1 } };
    System.out.println(navigateMaze(maze));
    System.out.println(navigateMaze(maze2));
    System.out.println(navigateMaze(maze3));
    System.out.println(navigateMaze(maze4));
  }

  public static boolean navigateMaze(int[][] matrix) {
    return navigateMaze(matrix, 0, 0);
  }

  public static boolean navigateMaze(int[][] matrix, int row, int col) {
    if (row == matrix.length - 1 && col == matrix[0].length - 1) {
      return true;
    }
    // don't explore a decision branch if the number doesn't appear
    // this way we don't need to pass it as a permeter, we just check the curent
    // row and col.
    if (row + 1 <= matrix.length - 1) {
      if (matrix[row + 1][col] == matrix[row][col]) {
        return navigateMaze(matrix, row + 1, col);
      }
    }
    if (col + 1 <= matrix[0].length - 1) {
      if (matrix[row][col + 1] == matrix[row][col]) {
        return navigateMaze(matrix, row, col + 1);
      }
    }
    return false;
  }

  public static int findMinPath(int[][] matrix, int row, int col, int val,
      int count) {
    if (col < 0 || row < 0 || row > matrix.length - 1 ||
        col > matrix[0].length - 1 || math[row][col] != val) {
      return Integer.MAX_VALUE;
    }
    if (matrix[row][col] == val) {
      return count + 1;
    }
    matrix[row][col] = 0;
    int a = findMinPath(matrix, row + 1, col, val, count);
    int b = findMinPath(matrix, row, col + 1, val, count);
    int c = findMinPath(matrix, row - 1, col, val, count);
    int d = findMinPath(matrix, row, col - 1, val, count);
    matrix[row][col] = val;
    int min = Math.min(a, Math.min(b, Math.min(c), Math.min(d)));
    return min;
  }

  public static int findLongestWorm(int[][] matrix, int row, int col, int val,
      int length) {
    if (col < 0 || row < 0 || row > matrix.length - 1 ||
        col > matrix[0].length - 1 || math[row][col] < val) {
      return Integer.MIN_VALUE;
    }
    if (matrix[row][col] <= val) {
      return count + 1;
    }
    matrix[row][col] = 0;
    int a = findLongestWorm(matrix, row + 1, col, val, length);
    int b = findLongestWorm(matrix, row, col + 1, val, length);
    int c = findLongestWorm(matrix, row - 1, col, val, length);
    int d = findLongestWorm(matrix, row, col - 1, val, length);
    matrix[row][col] = val;
    int max = Math.max(a, Math.max(b, Math.max(c), Math.max(d)));
    return max;
  }
}
