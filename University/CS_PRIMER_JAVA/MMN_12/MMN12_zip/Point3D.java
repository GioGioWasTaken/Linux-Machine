/*This Is the first part of mmn12. What follows below is the Point3D class.
  it takes either nothing, another object of the same type, or a  3 ordered tuple of the type 
  (height, width, length), as to represent a single coordinate in a 3D place.
 * @author Iyar Segev
 * @version 1.0
 */

package src; // has to do with the way my files are set locally. The grader may ignore this.

public class Point3D {
    private double x;
    private double y;
    private double z;

    // Constructors
    public Point3D() {
        this.x = 0.0;
        this.y = 0.0;
        this.z = 0.0;
    }

    public Point3D(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public Point3D(Point3D object){
        this.x = object.x;
        this.y = object.y;
        this.z = object.z;
    }

    // Getter methods
    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getZ() {
        return z;
    }

    // Setter methods
    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }

    public void setZ(double z) {
        this.z = z;
    }

  // returns a string representation of the 3D coordinate
    public String toString() {
        return "(" + this.x + "," + this.y + "," + this.z + ")";
    }

  // checks if 2 coordinates are identical
    public Boolean equals(Point3D other){
      if(this.x != other.x || this.y != other.y || this.z != other.z){
        return false;
      }
      return true;
    }
  // checks if a coordinate is above another, following the Z axis
    public Boolean isAbove(Point3D other){
      if(other.z < this.z){return true;}
      return false;
    }

    // As instructed in the document, isUnder, as well as many other methods, are to only use their opposing methods. 
    // Therefore, if they are equal, isUnder, and all other methods that use their possing methods in their definition, will return true.
  // opposite of isAbove
    public Boolean isUnder(Point3D other){
      if(!isAbove(other) && other.isAbove(this)){
        return true;
      }
      return false;
    }
  // checks if a coordinate is to the left following the Y axis
    public Boolean isLeft(Point3D other){
      if(other.y > this.y){
        return true;
      }
      return false;
    }

  // opposite of isLeft
    public Boolean isRight(Point3D other){
      if(!isLeft(other) && other.isLeft(this)){
        return true;
      }
      return false;
    }

  // same as the other 2, following x axis
    public Boolean isBehind(Point3D other){
      if(other.x > this.x){return true;}
      return false;
    }
  // opposite of isBehind
    public Boolean isInFrontOf(Point3D other){
      if(!isBehind(other) && other.isBehind(this)){
        return true;
      }
      return false;
    }

  // move the x, y , and z values dx, dy, and dz (respectively) distance away from their current position
    public void move (double dx, double dy, double dz){
      this.x+=dx;
      this.y+=dy;
      this.z+=dz;
    }
    
// Returns the distance between this point and other point p.

    public double distance(Point3D p){
      double inner_equation = (  Math.pow(this.x - p.x, 2) + Math.pow(this.y-p.y,2) + Math.pow(this.z-p.z, 2)  );
      double final_res = Math.pow(inner_equation, 0.5);
      return final_res;
    }

} // end of class Point3D
