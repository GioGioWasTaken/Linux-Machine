public class recursion_5 {

  public int triangle(int rows) {
    if (rows == 0)
      return 0;
    else {
      return triangle(rows - 1) + rows;
    }
  }
}