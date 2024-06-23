public class Q2 {
  public static void main(String[] args) {

    int mat[][] = { { 1, 2, 3, 2, 0, 1, 2 }, { 0, 1, 0, 0, 0, 3, 0 },
        { 0, 0, 1, 0, 0, 0, 0 }, { 5, 0, 0, 1, 0, 0, 0 },
        { 7, 0, 0, 0, 1, 0, 0 }, { 8, 0, 0, 0, 0, 1, 0 },
        { 1, 0, 0, 0, 0, 0, 0 } };

    boolean isTrue, isFalse;

    isTrue = isIdentity(mat, 0, 1);
    System.out.println("true: " + isTrue);
    isTrue = isIdentity(mat, 1, 1);
    System.out.println("true: " + isTrue);
    isTrue = isIdentity(mat, 1, 2);
    System.out.println("true: " + isTrue);
    isTrue = isIdentity(mat, 1, 3);
    System.out.println("true: " + isTrue);
    isTrue = isIdentity(mat, 1, 4);
    System.out.println("true: " + isTrue);
    isTrue = isIdentity(mat, 4, 1);
    System.out.println("true: " + isTrue);
    isTrue = isIdentity(mat, 4, 2);
    System.out.println("true: " + isTrue);
    isFalse = isIdentity(mat, 4, 3);
    System.out.println("false: " + isFalse);
  }

  public static boolean isIdentity(int[][] mat, int x, int size) {
    return isIdentity(mat, x, size, x, x);
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

  public static int maxMatrix(int[][] mat) {
    return maxMatrix(mat, 0, 1);
  }

  public static int maxMatrix(int[][] mat, int currX, int currSize) {
    int maximumX = (mat.length - 1) / 2;
    if (currX == maximumX) {
      if (isIdentity(mat, currX, currSize)) {
        return currSize;
      }
    }
    return maxMatrix(mat, currX + 1, currSize + 2);
  }
}
