/**
 * allPossiblePaths
 */
public class allPossiblePaths {
  public static void main(String[] args) {
    System.out.println(FindallPossiblePaths(4,4));;
  }
  public static int FindallPossiblePaths(int n, int m){
    if(n==0 ||m==0){
      return 0;
    }
    if(n==1 || m ==1){
      return 1;
    }
    // allPossiblePaths(n,m) = allpossiblePaths(n,m-1) + allPossiblePaths(n-1, m);
    return FindallPossiblePaths(n,m-1) + FindallPossiblePaths(n-1, m);
  }
}
