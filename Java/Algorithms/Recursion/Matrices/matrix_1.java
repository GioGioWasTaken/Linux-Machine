public class matrix_1 {
  public static void main(String[] args) {
  }

  public static int[] findVal(int[][] matrix, int value) {
    return findVal(0, 0, matrix, value);
  }

  public static int[] findVal(int row, int col, int[][] matrix, int value) {
    if (row == matrix.length && col == matrix[0].length) {
      return null; // value not found
    }
    if (matrix[row][col] == value) {
      return new int[] { row, col };
    }
    int nextCol = col + 1;
    int nextRow = row;
    if (nextCol > matrix[0].length) {
      nextRow++;
      nextCol = 0;
    }
    return findVal(nextRow, nextCol, matrix, value);
  }

  public static int findMaxVal(int[][] matrix) {
    return findMaxVal(row, col, matrix);
  }

  public static int findMaxVal(int row, int col, int[][] matrix) {
    if (row == matrix.length && col == matrix[0].length) {
      return matrix[col][row];
    }
    int current = matrix[col][row];
    int nextCol = col + 1;
    int nextRow = row;
    if (nextCol > matrix[0].length) {
      nextRow++;
      nextCol = 0;
    }
    return Math.max(current, findMaxVal(nextRow, nextCol, matrix));
  }

  public static int findMinVal(int[][] matrix) {
    return findMinVal(row, col, matrix);
  }

  public static int findMinVal(int row, int col, int[][] matrix) {
    if (row == matrix.length && col == matrix[0].length) {
      return matrix[col][row];
    }
    int current = matrix[col][row];
    int nextCol = col + 1;
    int nextRow = row;
    if (nextCol > matrix[0].length) {
      nextRow++;
      nextCol = 0;
    }
    return Math.min(current, findMaxVal(nextRow, nextCol, matrix));
  }
}
