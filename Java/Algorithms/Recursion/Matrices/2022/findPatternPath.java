
public class findPatternPath {
  public static int MaxPath(char[][] mat, String pattern) {
    int globalMax = 0;
    int rowAmount = mat.length;
    int colAmount = mat[0].length;
    for (int i = 0; i < rowAmount; i++) {
      for (int j = 0; j < colAmount; j++) {
        int localMax = lengthPath(mat, i, j, pattern);
        if (localMax > globalMax) {
          globalMax = localMax;
        }
      }
    }
    return globalMax;
  }

  public static int lengthPath(char[][] mat, int row, int col, String pattern) {
    boolean[][] visited = new boolean[mat.length][mat[0].length];
    return lengthPath(mat, row, col, pattern, visited);
  }

  public static boolean isInPattern(String pattern, char chara) {
    for (int i = 0; i < pattern.length(); i++) {
      if (chara == pattern.charAt(i)) {
        return true;
      }
    }
    return false;
  }

  public static int lengthPath(char[][] mat, int row, int col, String pattern,
      boolean[][] visited, int length) {
    if (row < 0 || col < 0 || row >= mat.length || col >= mat[0].length) {
      return 0;
    }
    if (visited[row][col] || !isInPattern(pattern, mat[row][col])) {
      return 0;
    }

    visited[row][col] = true;

    int right = 1 + lengthPath(mat, row, col + 1, pattern, visited, length);
    int left = 1 + lengthPath(mat, row, col - 1, pattern, visited, length);
    int up = 1 + lengthPath(mat, row - 1, col, pattern, visited, length);
    int down = 1 + lengthPath(mat, row + 1, col, pattern, visited, length);

    visited[row][col] = false;

    return max(right, left, up, down);
  }

  // Helper function to find the maximum of multiple integers
  public static int max(int... numbers) {
    int maxValue = Integer.MIN_VALUE;
    for (int num : numbers) {
      maxValue = Math.max(maxValue, num);
    }
    return maxValue;
  }

  public static void main(String[] args) {
    char[][] mat = { { 'a', 'd', 'e', 's', '@', 'a' },
        { '3', 'a', 'z', 'a', 's', 'a' },
        { '?', 'c', 'b', 'b', 'c', 'd' },
        { 'b', 'c', 'a', '8', 'b', 'b' },
        { 'c', '2', 'x', '+', 'b', 'c' } };
    String pattern = "abc";
    System.out.println(MaxPath(mat, pattern)); // Example usage
  }
}
