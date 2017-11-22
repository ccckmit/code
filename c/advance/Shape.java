class Shape {
  double area() { return 0.0; }
  
  public static void main(String[] argv) {
    Shape s[] = { new Shape(), new Circle(3.0) };
    for (int i=0; i<s.length; i++)
      System.out.println("area()="+s[i].area());
  }
}

class Circle extends Shape {
  public double r;
  Circle(double pr) { r = pr; }
  double area() { return 3.14*r*r; }
}
 