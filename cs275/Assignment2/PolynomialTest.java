import java.util.Scanner;

public class PolynomialTest 
{
  public static void main(String[] args){
    
    Polynomial p1 = new Polynomial(7.5);
    p1.add_to_coef(4, 3);
    p1.add_to_coef(1, 3);
    System.out.println(p1);
    System.out.println();
    
    p1.add_to_coef(10, 12);
    
    p1.assign_coeff(3, 2);
    System.out.println(p1);
    p1.assign_coeff(8, 3);
    System.out.println(p1);
    System.out.println();
    
    System.out.print("The value of the cofficient with the degree of 1 is: ");
    System.out.println( p1.coefficient(1) );
    System.out.print("The value of the cofficient with the degree of 3 is: ");
    System.out.println( p1.coefficient(3) );
    System.out.println();
    
    System.out.print("The polynomial evaluated for x = 1 is : ");
    System.out.println( p1.eval(1) );
    System.out.println();
    
    Polynomial p2 = new Polynomial(7.5);
    
    
    System.out.print("Determining if p1 and p2 equal: ");
    System.out.println( p1.equals(p2) );
    
    p2.add_to_coef(8, 3);
    p2.add_to_coef(3, 2);
    
    System.out.print("Determining if p1 and p2 equal: ");
    System.out.println( p1.equals(p2) );
    System.out.println();
    
    System.out.println("Polynomials p1 + p2 is equal to: ");
    Polynomial p3 = p1.add(p2);
    System.out.println(p3);
    
    Polynomial p4 = new Polynomial();
    System.out.println();
    System.out.println("Polynomial p1 multiplied by p2 is: ");
    System.out.println( p4 = p1.multiply(p2) );
    System.out.println();
    
    Polynomial p5 = new Polynomial(p4);
    System.out.print("Determining if p4 and p5 equal: ");
    System.out.println( p4.equals(p5) );
   

  }
}