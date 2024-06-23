public class Q1 {
  public static void main(String[] args) {
    int[][] matrix = {
    {0, 15, 80, 90},
    {-1, 0, 40, 50},
    {-1, -1, 0, 70},
    {-1, -1, -1, 0}
    };
    System.out.println(minPrice(matrix));
  }
  public static int minPrice(int[][] mat) {
    return minPrice(mat,0, 0); }

  public static int minPrice(int[][] mat, int row, int col) {
    if (col > mat[1].length || row > col) {
      return Integer.MAX_VALUE;
    }
    if(col==mat[1].length-1){
      return mat[row][col];
    }
    int option1 = mat[row][col]+ minPrice(mat, row + 1, col + 1);
    int option2 = minPrice(mat, row, col + 1);
    return Math.min(option1, option2); 
  }

}


// notes for self:

// colLength = mat[0].length-1
// since we look at a cell and decide if we're buying or not we will pass 1.
// (look at first cell) option1 choose to move to the next cell and buy
// current cell. Since we bought current cell than the price to go to the
// next cell decreased, and can be found at mat[col][col+1] option2 choose
// to look at next without buying. If we are looking at the next, if we
// choose to move to the next cell we increment a sum check the minimum base
// case is if we are looking past the last cell mat[col][colLength] = price
// of bus from current station to last station.
