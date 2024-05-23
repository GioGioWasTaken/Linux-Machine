/*This Is the second part of mmn12. What follows below is the Box3D class.
  The Box3D class takes either nothing, another object of the same type,
  or a base coordinate of type Point3D, paired with a 3 ordered tuple of the
 type (height, width, length), as to represent a Box in a 3d coordinate space.
 * @author Iyar Segev
 * @version 1.0
  */

package src; // has to do with the way my files are set locally. The grader may ignore this.

import src.Point3D;

public class Box3D {
  Point3D Point3D_base;
  private int _length;
  private int _width;
  private int _height;

  // Constructors
  public Box3D() {
    this.Point3D_base = new Point3D(0.0, 0.0, 0.0);
    this._height = 1;
    this._width = 1;
    this._length = 1;
  }

  public Box3D(Point3D base, int height, int width, int length) {
    this.Point3D_base = base;
    this._height = height;
    this._width = width;
    this._length = length;

    // Note for the grader, this condition can be achieved more concisely using
    // the ternary operator ? but to prioritize readability of code:
    if (height <= 0) {
      this._height = 1;
    }

    if (width <= 0) {
      this._width = 1;
    }

    if (length <= 0) {
      this._length = 1;
    }
  }

  public Box3D(Box3D box) {
    this.Point3D_base = box.Point3D_base;
    this._width = box._width;
    this._height = box._height;
    this._length = box._length;
  }

  // Getter methods
  public int getHeight() { return _height; }

  public int getLength() { return _length; }

  public int getWidth() { return _width; }

  public Point3D getBase() { return Point3D_base; }

  // Setter methods

  public void setHeight(int num) {
    if (num > 0) {
      this._height = num;
    }
  }

  public void setLength(int num) {
    if (num > 0) {
      this._length = num;
    }
  }

  public void setWidth(int num) {
    if (num > 0) {
      this._width = num;
    }
  }

  public void setBase(Point3D p) { Point3D_base = p; }

  // Other methods

  // Returns a string representation of this Box3D object.

  public String toString() {
    return "The base point is " + this.getBase().toString() +
        ", length = " + this._length + ", width = " + this._width +
        ", height = " + this._height;
  }

  // determines if the boxes are equal
  public boolean equals(Box3D other) {
    if (this._height == other._height && this._width == other._width &&
        this._length == other._length) {
      Point3D base = this.getBase();
      Point3D other_base = other.getBase();
      if (base.getX() == other_base.getX() &&
          base.getY() == other_base.getY() &&
          base.getZ() == other_base.getZ()) {
        return true;
      }
      return false;
    }
    return false;
  }

  // moves the base of the box the method was called upon
  public Box3D move(double dx, double dy, double dz) {
    Point3D original_base = this.Point3D_base;
    Point3D base = new Point3D(original_base);
    base.move(dx, dy, dz); // reuse previously made function
    Box3D res = new Box3D(base, this._height, this._width, this._length);
    return res;
  }

  // yields the top right back point of the box the method was called on
  public Point3D getUpRightBackPoint() {
    Point3D base = this.Point3D_base;
    return new Point3D(base.getX() - this._length, base.getY() + this._width,
                       base.getZ() + this._height);
  }

  // gets the center of the box and represents it as a Point3D coordinate
  public Point3D getCenter() {
    Point3D base = this.Point3D_base;
    return new Point3D(base.getX() - (double)(this._length) / 2,
                       base.getY() + (double)(this._width) / 2,
                       base.getZ() + (double)(this._height) / 2);
    // I will not cast the box parameters to a double type, since it is not
    // demanded.
  }

  // checks the distance between 2 centers of 2 boxes
  public double distance(Box3D other) {
    Point3D base = this.getCenter();
    Point3D other_base = other.getCenter();
    return base.distance(other_base);
  }

  // returns the volume of a box
  public int getVolume() { return this._height * this._length * this._width; }

  // returns the surface area of a box
  public int getSurfaceArea() {
    // We have a pair of faces of each size.
    return this._height * this._width * 2 + this._length * this._width * 2 +
        this._length * this._height * 2;
  }

  // checks if a box's volume is completely bigger than another box's volume.
  public boolean isLargerCapacity(Box3D other) {
    return other.getVolume() < this.getVolume();
  }

  // checks if the parameter passed box can be contained within the caller box
  public boolean contains(Box3D other) {
    // a box B may be contained within box A, if and only if, box B's width
    // length and height, are smaller than A's.
    return (this._height > other._height) && (this._length > other._length) &&
        (this._width > other._width);
  }

  // checks if a box is completley above another box
  public boolean isAbove(Box3D other) {
    Point3D base = this.getBase();
    Point3D other_base = other.getBase();
    // for a box to be completely above another, we must also account for box
    // length:
    base.setZ(base.getZ() + this._length);
    other_base.setZ(other_base.getZ() + other._length);
    return base.isAbove(other_base);
  }

} // end of class Box3D
