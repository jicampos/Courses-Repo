public class Cs275_Hw5{
  
  public static void main(String[] args){
  
    System.out.println("Testing binaryPrint");
    System.out.println("--------------------");
    System.out.print("binaryPrint(0): ");
    binaryPrint(0); // 0
    System.out.println();
    System.out.print("binaryPrint(4): ");
    binaryPrint(4); // 100
    System.out.println();
    System.out.print("binaryPrint(27): ");
    binaryPrint(27); // 11011
    System.out.println();
    
    System.out.println();
    System.out.println("Testing numbers");
    System.out.println("--------------------");
    System.out.println("numbers(00101, 2): ");
    numbers("00101", 2);
  }
  
  public static void binaryPrint(int n){
    if(n < 2)
      System.out.print(n);
    else{
      binaryPrint(n/2);
      System.out.print(n%2);
    }
  }
  
  public static void numbers(String prefix, int k) {
    if(prefix == null) throw new IllegalArgumentException("prefix is null");
    else if(k < 0) throw new IllegalArgumentException("k is negative");
    else if(k == 0) System.out.println(prefix);
    else{
      numbers(prefix + "0", k-1);
      numbers(prefix + "1", k-1);     
    }
  }
}