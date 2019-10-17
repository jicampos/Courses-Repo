public class Test{

  public static void main(String[] args){
Polynomial test1 = new Polynomial(1);
    test1.add_to_coef(2, 1);
    test1.add_to_coef(3, 2);
    System.out.println("The polynomial test1 should be: " +test1.toString());
      for(int i=0; i<test1.coeff.length; i++)
   {
     System.out.println(test1.coeff[i]);
   }
    
    Polynomial test2 = new Polynomial(2);
    test2.add_to_coef(3, 1);
    test2.add_to_coef(5, 4);
    System.out.println("The polynomial test2 should be: " +test2.toString());
      for(int i=0; i<test2.coeff.length; i++)
   {
     System.out.println(test2.coeff[i]);
   }
    
    System.out.println("The sum of the two polynomials is: " + test1.add(test2));  
  }
}
