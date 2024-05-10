/*This Is the first part of mmn11. What follows below is the triangle class.
 The triangle class takes parameteres for 3 triangle sides and calculates its
 area and perimeter Done by Iyar segev*/

import java.util.Scanner;

public class Triangle {
  public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    System.out.println("This program calculates the area "
                       + "and the perimeter of a given triangle. ");
    System.out.println("Please enter the three lengths"
                       + " of the triangle's sides");
    int a = scan.nextInt();
    int b = scan.nextInt();
    int c = scan.nextInt();
    // here we start calculating the area.
    int p = (a + b + c) / 2;
    int expr = p * (p - a) * (p - b) * (p - c);
    double s = 0;
    if (expr <= 0 || a <= 0 || b <= 0 || c <= 0) {
      s = -1; // this is both the output, and a flag we can use to check if
              // the input makes sense.
    } else {
      s = Math.pow(expr, 0.5);
    }

    // start calculating the perimeter.
    int perimeter = 0;
    if (a <= 0 || b <= 0 || c <= 0) {
      perimeter = -1;
    } else {
      perimeter = a + b + c; // same logic as s.
    }

    if (s == -1 || perimeter == -1) {
      System.out.println("The lengths of the triangle sides are: " + a + ", " +
                         b + ", " + c);
      System.out.println("The given three sides don't represent a triangle");
      // one of our flags was triggered. this triangle is invalid.
    } else {
      System.out.println("The lengths of the triangle sides are: " + a + ", " +
                         b + ", " + c);
      System.out.println("The perimeter of the triangle is: " + perimeter);
      System.out.println("The area of the triangle is: " + s);
    }

    // as requested, all done within main with no helper functions.
    // end of method main
  }
}
// end of class Triangle
