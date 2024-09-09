public class findmaxPath {
  public static void main(String[] args) {
  }

  public static int maxPath(int[][] mat) {
    return maxPath(mat, 0, 0, 0);
  }

  public static int maxPath(int[][] mat, int row, int col, int sum) {
    if (row < 0 || col < 0) {
      // invalid input
      return Integer.MIN_VALUE;
    }
    if (row == mat.length - 1 || col == mat[0].length - 1) {
      return sum;
    }
    int Tens = mat[row][col] / 10;
    int Ones = mat[row][col] % 10;

    int currentVal = mat[row][col];
    boolean move1isValid = (row + Tens < mat.length && col + Ones < mat[0].length);
    boolean move2isValid = (row + Ones < mat.length && col + Tens < mat[0].length);
    int Option1 = Integer.MIN_VALUE;
    int Option2 = Integer.MIN_VALUE;
    if (move1isValid) {
      Option1 = maxPath(mat, row + Tens, col + Ones, sum + mat[row][col]);
    }
    if (move2isValid) {
      Option2 = maxPath(mat, row + Ones, col + Tens, sum + mat[row][col]);
    }
    int max = Math.max(Option1, Option2);
    return max;
  }
}
