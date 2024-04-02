/*This Is the first part of mmn11. What follows below is the triangle class.
 The triangle class takes parameteres for 3 triangle sides and calculates its area and perimeter 
 Done by Iyar segev*/

import java.util.Scanner;

public class Triangle
{
  public static void main (String [] args)
  {
  Scanner scan = new Scanner (System.in);
  System.out.println ("This program calculates the area "
  + "and the perimeter of a given triangle. ");
  System.out.println ("Please enter the three lengths"
  + " of the triangle's sides");
  int a = scan.nextInt();
  int b = scan.nextInt();
  int c = scan.nextInt();
  if(calcArea(a,b,c)==-1 || CalcPerimeter(a,b,c)==-1){
    System.out.println("The given three sides don't represent a triangle");
  }
  else{
    System.out.println("The lengths of the triangle sides are:" +a +", " + b + ", " + c);
    double area = calcArea(a,b,c);
    int perimeter = CalcPerimeter(a,b,c);
    System.out.println("The perimeter of the triangle is: " + perimeter);
    System.out.println("The area of the triangle is: " + area);
  }

  }


  private static double calcArea(int a, int b, int c){
    int p = (a + b + c)/2;
    int expr = p *(p-a)*(p-b)*(p-c);
    if(expr<=0 || a<=0 || b<=0 || c<=0){
      return -1;
    }
    else{
      double s = Math.pow(expr,0.5);
      return s;
    }
  }
  private static int CalcPerimeter(int a, int b, int c){
    if(a<=0 || b<=0 || c<=0){
      return -1;
    }
    return a + b + c;
  }
  // end of method main
} 
//end of class Triangle
