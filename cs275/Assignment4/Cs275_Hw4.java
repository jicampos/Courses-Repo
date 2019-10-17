import java.util.Stack;
import java.util.Scanner;

public class Cs275_Hw4{
  
  public static void main(String[] args) {
    
    Scanner scanner = new Scanner(System.in);
    
    boolean answer;
    String converted;
    
    do {
      
      System.out.print("Enter an expression to convert from infix to postfix: ");
      converted = infix2postfix(scanner.nextLine() );
      System.out.println(converted);
      System.out.println(eval(converted) );
      
      // Asks user for another input, returns true to enter a new expression
      answer = newExpression();
      
    } while(answer);
  
  
  }  
  
  public static boolean newExpression(){
  
    Scanner scanner = new Scanner(System.in);
    char c;
    System.out.print("Press any key to enter another expression or [N] or [n] to cancel: ");
    c = scanner.next().charAt(0);
    System.out.println();
    if(c == 'N' || c == 'n')
      return false;
    else
      return true;
      
  }
  
  
  public static String infix2postfix(String s){
    
    Stack<Character> operators = new Stack<Character>();
    char next;
    int length = s.length(); 
    String answer = "";
    
    
    for(int i = 0; i < length; i++) {
      next = s.charAt(i);
      
      if(next == '(')
        operators.push(next);
      else if(Character.isDigit(next) || next == '.' || Character.isLetter(next) ) // Character.isDigit(string.charAt(index)) <-- Will return true if it's a digit
        answer += next;
      else if(isOperator(next) ) { // isOperator(char c) <-- Method will check for operators 
        answer += " ";
        while(!operators.empty() && operators.peek() != '(' && precedence(next, operators.peek()) ) {
          answer += " " + operators.pop();
        }
        answer += " ";
        operators.push(next);
      }
      else{
        if(next != ' ') {
          while(!operators.empty() && operators.peek() != '(') {
            answer += " " + operators.pop() + " ";
          }
          if(operators.empty() )
            throw new IllegalArgumentException("Unbalanced Parentheses, to many ')'");
          else 
            operators.pop(); 
        }
      }
      
    }
    
    while(!operators.empty() ) {
      if(operators.peek() == '(')
        throw new IllegalArgumentException("Unbalanced Parentheses, to many '('");
      else
        answer += " " + operators.pop() + " ";
    }
    
    
    return answer;
  }
  
  
  public static boolean isOperator(char next) {
    return (next == '+' || next == '-' || next == '*' || next == '/' || next == '^' || next == '%');
  }
  
  
  public static boolean precedence(char next, char peek) { // Checks for the correct precedence 
    if(next == '^') { 
      if(peek == '^')
        return true;
      else 
        return false;
    }
    else if(next== '*' || next== '/' || next == '%') {
      if(peek == '*' || peek == '/' || next == '%')
        return true;
      else 
        return false;
    }
    else   // nextis '-' or '+' 
      return true;
  }
  
  
  public static double eval(String expression){
    
    Scanner scanner = new Scanner(expression);
    Stack<Double> operands = new Stack<Double>();
    
    while(scanner.hasNext() ) {
      
      if(scanner.hasNextDouble() ) 
        operands.push(scanner.nextDouble() );
      else {
        double operand2 = operands.pop();
        double operand1 = operands.pop();
        String operator = scanner.next();
        
        switch(operator) {
          case "+" : operands.push(operand1 + operand2); break;
          case "-" : operands.push(operand1 - operand2); break;
          case "*" : operands.push(operand1 * operand2); break;
          case "/" : operands.push(operand1 / operand2); break;
          case "%" : operands.push(operand1 % operand2); break;
          case "^" : operands.push(Math.pow(operand1, operand2)); break;
        }
      }
    }
    scanner.close();
   return operands.pop();
  }
  
}  