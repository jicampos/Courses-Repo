/**
 * <h1>Quadratic Equation</h1>
 * The program represents the quadratic equation expression
 * 
 * @author Javier Campos
 * @version 1.0
 * @since 2017-09-09
 */
public class QuadraticExpression implements Cloneable{
  
  private double a;
  private double b;
  private double c;
   
  /**
   * The default constructor is used to initalize all instance variables in the 
   * class to zero. 
   */ 
  public QuadraticExpression(){
    a = 0;
    b = 0;
    c = 0;
  }
  
  /**
   * The constructor will initalize all coefficients passed 
   * through the parameters.
   * @param a The first double parameter will initalize coefficient a.
   * @param b The second double parameter will initalize coefficient b.
   * @param c The third double parameter will initalize coefficient c.
   */
  QuadraticExpression(double a, double b, double c){
    this.a = a;
    this.b = b;
    this.c = c;
  }
  
  /**
   * Prints the quadratic equation as a string.
   * @return A string representing the quadratic equation.
   */
  public String toString(){
    if(a == 0){
      if(b == 0 && c == 0)
        return "0";
      else if(b == 0)
        return "+ " + c;
      else if(c == 0)
        return "+ " +  b;
      else 
        return "+ " + b + "x + " + c;
    }
    else if(b == 0){
      if(c == 0)
        return a + "x^2 ";
      else
        return a + "x^2 + " + c; 
    }
    else if(c == 0)
      return a + "x^2 + " + b + "x";
    else 
      return a + "x^2 + " + b + "x + " + c;
  }
  
  /**
   * Evaulates the quadratic equation.
   * @param x A double representing the variable x of the equation.
   * @return Will return the value of the evaulated equation.
   */
  public double evaluate(double x){
    return (a*x*x + b*x + c);
  }
  
  /**
   * Sets a new value of the coefficient a of the equation. 
   * @param newA A double to set the new value of a.
   */
  public void setA(double newA){
    a = newA;
  }
  
  /**
   * Sets a new value for the coefficient b of the equation.
   * @param newB A double to set the new value of b.
   */
  public void setB(double newB){
    b = newB;
  }
  
  /**
   * Sets a new value for the coefficient c of the equation. 
   * @param newC A double to set the new value of c.
   */
  public void setC(double newC){
    c = newC;
  }
  
  /**
   * The method will add two quadratic equations.
   * @param q1 The first object of QuadraticExpression.
   * @param q2 The second object of QuadraticExpression.
   * @return A new expression that is the sum of q1 and q2.
   */
  public static QuadraticExpression sum(QuadraticExpression q1, QuadraticExpression q2){
  
    double newA, newB, newC;
    
    newA = q1.a + q2.a;
    newB = q1.b + q2.b;
    newC = q1.c + q2.c;
    
    QuadraticExpression answer = new QuadraticExpression(newA, newB, newC);
    
    return answer;
  } 
  
  /**
   * The method will multiply all terms in the equation by a scalar.
   * @param r A double scalar to multiplty to the equation.
   * @param q The QuadraticExpression to multiply.
   * @return A new expression representing r * q.
   */
  public static QuadraticExpression scale(double r, QuadraticExpression q){
    
    double newA, newB, newC;
    
    newA = q.a * r;
    newB = q.b * r;
    newC = q.c * r;
    
    QuadraticExpression answer = new QuadraticExpression(newA, newB, newC);
    
    return answer;
    }
  
  /**
   * The method will determine the number of roots 
   * in a quadratic equation.
   * @return An integer indicating the number of roots.
   */
  public int numberOfRoots(){
    double d = b*b - 4*a*c;
    if(a == 0 && b == 0 && c == 0)
         return 3;
    else if (a == 0 && b == 0)
      return 0;
    else if(a == 0)
      return 1;
    else if(d == 0)
      return 1;
    else if( d > 0)
      return 2;
    else //if(d < 0)
    return 0;  
  }
  
  /** 
   * The method will add a quadratic equations to 
   * the calling expression object.
   * @param q A QuadraticExpression object. 
   */
  public void add(QuadraticExpression q){
   
    this.a += q.a;
    this.b += q.b;
    this.c += q.c;
    
  }
  
  /**
   * The method will determine the smaller root
   * from the calling expression object.
   * @return The smaller root of two or one roots, 
   * or Double.MAX_VALUE if infinite roots.
   * @throws Exception Throws "No Solution" if no roots.
   */
  public double smallerRoot() throws Exception {
    if(numberOfRoots() == 0)
      throw new Exception("No solution");
    else if(numberOfRoots() == 3)
      return -Double.MAX_VALUE;
    else {
    double root1 = (-b + Math.sqrt(b*b - 4*a*c))/(2*a);
    double root2 = (-b - Math.sqrt(b*b - 4*a*c))/(2*a);
     if(root1 > root2)
       return root2;
     else
       return root1;
    }
  }
 
  /**
   * The method will determine the larger root
   * from the calling expression object.
   * @return The larger root of two or one roots, 
   * or -Double.MAX_VALUE if infinite roots.
   * @throws Exception No solution if no roots.
   */
  public double largerRoot() throws Exception {
    if(numberOfRoots() == 0)
      throw new Exception("No solution");
    else if(a == 0 && b == 0 & c == 0)
      return Double.MAX_VALUE;
    else{
    double root1 = (-b + Math.sqrt(b*b - 4*a*c))/(2*a);
    double root2 = (-b - Math.sqrt(b*b - 4*a*c))/(2*a);
     if(root1 > root2)
       return root1;
     else
       return root2;
    }
  }
     
  /**
   * This method will determine if a QuadraticExpression
   * is the same as the calling object. It will do so 
   * by comparing the values of both objects.
   * @param q A QuadraticExpression to compare.
   * @return True or false.
   */
  public boolean equals(Object obj){
    if(obj instanceof QuadraticExpression){
      QuadraticExpression q1 = (QuadraticExpression) obj;
      if(a != q1.a || b != q1.b || c != q1.c)
        return false;
      else 
        return true;
    }
    else  
      return false;
    }
  
  /**
   * The method will create a new QuadraticExpression
   * with the same values of the calling expresion.
   * @return A new QaudraticExpression.
   */
  public QuadraticExpression clone() throws CloneNotSupportedException {
    
    QuadraticExpression clone = null;
    
    try{
      clone = (QuadraticExpression)super.clone();
      return clone;
    } catch (CloneNotSupportedException e){
      e.printStackTrace();
    }
    
    return clone;
      
  }  
}