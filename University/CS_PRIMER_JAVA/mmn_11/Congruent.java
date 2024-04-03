/*This Is the second part of mmn11. What follows below is the Congruent class.
  The congruent class takes 6 pairs of coordinates and checks if the triangles
 yieled by said coordinates, are congruent. Done by Iyar segev*/

import java.util.Scanner;

public class Congruent {
  public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    // First triangle: Input
    System.out.println("Please enter the coordinates of the 3 "
                       + "vertices of the first triangle:");
    System.out.println("Enter the first vertex (2 real numbers)");
    double x11 = scan.nextDouble();
    double y11 = scan.nextDouble();
    System.out.println("Enter the second vertex (2 real numbers)");
    double x12 = scan.nextDouble();
    double y12 = scan.nextDouble();
    System.out.println("Enter the third vertex (2 real numbers)");
    double x13 = scan.nextDouble();
    double y13 = scan.nextDouble();

    // Second triangle: Input
    System.out.println("Please enter the coordinates of the 3 "
                       + "vertices of the second triangle:");

    double x21 = scan.nextDouble();
    double y21 = scan.nextDouble();
    System.out.println("Enter the second vertex (2 real numbers)");
    double x22 = scan.nextDouble();
    double y22 = scan.nextDouble();
    System.out.println("Enter the third vertex (2 real numbers)");
    double x23 = scan.nextDouble();
    double y23 = scan.nextDouble();

    // First triangle: Calculation
    // We shall use the distance formula to calculate the distance between 2
    // cartesian (thanks descartes!) coordinate pairs.
    // 0.5 is the square root part of the formula. 2 is the power of the
    // expressions inside it.
    double a1 =
        Math.pow((Math.pow((x12 - x11), 2) + Math.pow((y12 - y11), 2)), 0.5);
    double b1 =
        Math.pow((Math.pow((x13 - x12), 2) + Math.pow((y13 - y12), 2)), 0.5);
    double c1 =
        Math.pow((Math.pow((x13 - x11), 2) + Math.pow((y13 - y11), 2)), 0.5);
    // First triangle: Output
    System.out.println("The first triangle is: (" + x11 + ", " + y11 + ") "
                       + "(" + x12 + ", " + y12 + ") "
                       + "(" + x13 + ", " + y13 + ").");
    System.out.println("Its lenghts are " + a1 + ", " + b1 + ", " + c1 + ".");

    // Second Triangle: Calculation
    double a2 =
        Math.pow((Math.pow((x22 - x21), 2) + Math.pow((y22 - y21), 2)), 0.5);
    double b2 =
        Math.pow((Math.pow((x23 - x22), 2) + Math.pow((y23 - y22), 2)), 0.5);
    double c2 =
        Math.pow((Math.pow((x23 - x21), 2) + Math.pow((y23 - y21), 2)), 0.5);
    // Second triangle: Output
    System.out.println("The second triangle is: (" + x21 + ", " + y21 + ") "
                       + "(" + x22 + ", " + y22 + ") "
                       + "(" + x23 + ", " + y23 + ").");
    System.out.println("Its lenghts are " + a2 + ", " + b2 + ", " + c2 + ".");

    // Now we must check if the triangles are congruent.
    boolean congruent = ((a1 == a2 && b1 == b2 && c1 == c2) ||
                         (a1 == b2 && b1 == c2 && c1 == a2) ||
                         (a1 == c2 && b1 == a2 && c1 == b2) ||
                         (a1 == b2 && b1 == a2 && c1 == c2) ||
                         (a1 == c2 && b1 == b2 && c1 == a2) ||
                         (a1 == a2 && b1 == c2 && c1 == b2));
    // Print the result
    if (congruent) {
      System.out.println("The triangles are congruent.");
    } else {
      System.out.println("The triangles are not congruent.");
    }
    // As required, no helper functions were used.
  }
}
