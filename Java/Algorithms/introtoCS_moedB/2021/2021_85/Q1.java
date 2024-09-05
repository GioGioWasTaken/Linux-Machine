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
    return minPrice(mat, 0, 0 ,0 );
  }

  private static int minPrice(int[][]mat,int i,int j,int sum)
{
    if(i<0||j<0||i>mat.length-1||j>mat[i].length-1||mat[i][j]==-1){
      return Integer.MAX_VALUE;
    }
    if(j==mat[i].length-1){
      return sum+mat[i][j];
    }
    int move1 = minPrice(mat,i+1,j,sum+mat[i][j]);
    int move2 = minPrice(mat,i,j+1,sum);
    return Math.min(move1,move2);
  }
}


//  if we choose to go the the next station , set the parameter row =col , currSum + currValue
