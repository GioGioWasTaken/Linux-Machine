 /*  navigateToEnd of a maze, a valid path is a path made entirely of 1s  */
class navigateToEnd {
  public static void main(String[] args) {
    int[][] maze = {
    { 1, 1, 2, 3 },
    { 1, 2, 2, 2 },
    { 1, 1, 1, 1 },
    };
     int[][] maze2= {
     {
         1,   0,   0,   0,   0
       },
     {
         1,   0,    1,    1,    1
       },
     {
         1,    1,    1,    0,    1
       },
     {0,   0,   0,   0,   1},
     {
         0,   0,   0,   0,   1
       }
     };
    if(navigateMaze(maze2)){
      System.out.println("maze is navigatable\n");
    } else{
      System.out.println("maze is not navigatable.\n");
    }
  }

  public static boolean navigateMaze(int[][] matrix){
    return navigateMaze(matrix,0,0);
  }


  public static boolean navigateMaze(int[][] matrix, int row, int col){
    if(row==matrix.length-1 && col == matrix[0].length-1){
      return matrix[row][col] == 1;
    } 
    if(isSafe(matrix,row,col)){
      matrix[row][col] =0;
      boolean found = navigateMaze(matrix,row+1,col) || navigateMaze(matrix,row-1,col) || navigateMaze(matrix,row,col+1) || navigateMaze(matrix,row,col-1);
      matrix[row][col] =1; // if it's not 1 we don't go there in the first place.
      return found;
    } else{
      return false;
    }
  }


  public static boolean isSafe(int[][] matrix, int row, int col){
    int row_max =  matrix.length;
    int col_max = matrix[0].length;
    return (row<row_max && row >=0 && col>=0 && col<col_max &&matrix[row][col]==1);
  }

}
